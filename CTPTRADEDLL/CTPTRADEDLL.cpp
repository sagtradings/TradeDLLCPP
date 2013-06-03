// CTPTRADEDLL.cpp : Defines the exported functions for the DLL application.
//


#include "nativeinterfaces_TradingNativeInterface.h"
#include "globals.h"
#include "TraderSingletonImpl.cpp"

using namespace std;
static JavaVM * cachedJvm;
HANDLE g_hEvent = CreateEvent(NULL, true, false, NULL);


list<jobject> observers;

 CThostFtdcMdApi *pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
 CThostFtdcTraderApi *traderInstance = CThostFtdcTraderApi::CreateFtdcTraderApi();
 TraderEventHandler th(traderInstance);


JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_sendLoginMessage
  (JNIEnv *env, jobject srcObject, jstring brokerId, jstring password, jstring investorId){

		
		
		traderInstance->RegisterSpi(&th);
		traderInstance ->RegisterFront("tcp://218.1.96.8:41205");
		traderInstance->SubscribePrivateTopic(THOST_TERT_RESUME);
		traderInstance->SubscribePublicTopic(THOST_TERT_RESUME);
		traderInstance -> Init();
		WaitForSingleObject(g_hEvent, INFINITE);
		ResetEvent(g_hEvent);
		CThostFtdcReqUserLoginField reqUserLogin;
		//const char  *userID2 = "00000008";
		//const char  *password2 = "123321";
		//const char  *brokerID2 = "1013";
		//strcpy_s(reqUserLogin.UserID, userID2);
		//strcpy_s(reqUserLogin.Password, password2);
		//strcpy_s(reqUserLogin.BrokerID,brokerID2);
		
		strcpy_s(reqUserLogin.UserID, env->GetStringUTFChars(investorId, false));
		strcpy_s(reqUserLogin.Password, env->GetStringUTFChars(password, false));
		strcpy_s(reqUserLogin.BrokerID, env->GetStringUTFChars(brokerId, false));

		

		traderInstance->ReqUserLogin(&reqUserLogin, 0);
		printf("Login sent successfully");
		WaitForSingleObject(g_hEvent, INFINITE);
		ResetEvent(g_hEvent);
		//traderInstance -> Release();

}

JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_sendTradeRequest
  (JNIEnv *env, jobject callerObject, jstring brokerId, jstring password, jstring investorId, jobject tradeRequest){





	  		const char * instrument = "IF1307";
			CThostFtdcInputOrderField orderField;
			memset(&orderField,0,sizeof(orderField));

			strcpy_s(orderField.UserID, env->GetStringUTFChars(investorId, false));
			strcpy_s(orderField.InvestorID, env->GetStringUTFChars(investorId, false));
			strcpy_s(orderField.BrokerID, env->GetStringUTFChars(brokerId, false));
			strcpy_s(orderField.InstrumentID, instrument);
			strcpy_s(orderField.OrderRef, "000000000001");
			orderField.Direction = THOST_FTDC_D_Sell;
			orderField.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
			//orderField.Direction = THOST_FTDC_D_Buy;
			strcpy_s(orderField.CombOffsetFlag, "0");
			strcpy_s(orderField.CombHedgeFlag, "1");
			orderField.LimitPrice = 2600; 
			strcpy_s(orderField.GTDDate, "");
			orderField.VolumeCondition = THOST_FTDC_VC_AV;
			orderField.MinVolume = 0;
			orderField.ContingentCondition = THOST_FTDC_CC_Immediately;
			orderField.StopPrice = 0;
			orderField.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
			orderField.IsAutoSuspend = 0;
			orderField.VolumeTotalOriginal = 10;
			orderField.TimeCondition = THOST_FTDC_TC_GFD;
			traderInstance->ReqOrderInsert(&orderField, 1);
			printf("sending trade request");
			WaitForSingleObject(g_hEvent, INFINITE);
	  
}

JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_sendOrderAction
  (JNIEnv *env, jobject callerObject, jstring brokerId, jstring password, jstring investorId, jobject OrderActionRequest){
	  printf("order action!");


}

JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_subscribeListener
  (JNIEnv *env, jobject callerObject, jobject subscriber){
	jobject o = env->NewGlobalRef(subscriber);
	observers.push_back(o);
}

JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_unSubscribeListener
  (JNIEnv *env, jobject caller, jobject subscriber){

}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved){
	cachedJvm = jvm;
	//printf("JVM on load");
	return JNI_VERSION_1_6;

}

