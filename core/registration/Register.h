#pragma once

#include <cstdint>

constexpr unsigned char maxName = 24;

typedef uint64_t SessionId[2]; // 64 bits * 2 = 128 bits

// This ordering should be fairly optimal for memory/performance
struct Client {
	void* fileHandle; // TODO: start replacing win32 types with either generic types or a preprocessor selected type in preparation for the mac/linux port
	void* communication;
	SessionId sessionId;

	char name[maxName];
};

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

    Returns a pointer to the added client, which now contains a unique sessionId, or nullptr if adding the client would bring the number of registered clients over the internal maximum.
    */
    const Client* addClient(char* name, unsigned char nameLength);

    /*
    Removes the client at the given index.

    Returns false if no client is registered at the provided index.
    */
    bool removeClient(unsigned char index);

    /*
    Returns the number of registered clients.
    */
    unsigned char size();

    // ? Can this be done better?
    void cleanup();

    // TODO: add [] override maybe

}