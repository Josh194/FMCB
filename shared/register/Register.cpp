#include "Register.h"

#include "../Global.h"

#include <cstdint>
#include <cstring>
#include <Windows.h>

typedef uint64_t SessionId[2];

SessionId sid;

char name[23]; // Server wants 23 to be able to insert a null terminator manually

bool registration::initialize(const char* name, unsigned char nameLength) {
    if (nameLength > 23) {
        return false;
    }

    std::memcpy(&::name, name, nameLength);

    return true;
}

char registration::request() {
    // TODO: use initialized name
    // Type: REGISTER_NEW (1), PID: DWORD (0 0 0 0), Name Size: 4 (4), Name: Test (84 101 115 116)
    unsigned char out[10] = {1, 0, 0, 0, 0, 4, 84, 101, 115, 116};
    unsigned char in[32];

    // TODO: cleanup
    *(DWORD*) (out + 1) = GetCurrentProcessId();

    DWORD bytesRead;

    // ! TODO: return -1 if pipe is busy
    CallNamedPipeA(
        "\\\\.\\pipe\\FMBCRegister",
        &out,
        10,
        &in,
        32,
        &bytesRead,
        NMPWAIT_NOWAIT
    );

    // ! TODO: save session id

    api_global::bufferSize = 1024;
    api_global::fileHandle = *(HANDLE*) (in + 17);

    return in[0];
}