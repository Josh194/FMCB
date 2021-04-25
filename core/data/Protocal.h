#pragma once

#include <cstdint>

typedef uint64_t SessionId[2]; // 64 bits * 2 = 128 bits

namespace handshake {

    constexpr unsigned char maxName = 20;

    /*
    Used to query the capabilities of the server
    */
    struct Query {
        enum Capabilities : std::int32_t {
            kABIVersion = 0x00000001,
            kProcessing = 0x00000002
        } capabilities;
    };

    struct QueryAck { 
        // TODO: implement
    };

    /*
    A request to the server to register a client.
    */
    struct Request {
        enum Type : std::int32_t {
            kRegisterNew = 1,
            kRegisterExisting
        } type;

        std::uint32_t pid;

        std::uint32_t nameLength;
        char name[maxName];
    };

    struct RequestAck {
        /*
        The status of the request.
        */
        enum Status : std::int32_t {
            kErrorRequestDenied = -2,
            kErrorInvalidRequest,
            kSuccess,
            kErrorServerBusy
        } status;

        static_assert(kSuccess == 0);

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