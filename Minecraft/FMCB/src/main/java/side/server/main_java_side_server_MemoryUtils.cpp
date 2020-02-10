#define BUF_SIZE 256

#include <jni.h>
#include <windows.h>

HANDLE hMapFile;
LPVOID pBuf;

JNIEXPORT void JNICALL Java_main_java_side_server_MemoryUtils_createBuffer(JNIEnv* env, jclass thisClass) {
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,	// use paging file
		NULL,			// default security
  		PAGE_READWRITE,		// read/write access
		0,			// maximum object size (high-order DWORD)
		BUF_SIZE,		// maximum object size (low-order DWORD)
		"Local\\FMCBuffer");		// name of mapping object
}

JNIEXPORT void JNICALL Java_main_java_side_server_MemoryUtils_closeBuffer(JNIEnv* env, jclass thisClass) {
	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);
}

JNIEXPORT jobject JNICALL Java_main_java_side_server_MemoryUtils_mapBuffer(JNIEnv* env, jclass thisClass) {
	pBuf = (LPTSTR) MapViewOfFile(hMapFile,	// handle to map object
		FILE_MAP_ALL_ACCESS,		// read/write permission
		0,				// file offset (high-order DWORD)
		0,				// file offset (low-order DWORD)
		BUF_SIZE);			// number of bytes to map

	return env -> NewDirectByteBuffer(pBuf, BUF_SIZE);
}