#include "BufferAccess.h"

#include "Global.h"

#include <Windows.h>

LPVOID buffer;

void* communication::map() {
	buffer = MapViewOfFile(
		api_global::fileHandle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		api_global::bufferSize
	);

	return buffer;
}

char communication::unmap() {
	bool nUnmapped = UnmapViewOfFile(buffer) == 0;
	bool nClosed = CloseHandle(api_global::fileHandle) == 0;

	return nUnmapped | (nClosed << 1); // ? Is this working correctly?
}