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

    struct QueryAck { // ! May not be needed

    };

    /*
    A request to the server to register a client.
    */
    struct Request {
        enum struct Type : std::int32_t {
            REGISTER_NEW = 0,
            REGISTER_EXISTING = 1
        } type;

        std::uint32_t pid;

        std::uint32_t nameLength;
        char name[20];
    };

    struct RequestAck {
        /*
        The status of the request.
        */
        enum struct Status : std::int32_t {
            SUCCESS = 0,
            ERROR_REQUEST_DENIED = -1,
            ERROR_SERVER_BUSY = -2
        } status;

        /*
        A handle to a shared communication file, duplicated to the context of the requesting client.
        */
        alignas(8) void* fileHandle; // https://docs.microsoft.com/en-us/windows/win32/winprog64/interprocess-communication

        /*
        The session id assigned to the client.
        */
        SessionId sid;
    };

}