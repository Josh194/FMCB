#pragma once

#include "LinkedArray.h"

#include <cstdint>

typedef uint64_t SessionId[2]; // 64 bits * 2 = 128 bits

// This ordering should be fairly optimal for memory/performance
struct Client {
	void* fileHandle; // TODO: start replacing win32 types with either generic types or a preprocessor selected type in preparation for the mac/linux port
	void* communication;
	SessionId sessionId;

	char name[24];
};

namespace database {

    void init();

    extern LinkedArray<Client, 32> clients;

    // We will also need a container for other server connections in the future
    
}