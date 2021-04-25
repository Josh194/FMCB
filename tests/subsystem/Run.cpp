#include <iostream>

#include "register/Register.h"
#include "memory/BufferAccess.h"

#include <atomic>
#include <Windows.h> // ! Only needed for inputThread

std::atomic<bool> shouldExit = false; // TODO: Write a better way of doing this
DWORD WINAPI inputThread(LPVOID lpThreadParameter) {
	int a;

	std::cin >> a;

	shouldExit = true;

	return 0;
}

HANDLE inputThreadHandle;

int main() {
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

		return 0;
	}

    std::cout << "Attempting to connect to core server" << std::endl;

    // ! Isn't used by request() yet
    // registration::initialize();

    if (registration::request() == handshake::RequestAck::kSuccess) {
        std::cout << "Connection successful" << std::endl;

        char* comm = reinterpret_cast<char*>(communication::map());

        std::cout << reinterpret_cast<void*>(comm) << std::endl;

        comm[0] = 5;

        while (shouldExit == false) {
            if (comm[512] == 5) {
                break;
            }

            Sleep(250);
        }

        std::cout << +communication::unmap() << std::endl;
    } else {
        std::cout << "Connection failed" << std::endl;
    }

    CloseHandle(inputThreadHandle);

    std::cout << "Exiting" << std::endl;

    return 0;
}