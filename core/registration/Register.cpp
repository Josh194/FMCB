#include "Register.h"

#include <windows.h>
#include <iostream>
#include <vector>

std::uint32_t maxClients = 2;
// ? Maybe replace with preallocated array, custom allocator, or some other data structure?
std::vector<Client> clients;

void client_register::init(std::uint32_t maxClients) {
	::maxClients = maxClients;
}

/*
TODO: nameLength must be (max - 1) (- 1 so a null terminator can be inserted)
We may need a program wide error system, similar to win32, in order to free up return values
*/
const Client* client_register::addClient(char* name, unsigned char nameLength) {
	if (clients.size() == maxClients) {
		return nullptr;
	}

	// ? This doesn't initialize the new object, right?
	Client& client = clients.emplace_back();

	// ? Can we close the file mapping handle after mapping it into process memory?
	client.fileHandle = CreateFileMappingA(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		1024,
		NULL // Protects access from unauthorized local subsystems
	);

	// ! We need an program wide error system
	if (client.fileHandle == NULL) {
		std::cout << "Create file error: " << GetLastError() << std::endl;

		return nullptr;
	}

	client.communication = MapViewOfFile(
		client.fileHandle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		1024 // TODO: this should be handled better
	);

	// ! We need an program wide error system
	if (client.communication == NULL) {
		std::cout << "Map error: " << GetLastError() << std::endl;

		return nullptr;
	}

	client.sessionId[1] = 0xa538f; // TODO: generate a unique SID automatically

	memcpy(&client.name, name, nameLength); // Copy the (Non null-terminated name into the struct)
	client.name[nameLength] = 0; // Inserts a null terminator at the end of the name so it can be easily printed

	std::cout << "Name (Length " << +nameLength << "): " << client.name << std::endl;

	return &client;
}

bool client_register::removeClient(unsigned char index) {
	if (index < clients.size()) {
		// TODO: this can maybe be done more cleanly
		clients.erase(clients.begin() + index);

		return true;
	}

	return false;
}

unsigned char client_register::size() {
	return clients.size();
}

void client_register::cleanup() {
	for(int i = 0; i < clients.size(); i++){
		UnmapViewOfFile(clients[i].communication);

		CloseHandle(clients[i].fileHandle);
	}
}