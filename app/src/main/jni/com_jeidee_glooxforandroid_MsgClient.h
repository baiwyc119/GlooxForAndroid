/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_jeidee_glooxforandroid_MsgClient */

#ifndef _Included_com_jeidee_glooxforandroid_MsgClient
#define _Included_com_jeidee_glooxforandroid_MsgClient
#ifdef __cplusplus
extern "C" {
#endif
#undef com_jeidee_glooxforandroid_MsgClient_MIN_PRIORITY
#define com_jeidee_glooxforandroid_MsgClient_MIN_PRIORITY 1L
#undef com_jeidee_glooxforandroid_MsgClient_NORM_PRIORITY
#define com_jeidee_glooxforandroid_MsgClient_NORM_PRIORITY 5L
#undef com_jeidee_glooxforandroid_MsgClient_MAX_PRIORITY
#define com_jeidee_glooxforandroid_MsgClient_MAX_PRIORITY 10L
/*
 * Class:     com_jeidee_glooxforandroid_MsgClient
 * Method:    _newInstance
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_jeidee_glooxforandroid_MsgClient__1newInstance
  (JNIEnv *, jobject);

/*
 * Class:     com_jeidee_glooxforandroid_MsgClient
 * Method:    _setLoginInfo
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_jeidee_glooxforandroid_MsgClient__1setLoginInfo
  (JNIEnv *, jobject, jlong, jstring, jstring, jstring, jint);

/*
 * Class:     com_jeidee_glooxforandroid_MsgClient
 * Method:    _connect
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_jeidee_glooxforandroid_MsgClient__1connect
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_jeidee_glooxforandroid_MsgClient
 * Method:    _disConnect
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_jeidee_glooxforandroid_MsgClient__1disConnect
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_jeidee_glooxforandroid_MsgClient
 * Method:    _recv
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_jeidee_glooxforandroid_MsgClient__1recv
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_jeidee_glooxforandroid_MsgClient
 * Method:    _deleteInstance
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_jeidee_glooxforandroid_MsgClient__1deleteInstance
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
