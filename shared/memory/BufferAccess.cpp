#include "BufferAccess.h"

#include "Global.h"

#include <windows.h>

HANDLE mapHandle;
LPVOID buffer;

inline bool ipc::create() {
	mapHandle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		0,
		PAGE_READWRITE,
		HIDWORD(buffer_global::BUF_SIZE),
		LODWORD(buffer_global::BUF_SIZE),
		buffer_global::bufName
	);

	return mapHandle != NULL;
}

inline bool ipc::open() {
	mapHandle = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		0,
		buffer_global::bufName
	);

	return mapHandle != NULL;
}

inline void* ipc::map() {
	buffer = MapViewOfFile(
		mapHandle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		buffer_global::BUF_SIZE
	);

	return buffer;
}

/*
* Attempts to close the file mapping handle even if unable to unmap the file to avoid complicating the close process.
*/
inline int8_t ipc::unmap() {
	bool nUnmapped = UnmapViewOfFile(buffer) == NULL;
	bool nClosed = CloseHandle(mapHandle) == NULL;

	return nUnmapped | (nClosed << 1);
}