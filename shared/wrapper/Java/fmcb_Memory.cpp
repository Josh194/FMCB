#include "fmcb_Memory.h"

#include <memory/BufferAccess.h>
#include <Global.h>

JNIEXPORT jobject JNICALL Java_fmcb_Memory_mapBuffer(JNIEnv* env, jclass obj) {
	return env -> NewDirectByteBuffer(communication::map(), api_global::bufferSize);
}

JNIEXPORT jbyte JNICALL Java_fmcb_Memory_unmapBuffer(JNIEnv* env, jclass obj) {
	return communication::unmap();
}