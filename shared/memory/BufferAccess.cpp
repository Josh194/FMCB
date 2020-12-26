#include "BufferAccess.h"

#include <windows.h>

HANDLE mapHandle;
LPVOID buffer;

bool ipc::create() {
	mapHandle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		0,
		PAGE_READWRITE,
		0,
		buffer_global::BUF_SIZE,
		buffer_global::bufName
	);

	return mapHandle != 0;
}

bool ipc::open() {
	mapHandle = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		0,
		buffer_global::bufName
	);

	return mapHandle != 0;
}

void* ipc::map() {
	buffer = MapViewOfFile(
		mapHandle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		buffer_global::BUF_SIZE
	);

	return buffer;
}

int8_t ipc::unmap() {
	bool nUnmapped = UnmapViewOfFile(buffer) == 0;
	bool nClosed = CloseHandle(mapHandle) == 0;

	return nUnmapped | (nClosed << 1);
}