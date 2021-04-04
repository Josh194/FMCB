#pragma once

#include <cstdint>

typedef uint64_t SessionId[2]; // 64 bits * 2 = 128 bits

//typedef void* HANDLE;

/*
Contains the functions necessary to interact with the internal list of registered clients.
*/
namespace client_register {

    /*
    Initializes the client register with a given maximum number of registered clients.

    This method should only be called once.
    */
    void init(unsigned char maxClients);

    /*
    Adds a client to the internal register.

    The returned pointer should not be written to, only read from.

    Returns a pointer to a unique session id to be given to the requesting client, or nullptr if adding the client would bring the number of registered clients over the internal maximum.
    */
    SessionId* addClient(char* name, unsigned char nameLength, uint32_t processId);

    /*
    Removes the client at the given index.

    Returns false if no client is registered at the provided index.
    */
    bool removeClient(unsigned char index);

    /*
    Returns the number of registered clients.
    */
    unsigned char size();

    // TODO: add [] override

}