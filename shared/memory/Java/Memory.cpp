#include "Memory.h"

#include <BufferAccess.h>
#include <Global.h>

JNIEXPORT jboolean JNICALL Java_fmcb_memory_Memory_openBuffer(JNIEnv* env, jclass obj) {
	return ipc::open();
}

JNIEXPORT jobject JNICALL Java_fmcb_memory_Memory_mapBuffer(JNIEnv* env, jclass obj) {
	return env -> NewDirectByteBuffer(ipc::map(), buffer_global::BUF_SIZE);
}

JNIEXPORT jbyte JNICALL Java_fmcb_memory_Memory_unmapBuffer(JNIEnv* env, jclass obj) {
	return ipc::unmap();
}