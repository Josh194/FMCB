#include <iostream>

#include <Windows.h>
#include <cstdint>

int main() {
    std::cout << "Attempting to connect to core server" << std::endl;

    DWORD bytesRead;

    // Type: REGISTER_NEW (1), PID: 2305 (1 9 0 0), Name Size: 4 (4), Name: Test (84 101 115 116)
    unsigned char out[10] = {1, 1, 9, 0, 0, 4, 84, 101, 115, 116};
    unsigned char in[32];

    CallNamedPipeA(
        "\\\\.\\pipe\\FMBCRegister",
        &out,
        10,
        &in,
        32,
        &bytesRead,
        NMPWAIT_NOWAIT
    );

    std::cout << "Data received: ";
    for (int i = 0; i < bytesRead; i++){
        std::cout << +in[i] << " ";
    }
    std::cout << std::endl;

    std::cout << bytesRead << " bytes read" << std::endl;

    return 0;
}