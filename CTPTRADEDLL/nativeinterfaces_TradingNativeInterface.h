/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class nativeinterfaces_TradingNativeInterface */

#ifndef _Included_nativeinterfaces_TradingNativeInterface
#define _Included_nativeinterfaces_TradingNativeInterface
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     nativeinterfaces_TradingNativeInterface
 * Method:    sendLoginMessage
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_sendLoginMessage
  (JNIEnv *, jobject, jstring, jstring, jstring);

/*
 * Class:     nativeinterfaces_TradingNativeInterface
 * Method:    sendTradeRequest
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Lbo/TradeRequest;)V
 */
JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_sendTradeRequest
  (JNIEnv *, jobject, jstring, jstring, jstring, jobject);

/*
 * Class:     nativeinterfaces_TradingNativeInterface
 * Method:    sendOrderAction
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Lbo/OrderActionRequest;)V
 */
JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_sendOrderAction
  (JNIEnv *, jobject, jstring, jstring, jstring, jobject);

/*
 * Class:     nativeinterfaces_TradingNativeInterface
 * Method:    subscribeListener
 * Signature: (Llisteners/DefaultCTPListener;)V
 */
JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_subscribeListener
  (JNIEnv *, jobject, jobject);

/*
 * Class:     nativeinterfaces_TradingNativeInterface
 * Method:    unSubscribeListener
 * Signature: (Llisteners/DefaultCTPListener;)V
 */
JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_unSubscribeListener
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
