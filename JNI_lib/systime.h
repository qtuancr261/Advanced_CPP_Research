#include <jni.h>

#ifndef _SYSTIME_H_
#define _SYSTIME_H_
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     
 * Method:    setTime
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_jzcommon_corelib_MainApp_setTime
  (JNIEnv *, jobject, jint, jint, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
