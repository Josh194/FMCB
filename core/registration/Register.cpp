#include "Register.h"

#include <windows.h>
#include <iostream>
#include <vector>

// ? Put in header? ----------------------------------------
#include <cstdint>

// This ordering should be fairly optimal for memory/performance
struct Client {
	HANDLE communication;
	SessionId sessionId;

	char name[24];
};
// ? -------------------------------------------------------

unsigned char maxClients = 2; // Could probably just use an int, but this adds another level of protection from runoff
// ? Maybe replace with preallocated array, custom allocator, or some other data structure?
std::vector<Client> clients;

void client_register::init(unsigned char maxClients) {
	::maxClients = maxClients;
}

// TODO: max nameLength must be 24 - 1 (- 1 so a null terminator can be inserted)
SessionId* client_register::addClient(char* name, unsigned char nameLength, uint32_t processId) {
	if (clients.size() == maxClients) {
		return nullptr;
	}

	clients.push_back({NULL, {0, 0xa538f}, {}}); // TODO: generate a unique SID automatically

	// TODO: Reduce number of instances of clients[clients.size() - 1]
	memcpy(&clients[clients.size() - 1].name, name, nameLength);
	clients[clients.size() - 1].name[nameLength] = 0; // Adds a null terminator

	std::cout << "Name (Length " << +nameLength << "): " << clients[clients.size() - 1].name << std::endl;
	std::cout << "PID: " << processId << std::endl;

	return &clients[clients.size() - 1].sessionId;
}

bool client_register::removeClient(unsigned char index) {
	if (index < clients.size()) {
		// TODO: This can probably be done better
		// ? Does erase() return -1/0/etc one failure?
		clients.erase(clients.begin() + index);

		return true;
	}

	// ? Does skipping the else give worse/better/same performance?
	return false;
}

unsigned char client_register::size() {
	return clients.size();
}