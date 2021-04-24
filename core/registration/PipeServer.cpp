#include "PipeServer.h"

#include "Register.h"
#include "Status.h"

#include <Windows.h>
#include <iostream>

// TODO: replace with variable; pipe count must be <= maxSubsystems
#define PIPE_COUNT 2
#define PIPE_BUFFER_SIZE 32

struct PipeInst {
	HANDLE handle = INVALID_HANDLE_VALUE;

	bool waiting = false;

	DWORD bytesRead;
	char buffer[PIPE_BUFFER_SIZE]; 

	OVERLAPPED overlap;
};
 
PipeInst pipes[PIPE_COUNT];

// TODO: maybe clean this up
const char error_response = -1;

bool registration_server::init() {
    for (int i = 0; i < PIPE_COUNT; i++) {
		/*
		! Inherently, this opens up the core server to malicious use,
		! extreme care must be taken to insure no information is shared that could compromise the host machine.

		This should be shared with subsystem developers in an obvious place, along with a message encouraging them to write secure network code.
		Even still, the subsystem api should be written in such a way to reduce the risk of an experienced dev opening up their system for exploitation.

		Because of this, a subsystem-side api should be provided, and developers should be highly encouraged to use it, doing otherwise at their own (and any of their users) risk.

		Some/all network data should be encrypted, or an option should at least exist for it (maybe subsystems could opt-in to full or partial encryption depending on their content),
		as some users may prefer the slight performance boost in exchange for third parties being able to see the volume of dirt transferred between two games (of course network data may not always be so insignificant)
		*/
		pipes[i].handle = CreateNamedPipeA(
			"\\\\.\\pipe\\FMBCRegister",
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
			4,
			1024, // Estimated public key size is 2048 bits, assuming perfect packing (not the case) this can hold 4 public keys at once (a public key being the largest object to be used in a registration handshake)
			1024,
			50,
			NULL
		);

		if (pipes[i].handle == INVALID_HANDLE_VALUE) {
			std::cout << "Failed to initialize pipe#" << i << " with error " << GetLastError() << ". This could be because a previous session was not cleaned up completely, or an application could be attempting to hijack communication." << std::endl;

			return false;
		}

		// ? Should this be a separate function?
		ConnectNamedPipe(pipes[i].handle, &pipes[i].overlap);

		DWORD error = GetLastError();

		if (error != ERROR_IO_PENDING && error != ERROR_PIPE_CONNECTED) {
			std::cout << "Pipe#" << i << " failed to enable incoming connections with error " << GetLastError() << std::endl;

			return false;
		} else {
			std::cout << "Pipe#" << i << " waiting for incoming connections" << std::endl;
		}
	}

    return true;
}

bool registration_server::cycle() {
	// TODO: this whole system needs improvement
	for (int i = 0; i < PIPE_COUNT; i++) {
		if (pipes[i].waiting) {	
			if (HasOverlappedIoCompleted(&pipes[i].overlap)) {
				std::cout << "Pipe#" << i << " finished job, disconnecting subsystem and waiting for a new connection" << std::endl;

				pipes[i].waiting = false;

				DisconnectNamedPipe(pipes[i].handle);
				// ? Shoule reconnect code be moved to a function?
				ConnectNamedPipe(pipes[i].handle, &pipes[i].overlap);

				DWORD error = GetLastError();

				if (error != ERROR_IO_PENDING && error != ERROR_PIPE_CONNECTED) {
					std::cout << "Pipe#" << i << " failed to re-enable incoming connections with error " << GetLastError() << std::endl;

					// ? Should not exit right away maybe
					return false;
				}
			}
		} else {
			// TODO: Overlapped IO means that this may run more than once for the same connection, this should be fixed
			ReadFile(
				pipes[i].handle,
				&pipes[i].buffer,
				PIPE_BUFFER_SIZE,
				&pipes[i].bytesRead,
				&pipes[i].overlap
			);

			if (pipes[i].bytesRead != 0) {
				std::cout << "Connection received on pipe#" << i << std::endl;

				// TODO:: clean this up maybe
				const Client* client = client_register::registerClient(pipes[i].buffer + 6, pipes[i].buffer[5]);

				// TODO: maybe move read/write code to their own functions, this is a bit messy
				if (client == nullptr) {
					if (status == Status::kErrorOverflow) {
						std::cout << "Maximum number of subsystems reached, request will not be serviced" << std::endl;
					};

					WriteFile(
						pipes[i].handle,
						&error_response,
						1,
						NULL,
						&pipes[i].overlap
					);
				} else {
					// TODO: make this more efficient maybe
					// ! TODO: does not account for 32 bit handles
					char message[25];

					message[0] = 0; // Success code

					memcpy(message + 1, client -> sessionId, 16);

					// TODO: clean this up
					HANDLE clientHandle = OpenProcess(
						PROCESS_DUP_HANDLE,
						false,
						*reinterpret_cast<uint32_t*>(pipes[i].buffer + 1)
					);

					// ? What happens if the client doesn't close this handle? Should we close it?
					DuplicateHandle(
						GetCurrentProcess(),
						client -> fileHandle,
						clientHandle,
						reinterpret_cast<HANDLE*>(message + 17),
						NULL,
						false,
						DUPLICATE_SAME_ACCESS 
					);

					CloseHandle(clientHandle);

					WriteFile(
						pipes[i].handle,
						&message,
						25,
						NULL,
						&pipes[i].overlap
					);
				}

				pipes[i].bytesRead = 0;
				pipes[i].waiting = true;
			}
		}
	}

	return true;
}

void registration_server::cleanup() {
	for (int i = 0; i < PIPE_COUNT; i++) {
		if (pipes[i].handle != INVALID_HANDLE_VALUE) {
			CloseHandle(pipes[i].handle);
		}
	}
}