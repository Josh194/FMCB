#include "PipeServer.h"

#include "Register.h"

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
			std::cout << "Failed to initialize pipe#" << i << " with error " << GetLastError()
				<< ". This could be because a previous session was not cleaned up completely, or an application could be attempting to hijack communication." << std::endl;

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
				// TODO: move reconnect code to a function
				ConnectNamedPipe(pipes[i].handle, &pipes[i].overlap);

				DWORD error = GetLastError();

				if (error != ERROR_IO_PENDING && error != ERROR_PIPE_CONNECTED) {
					std::cout << "Pipe#" << i << " failed to re-enable incoming connections with error " << GetLastError() << std::endl;

					// ? Should not exit right away maybe
					return false;
				}
			}
		} else {
			ReadFile(
				pipes[i].handle,
				&pipes[i].buffer,
				PIPE_BUFFER_SIZE,
				&pipes[i].bytesRead,
				&pipes[i].overlap
			);

			if (pipes[i].bytesRead != 0) {
				std::cout << "Connection received on pipe#" << i << std::endl;

				SessionId* id = client_register::addClient(pipes[i].buffer + 6, *(unsigned char*) (pipes[i].buffer + 5), *(uint32_t*) (pipes[i].buffer + 1));

				if (id == nullptr) {
					// TODO: implement actual code for this; pipes should notify subsystems attempting to connect that their connection cannot be serviced to prevent them from assuming an instance will soon be available to answer their request.
					std::cout << "Warning, maximum number of subsystems reached" << std::endl;

					return false;
				}

				WriteFile(
					pipes[i].handle,
					id,
					16,
					NULL,
					&pipes[i].overlap
				);

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