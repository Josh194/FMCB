#include "fmcb_Register.h"

#include "register/Register.h"

JNIEXPORT jboolean JNICALL Java_fmcb_Register_initialize(JNIEnv* env, jclass obj, jstring name) {
    const char* str = env -> GetStringUTFChars(name, 0);

    bool initialized = registration::initialize(str, env -> GetStringUTFLength(name)); // ? Does GetStringUTFLength() include the null terminator? If so, this function will fail when using the max allowed characters.

    env -> ReleaseStringUTFChars(name, str);

	return initialized;
}

JNIEXPORT jbyte JNICALL Java_fmcb_Register_request(JNIEnv* env, jclass obj) {
	return registration::request();
}