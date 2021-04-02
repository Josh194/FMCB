#include <iostream>

#include <Windows.h>

int main() {
    std::cout << "Attempting to connect to core server" << std::endl;

    DWORD bytes;

    char data[2] = {1, 2};

    CallNamedPipeA(
        "\\\\.\\pipe\\FMBCRegister",
        &data,
        2,
        NULL,
        0,
        &bytes,
        NMPWAIT_NOWAIT
    );

    std::cout << GetLastError() << std::endl;

    return 0;
}