#include <errno.h>
#include <stdlib.h>
#include <jni.h>
#include <unistd.h>

static char** getStringArray(JNIEnv* env, jobjectArray array) {
	int length = (*env)->GetArrayLength(env, array);
	char** native = (char**)malloc(sizeof(char*) * (length + 1));
	for (int i = 0; i < length; ++i) {
		jstring str = (jstring)((*env)->GetObjectArrayElement(env, array, i));
		char* raw = (char*)((*env)->GetStringUTFChars(env, str, 0));
		native[i] = raw;
	}
	native[length] = NULL;
	return native;
}

static void destroyStringArray(JNIEnv* env, jobjectArray array,
		char** native) {
	int length = (*env)->GetArrayLength(env, array);
	for (int i = 0; i < length; ++i) {
		jstring str = (jstring)((*env)->GetObjectArrayElement(env, array, i));
		(*env)->ReleaseStringUTFChars(env, str, native[i]);
	}
	free(native);
}

JNIEXPORT jint JNICALL Java_com_huawei_NativeExec_execv(JNIEnv* env,
		jobject self, jstring path, jobjectArray argv) {
	const char* path_ = (*env)->GetStringUTFChars(env, path, 0);
	char** argv_ = getStringArray(env, argv);
	int r = execv(path_, argv_);
	(*env)->ReleaseStringUTFChars(env, path, path_);
	destroyStringArray(env, argv, argv_);
	return -errno;
}

JNIEXPORT jint JNICALL Java_com_huawei_NativeExec_execvp(JNIEnv* env,
		jobject self, jstring file, jobjectArray argv) {
	const char* file_ = (*env)->GetStringUTFChars(env, file, 0);
	char** argv_ = getStringArray(env, argv);
	int r = execvp(file_, argv_);
	(*env)->ReleaseStringUTFChars(env, file, file_);
	destroyStringArray(env, argv, argv_);
	return -errno;
}
