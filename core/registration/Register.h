#pragma once

#include "data/Database.h"

#include <cstdint>

constexpr unsigned char maxName = 24;

/*
Contains the functions necessary to interact with the internal list of registered clients.
*/
namespace client_register {

    /*
    Initializes the client register with a given maximum number of registered clients.

    This method should only be called once.
    */
    void init(std::uint32_t maxClients);

    /*
    Adds a client to the internal register.

    Returns a pointer to the added client, which now contains a unique sessionId, or nullptr if adding the client would bring the number of registered clients over the internal maximum.
    */
    const Client* registerClient(char* name, unsigned char nameLength);

    /*
    Returns the number of registered clients.
    */
    unsigned char size();

    // ? Can this be done better?
    void cleanup();

    // TODO: add [] override maybe

}