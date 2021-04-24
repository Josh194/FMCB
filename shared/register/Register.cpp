#include "Register.h"

#include "../Global.h"

#include <cstring>
#include <Windows.h>

SessionId sid;

// ! TODO: Don't hardcode
char name[19]; // Server wants 19 to be able to insert a null terminator manually

bool registration::initialize(const char* name, unsigned char nameLength) {
    if (nameLength > 19) {
        return false;
    }

    std::memcpy(&::name, name, nameLength);

    return true;
}

handshake::RequestAck::Status registration::request() {
    // TODO: use initialized name
    // Type: REGISTER_NEW (1), PID: DWORD (0 0 0 0), Name Size: 4 (4), Name: Test (84 101 115 116)
    handshake::Request out = {
        handshake::Request::Type::REGISTER_NEW,
        GetCurrentProcessId(),
        4,
        "Test"
    };

    handshake::RequestAck in;
    in.status = in.SUCCESS;

    // TODO: can we find a use for this?
    DWORD bytesRead;

    // TODO: extended error checking
    CallNamedPipeA(
        "\\\\.\\pipe\\FMBCRegister",
        &out,
        sizeof(out),
        &in,
        sizeof(in),
        &bytesRead,
        NMPWAIT_NOWAIT
    );

    // ? Should we explicitly set last error to zero beforehand?
    if (GetLastError() == ERROR_PIPE_BUSY) {
        return in.status; // ? Should this be cleaned up?
    }

    // ! TODO: save session id

    // TODO: cleanup
    if (in.status == handshake::RequestAck::Status::SUCCESS) { // if successful
        api_global::bufferSize = 1024;
        api_global::fileHandle = in.fileHandle;
    }

    return in.status;
}