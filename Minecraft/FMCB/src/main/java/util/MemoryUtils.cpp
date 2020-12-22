#include "MemoryUtils.h"

#include <BufferAccess.h>
#include <Global.h>

JNIEXPORT jboolean JNICALL Java_main_java_util_MemoryUtils_openBuffer(JNIEnv* env, jclass obj) {
	return ipc::open();
}

JNIEXPORT jobject JNICALL Java_main_java_util_MemoryUtils_mapBuffer(JNIEnv* env, jclass obj) {
	return env -> NewDirectByteBuffer(ipc::map(), buffer_global::BUF_SIZE);
}

JNIEXPORT jbyte JNICALL Java_main_java_util_MemoryUtils_unmapBuffer(JNIEnv* env, jclass obj) {
	return ipc::unmap();
}