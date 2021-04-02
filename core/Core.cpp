#include <iostream>
#include <atomic>
// Can we include a slightly less bloated header?
#include <Windows.h>

#include "minparse.h"

#include "Global.h"

std::atomic<bool> shouldExit = false;

DWORD WINAPI inputThread(LPVOID lpThreadParameter) {
	int a;

	std::cin >> a;

	shouldExit = true;

	return 0;
}

int main(int argc, char** argv) {
	std::cout << "FMCB core server " << VERSION << std::endl;

	minparse::init(argc - 1, argv + 1);

	minparse::argument arg = {};

	while (minparse::parse(&arg)) {
		// Obviously not very good, minparse will need to be farther developed
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
			if (arg.argc == 1) {
				std::cout << "Max subsystems set to " << arg.argv[0] << std::endl;
			}

			break;

		default:
			std::cout << "Invalid parameter \"" << arg.arg[0] << "\"" << std::endl;

			return 0;
		}
	}

	std::cout << "Creating subsystem registration pipe" << std::endl;

	/*
	! Inherently, this opens up the core server to malicious use,
	! extreme care must be taken to insure no information is shared that could compromise the host machine.

	This should be shared with subsystem developers in an obvious place, along with a message encouraging them to write secure network code.
	Even still, the subsystem api should be written in such a way to reduce the risk of an experienced dev opening up their system for exploitation.

	Because of this, a subsystem-side api should be provided, and developers should be highly encouraged to use it, doing otherwise at their own (and any of their users) risk.

	Some/all network data should be encrypted, or an option should at least exist for it (maybe subsystems could opt-in to full or partial encryption depending on their content),
	as some users may prefer the slight performance boost in exchange for third parties being able to see the volume of dirt transferred between two games (of course network data may not always be so insignificant)
	*/
	HANDLE pipe = CreateNamedPipeA(
		"\\\\.\\pipe\\FMBCRegister",
		PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
		4,
		1024, // Estimated public key size is 2048 bits, assuming perfect packing (not the case) this can hold 4 public keys at once (a public key being the largest object to be used in a registration handshake)
		1024,
		50,
		NULL
	);

	std::cout << GetLastError() << std::endl;

	/*
	Need to use win32 threads as my gcc doesn't like posix, I think because I told it to on installation. I could just reinstall, but where's the fun in that?
	Besides, we're already going to be writting platform-specific code, using the native functions gives us more control, and should in theory give a tiny performance edge, not that we need it for anything.
	*/
	// Should do this after core server has finished starting up
	// Is 1024 bytes enough for C++ std i/o?
	CreateThread(
		NULL,
		1024,
		inputThread,
		NULL,
		0,
		NULL
	);

	OVERLAPPED state = {};

	ConnectNamedPipe(pipe, &state);

	DWORD bytes = 0;
	char buffer[2] = {};
	OVERLAPPED overlapped = {};

	while (true) {
		// Readfile may "fail" occasionally at high check rates as it is asynchronous"
		if (bytes != 0) {
			std::cout << "Connected: " << +buffer[0] << "/" << +buffer[1] << std::endl;

			DisconnectNamedPipe(pipe);

			break;
		}

		ReadFile(
			pipe,
			&buffer,
			2,
			&bytes,
			&overlapped
		);

		if (shouldExit) {
			break;
		}

		Sleep(500);
	}

	CloseHandle(pipe);

	return 0;
}