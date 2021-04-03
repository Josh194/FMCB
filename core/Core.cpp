#include <iostream>
#include <vector>
#include <atomic>
#include <climits>
// ? Can we include a slightly less bloated header?
#include <Windows.h>

#include "minparse.h"

#include "Global.h"

// TODO: replace with variable; pipe count must be <= maxSubsystems
#define PIPE_COUNT 2
#define PIPE_BUFFER_SIZE 32

typedef char SessionID[16]; // 16 bytes * 8 bits = 128 bits

struct PipeInst {
	HANDLE handle = INVALID_HANDLE_VALUE;

	bool waiting = false;

	DWORD bytesRead;
	char buffer[PIPE_BUFFER_SIZE]; 

	OVERLAPPED overlap;
};

struct Subsystem {
	std::string name;
	SessionID sessionid;

	HANDLE communication;
};
 
PipeInst pipes[PIPE_COUNT]; // ? Should this be configureable?

unsigned char maxSubsystems = 2; // Could probably just use an int, but this adds another level of protection from runoff
std::vector<Subsystem> clients;

HANDLE inputThreadHandle; // TODO: maybe put this somewhere else

std::atomic<bool> shouldExit = false; // TODO: Write a better way of doing this

void cleanupAndExit() {
	std::cout << "Cleaning up; you should receive one more message before the program exits." << std::endl;

	if (inputThreadHandle != NULL) {
		/*
		? Does this actually exit the thread cleanly?
		From the api, it would seem that the thread stack is not unallocated unless it closes itself (though it's probably cleaned up automatically by any remotely recent version of windows).
		*/
		CloseHandle(inputThreadHandle);
	}

	for (int i = 0; i < PIPE_COUNT; i++) {
		if (pipes[i].handle != INVALID_HANDLE_VALUE) {
			CloseHandle(pipes[i].handle);
		}
	}

	std::cout << "Cleanup complete, exiting." << std::endl;

	std::exit(0);
}

DWORD WINAPI inputThread(LPVOID lpThreadParameter) {
	int a;

	std::cin >> a;

	shouldExit = true;

	return 0;
}

int main(int argc, char** argv) {
	std::cout << "FMCB core server " << VERSION << std::endl;

	if (CHAR_BIT != 8) {
		std::cout << "Byte size is not 8, FMCB assumes the size of a byte in order to provide a common ground for subsystems, and to insure the length of certain security keys.\nCritical error detected, shutting down." << std::endl;

		return 0;
	}

	minparse::init(argc - 1, argv + 1);

	minparse::argument arg = {};

	while (minparse::parse(&arg)) {
		// TODO: Obviously not very good, minparse will need to be farther developed
		switch (arg.arg[0]) {
		case 'x':
			/*
			Used by subsystem developers in order to test their code.

			This mode will output extensive debugging info related to connections, internal feature processing, etc.
			*/
			// Alternatively, test code could be controlled via the preprocessor, and two versions of the core server could be built.
			std::cout << "Core server started in test mode" << std::endl;

			break;
		case 't':
			if (arg.argc == 1) {
				std::cout << "Processing thread count set to " << arg.argv[0] << std::endl;
			}

			break;
		case 's':
			if (arg.argc == 1) { // TODO: make minparse do checking like this automatically maybe
				long in = std::strtol(arg.argv[0], nullptr, 10); // TODO: maybe error check a bit more
				
				if (in > 255) {
					std::cout << "argument 's' must be lower than 256, using maximum value instead." << std::endl; // TODO: make minparse do error checking like this automatically maybe

					in = 255;
				}

				maxSubsystems = in;

				std::cout << "Max subsystems set to " << in << std::endl;
			} else {
				std::cout << "argument 's' must be an integer between 0 and 255, ignoring given values." << std::endl;
			}

			break;

		default:
			std::cout << "Invalid parameter \"" << arg.arg[0] << "\"" << std::endl;

			return 0;
		}
	}

	/*
	Need to use win32 threads as my gcc doesn't like posix, I think because I told it to on installation. I could just reinstall, but where's the fun in that?
	Besides, we're already going to be writting platform-specific code, using the native functions gives us more control, and should in theory give a tiny performance edge, not that we need it for anything.
	*/
	// ? Is 1024 bytes enough for C++ std I/O? It should run anyway, but forcing memory to be allocated at runtime can't be good for performance.
	inputThreadHandle = CreateThread(
		NULL,
		1024,
		inputThread,
		NULL,
		0,
		NULL
	);

	if (inputThreadHandle == NULL) {
		std::cout << "Input thread failed to start with error " << GetLastError() << std::endl;

		cleanupAndExit();
	}

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

			cleanupAndExit();
		}
	}

	for (int i = 0; i < PIPE_COUNT; i++) {
		ConnectNamedPipe(pipes[i].handle, &pipes[i].overlap);

		DWORD error = GetLastError();

		if (error != ERROR_IO_PENDING && error != ERROR_PIPE_CONNECTED) {
			std::cout << "Pipe#" << i << " failed to enable incoming connections with error " << GetLastError() << std::endl;

			cleanupAndExit();
		}
	}

	std::cout << "Startup complete, waiting for registration connections" << std::endl;

	while (true) {
		// TODO: this whole system needs improvement
		for (int i = 0; i < PIPE_COUNT; i++) {
			if (shouldExit) {
				cleanupAndExit();
			}

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
						cleanupAndExit();
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

					if (clients.size() >= maxSubsystems) {
						// TODO: implement actual code for this; pipes should notify subsystems attempting to connect that their connection cannot be serviced to prevent them from assuming an instance will soon be available to answer their request.
						std::cout << "Warning, maximum number of subsystems reached" << std::endl;
					}

					std::cout << "Name: " << std::string(pipes[i].buffer + 5) << std::endl;
					std::cout << "PID: " << *((DWORD*) (pipes[i].buffer + 1)) << std::endl;

					// TODO: clean this up
					int index = clients.size();
					clients.push_back({"Name", {'a', '3', 'b', '7', '7', 'k'}, NULL}); // TODO: generate a unique SID automatically

					WriteFile(
						pipes[i].handle,
						&clients[index].sessionid,
						16,
						NULL,
						&pipes[i].overlap
					);

					pipes[i].bytesRead = 0;
					pipes[i].waiting = true;
				}
			}

			Sleep(150);
		}
	}

	cleanupAndExit();
}