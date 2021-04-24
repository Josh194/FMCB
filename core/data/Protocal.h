#pragma once

#include <cstdint>

typedef uint64_t SessionId[2]; // 64 bits * 2 = 128 bits

namespace handshake {

    /*
    Used to query the capabilities of the server
    */
    struct Query { // ! May not be needed
        enum struct Capabilities : std::int32_t {
            VERSION = 0x00000001,
            BIT_WIDTH = 0x00000002,
            PROCESSING = 0x00000004
        } capabilities;
    };

    struct QueryAck { 
        // ! May not be needed
    };

    /*
    A request to the server to register a client.
    */
    struct Request {
        enum struct Type : std::int32_t {
            REGISTER_NEW = 1,
            REGISTER_EXISTING = 2
        } type;

        std::uint32_t pid;

        std::uint32_t nameLength;
        char name[20];
    };

    struct RequestAck {
        /*
        The status of the request.
        */
        enum Status : std::int32_t {
            ERROR_REQUEST_DENIED = -2,
            ERROR_INVALID_REQUEST,
            SUCCESS, // TODO: Assert this
            ERROR_SERVER_BUSY
        } status;

        /*
        A handle to a shared communication file, duplicated to the context of the requesting client.
        */
        // ! Can we only use the low 32 bits (Supposedly only ones used when sharing between 32/64 bit processes)? Would save 8 bytes if so.
        alignas(8) void* fileHandle; // https://docs.microsoft.com/en-us/windows/win32/winprog64/interprocess-communication

        /*
        The session id assigned to the client.
        */
        SessionId sid;
    };

}