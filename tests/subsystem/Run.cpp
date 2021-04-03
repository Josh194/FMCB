#include <iostream>

#include <Windows.h>

int main() {
    std::cout << "Attempting to connect to core server" << std::endl;

    DWORD bytesRead;

    // Type: REGISTER_NEW (1), PID: 2305 (1 9 0 0), Name: Test\0 (84 101 115 116 0)
    unsigned char out[10] = {1, 1, 9, 0, 0, 84, 101, 115, 116, 0};
    char in[32];

    CallNamedPipeA(
        "\\\\.\\pipe\\FMBCRegister",
        &out,
        10,
        &in,
        32,
        &bytesRead,
        NMPWAIT_NOWAIT
    );

    std::cout << "Data received: " << in << std::endl;
    std::cout << bytesRead << " bytes read" << std::endl;

    return 0;
}