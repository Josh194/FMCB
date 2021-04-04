#include "Global.h"
#include "minparse.h"

#include "registration/PipeServer.h"
#include "registration/Register.h"

#include <iostream>
#include <vector>
#include <atomic>
#include <climits>
// ? Can we include a slightly less bloated header?
#include <Windows.h>

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

	registration_server::cleanup();

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

				client_register::init(in);

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

	if (!registration_server::init()) {
		cleanupAndExit();
	}

	std::cout << "Startup complete" << std::endl;

	while (true) {
		if (shouldExit) {
			cleanupAndExit();
		}

		registration_server::cycle();

		Sleep(250);
	}

	cleanupAndExit();
}