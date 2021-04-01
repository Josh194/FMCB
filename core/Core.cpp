#include <iostream>
// Can we include a slightly less bloated header?
#include <Windows.h>

#include "minparse.h"

#include "Global.h"

int main(int argc, char** argv) {
	std::cout << "FMCB core server " << VERSION << std::endl;

	minparse::init(argc - 1, argv + 1);

	minparse::argument arg = {};

	while (minparse::parse(&arg)) {
		// Obviously not very good, minparse will need to be farther developed
		switch (arg.arg[0]) {
		case 't':
			if (arg.argc == 1) {
				std::cout << "Worker count set to " << arg.argv[0] << std::endl;
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

	HANDLE pipe = CreateNamedPipeA(
		"\\\\.\\pipe\\FMBCRegister",
		PIPE_ACCESS_DUPLEX | FILE_FLAG_FIRST_PIPE_INSTANCE | FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
		1,
		1024,
		1024,
		50,
		NULL
	);

	std::cout << GetLastError() << std::endl;

	CloseHandle(pipe);

	return 0;
}