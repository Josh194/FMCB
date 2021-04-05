#include <iostream>

#include <Windows.h>
#include <cstdint>

int main() {
    std::cout << "Attempting to connect to core server" << std::endl;

    DWORD bytesRead;

    // Type: REGISTER_NEW (1), PID: DWORD (0 0 0 0), Name Size: 4 (4), Name: Test (84 101 115 116)
    unsigned char out[10] = {1, 0, 0, 0, 0, 4, 84, 101, 115, 116};
    unsigned char in[32];

    // TODO: cleanup
    *(DWORD*) (out + 1) = GetCurrentProcessId();

    CallNamedPipeA(
        "\\\\.\\pipe\\FMBCRegister",
        &out,
        10,
        &in,
        32,
        &bytesRead,
        NMPWAIT_NOWAIT
    );

    std::cout << "Data received" << std::endl;

    std::cout << "Session Id: ";
    for (int i = 0; i < bytesRead; i++){
        std::cout << +in[i] << " ";
    }
    std::cout << std::endl;

    std::cout << bytesRead << " bytes read" << std::endl;

    HANDLE file = *(HANDLE*) (in + 17);

    void* map = MapViewOfFile(
		file,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		1024 // TODO: this should be handled better
	);

    std::cout << "Address: " << map << std::endl;

    UnmapViewOfFile(map);

    std::cout << CloseHandle(file) << " " << GetLastError() << std::endl;

    return 0;
}