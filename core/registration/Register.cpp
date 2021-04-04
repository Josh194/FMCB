#include "Register.h"

#include <windows.h>
#include <iostream>
#include <vector>

// ? Put in header? ----------------------------------------
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

/*
TODO: nameLength must be (max - 1) (- 1 so a null terminator can be inserted)
We may need a program wide error system, similar to win32, in order to free up return values
*/
SessionId* client_register::addClient(char* name, unsigned char nameLength, uint32_t processId) {
	if (clients.size() == maxClients) {
		return nullptr;
	}

	// TODO: Reduce number of instances of clients[clients.size() - 1]
	// ? This doesn't initialize the new object, right?
	clients.emplace_back();
	clients[clients.size() - 1].sessionId[1] = 0xa538f; // TODO: generate a unique SID automatically

	memcpy(&clients[clients.size() - 1].name, name, nameLength); // Copy the (Non null-terminated name into the struct)
	clients[clients.size() - 1].name[nameLength] = 0; // Inserts a null terminator at the end of the name so it can be easily printed

	std::cout << "Name (Length " << +nameLength << "): " << clients[clients.size() - 1].name << std::endl;
	std::cout << "PID: " << processId << std::endl;

	return &clients[clients.size() - 1].sessionId;
}

bool client_register::removeClient(unsigned char index) {
	if (index < clients.size()) {
		// TODO: This can maybe be done more cleanly
		clients.erase(clients.begin() + index);

		return true;
	}

	return false;
}

unsigned char client_register::size() {
	return clients.size();
}