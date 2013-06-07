// CTPTRADEDLL.cpp : Defines the exported functions for the DLL application.
//


#include "nativeinterfaces_TradingNativeInterface.h"
#include "globals.h"
#include "TraderSingletonImpl.cpp"

using namespace std;
static JavaVM * cachedJvm;
HANDLE g_hEvent = CreateEvent(NULL, true, false, NULL);
int iNextOrderRef = 0;

list<jobject> observers;

// CThostFtdcMdApi *pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
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
		printf("returning from login request");
		//traderInstance -> Release();

}

JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_sendTradeRequest
  (JNIEnv *env, jobject callerObject, jstring brokerId, jstring password, jstring investorId, jobject tradeRequest){





	  		
			CThostFtdcInputOrderField orderField;
			memset(&orderField,0,sizeof(orderField));

			printf("getting class for TradeRequest\n");
			jclass cls = env->GetObjectClass(tradeRequest);

			printf("getting method ID's 1 -5\n");
			jmethodID m_autoSuspendId = env->GetMethodID(cls, "getAutoSuspend", "()I");
			jmethodID m_brokerId = env->GetMethodID(cls, "getBrokerID", "()Ljava/lang/String;");
			jmethodID m_businessUnitId = env->GetMethodID(cls, "getBusinessUnit", "()Ljava/lang/String;");
			jmethodID m_combHedgeFlagId = env->GetMethodID(cls, "getCombHedgeFlag", "()Ljava/lang/String;");
			jmethodID m_combOffsetId = env->GetMethodID(cls, "getCombOffsetFlag", "()Ljava/lang/String;");

			printf("getting method ID's 6 - 10\n");
			jmethodID m_contingentConditionId = env->GetMethodID(cls, "getContingentCondition", "()Ljava/lang/String;");
			jmethodID m_directionId = env->GetMethodID(cls, "getDirection", "()Ljava/lang/String;");
			jmethodID m_forceCloseReasonId = env->GetMethodID(cls, "getForceCloseReason", "()Ljava/lang/String;");
			jmethodID m_gtdDateId = env->GetMethodID(cls, "getGtdDate", "()Ljava/lang/String;");
			jmethodID m_instrumentIDId = env->GetMethodID(cls, "getInstrumentID", "()Ljava/lang/String;");

			printf("getting method ID's 11 - 15\n");
			jmethodID m_investorIDId = env->GetMethodID(cls, "getInvestorID", "()Ljava/lang/String;");
			jmethodID m_limitPriceId = env->GetMethodID(cls, "getLimitPrice", "()D");
			jmethodID m_minVolumeId = env->GetMethodID(cls, "getMinVolume", "()I");
			jmethodID m_orderPriceTypeId = env->GetMethodID(cls, "getOrderPriceType", "()Ljava/lang/String;");
			jmethodID m_orderRefId = env->GetMethodID(cls, "getOrderRef", "()Ljava/lang/String;");

			printf("getting method ID's 16 - 20\n");
			jmethodID m_requestIDId = env->GetMethodID(cls, "getRequestID", "()I");
			jmethodID m_stopPriceId = env->GetMethodID(cls, "getStopPrice", "()D");
			jmethodID m_swapOrderId = env->GetMethodID(cls, "getSwapOrder", "()I");
			jmethodID m_timeConditionId = env->GetMethodID(cls, "getTimeCondition", "()Ljava/lang/String;");
			jmethodID m_userForceCloseId = env->GetMethodID(cls, "getUserForceClose", "()I");

			printf("getting method ID's 21 - 23\n");
			jmethodID m_userIDId = env->GetMethodID(cls, "getUserID", "()Ljava/lang/String;");
			jmethodID m_volumeConditionId = env->GetMethodID(cls, "getVolumeCondition", "()Ljava/lang/String;");
			jmethodID m_volumeTotalOriginal = env->GetMethodID(cls, "getVolumeTotalOriginal", "()I");

			printf("creating jstrings 1 - 5\n");
			jstring j_brokerId = (jstring)env->CallObjectMethod(tradeRequest, m_brokerId, 0);
			const char *c_brokerID = env->GetStringUTFChars(j_brokerId, false);
			
			jstring j_businessUnit = (jstring)env->CallObjectMethod(tradeRequest, m_businessUnitId, 0);
			const char *c_businessUnit = env->GetStringUTFChars(j_businessUnit, false);
			
			jstring j_combHedgeFlag = (jstring)env->CallObjectMethod(tradeRequest, m_combHedgeFlagId, 0);
			const char *c_CombHedgeFlag = env->GetStringUTFChars(j_combHedgeFlag, false);

			jstring j_combOffsetFlag = (jstring)env->CallObjectMethod(tradeRequest, m_combOffsetId, 0);
			const char *c_combOffsetFlag = env->GetStringUTFChars(j_combOffsetFlag, false);
			
			jstring j_contingentCondition = (jstring)env->CallObjectMethod(tradeRequest, m_contingentConditionId, 0);
			const char *c_contingentCondition = env->GetStringUTFChars(j_contingentCondition, false);
			
			printf("creating jstrings 6 - 10\n");
			jstring j_direction = (jstring)env->CallObjectMethod(tradeRequest, m_directionId, 0);
			const char *c_direction = env->GetStringUTFChars(j_direction, false);
			
			jstring j_forceCloseReason = (jstring)env->CallObjectMethod(tradeRequest, m_forceCloseReasonId, 0);
			const char *c_forceCloseReason = env->GetStringUTFChars(j_forceCloseReason, false);

			jstring j_gtdDate = (jstring)env->CallObjectMethod(tradeRequest, m_gtdDateId, 0);
			const char *c_gtdDate = env -> GetStringUTFChars(j_gtdDate, false);

			jstring j_instrumentID = (jstring)env->CallObjectMethod(tradeRequest, m_instrumentIDId, 0);
			const char *c_instrumentId = env -> GetStringUTFChars(j_instrumentID, false);

			jstring j_investorId = (jstring)env->CallObjectMethod(tradeRequest, m_investorIDId, 0);
			const char *c_investorId = env->GetStringUTFChars(j_investorId, false);

			printf("creating jstrings 11- 15\n");
			printf("     orderPriceType\n");
			jstring j_orderPriceType = (jstring)env->CallObjectMethod(tradeRequest, m_orderPriceTypeId, 0);
			const char *c_orderPriceType = env->GetStringUTFChars(j_orderPriceType, false);
			printf("     orderRef\n");
			jstring j_orderRef = (jstring)env->CallObjectMethod(tradeRequest, m_orderRefId, 0);
			const char *c_orderRef = env->GetStringUTFChars(j_orderRef, false);
			printf("     timeCondition\n");
			jstring j_timeCondition = (jstring)env->CallObjectMethod(tradeRequest, m_timeConditionId, 0);
			const char *c_timeCondition = env->GetStringUTFChars(j_timeCondition, false);
			printf("     userId\n");
			jstring j_userID = (jstring)env->CallObjectMethod(tradeRequest, m_userIDId, 0);
			const char *c_userID = env->GetStringUTFChars(j_userID, false);
			printf("     volumeCondition\n");
			jstring j_volumeCondition = (jstring)env->CallObjectMethod(tradeRequest, m_volumeConditionId, 0);
			const char *c_volumeCondition = env->GetStringUTFChars(j_volumeCondition, false);

			strcpy_s(orderField.UserID, env->GetStringUTFChars(investorId, false));
			strcpy_s(orderField.InvestorID, env->GetStringUTFChars(investorId, false));
			strcpy_s(orderField.BrokerID, env->GetStringUTFChars(brokerId, false));
			strcpy_s(orderField.InstrumentID, c_instrumentId);
			strcpy_s(orderField.OrderRef, "000000000001");
			
			printf("invoking getters 1-5\n");
			orderField.Direction = c_direction[0];
			orderField.OrderPriceType = c_orderPriceType[0];
			strcpy_s(orderField.CombOffsetFlag, c_combOffsetFlag);
			strcpy_s(orderField.CombHedgeFlag, c_CombHedgeFlag);
			orderField.LimitPrice = env->CallDoubleMethod(tradeRequest, m_limitPriceId); 

			printf("invoking getters 6-10\n");
			strcpy_s(orderField.GTDDate, c_gtdDate);
			orderField.VolumeCondition = c_volumeCondition[0];
			orderField.MinVolume = env->CallIntMethod(tradeRequest, m_minVolumeId);
			orderField.ContingentCondition = c_contingentCondition[0];
			orderField.StopPrice = env->CallDoubleMethod(tradeRequest, m_stopPriceId);

			printf("invoking getters 11 - 14\n");
			orderField.ForceCloseReason = c_forceCloseReason[0];
			orderField.IsAutoSuspend = env->CallIntMethod(tradeRequest, m_autoSuspendId);
			orderField.VolumeTotalOriginal = env->CallIntMethod(tradeRequest, m_volumeTotalOriginal);
			orderField.TimeCondition = c_timeCondition[0];

			printf("Direction: %c\n", orderField.Direction);
			printf("OrderPriceType: %c\n", orderField.OrderPriceType);
			printf("CombOffsetFlag: %s\n", orderField.CombOffsetFlag);
			printf("LimitPrice: %f\n", orderField.LimitPrice);
			printf("GtdDate: %s\n", orderField.GTDDate);
			printf("VolumeCondition: %c\n", orderField.VolumeCondition);
			printf("MinVolume: %i\n", orderField.MinVolume);
			printf("ContingentCondition %c\n", orderField.ContingentCondition);
			printf("StopPrice %f\n", orderField.StopPrice);
			printf("ForceCloseReason %c\n", orderField.ForceCloseReason);
			printf("AutoSuspend: %i\n", orderField.IsAutoSuspend);
			printf("VolumeTotalOriginal: %i\n", orderField.VolumeTotalOriginal);
			printf("TimeCondition: %c\n", orderField.TimeCondition);
			printf("InstrumentID: %s\n", orderField.InstrumentID);

			traderInstance->ReqOrderInsert(&orderField, 1);
			env->DeleteLocalRef(j_brokerId);
			env->ReleaseStringUTFChars(j_brokerId, c_brokerID);
			env->DeleteLocalRef(j_businessUnit);
			env->ReleaseStringUTFChars(j_businessUnit, c_businessUnit);
			env->DeleteLocalRef(j_combHedgeFlag);
			env->ReleaseStringUTFChars(j_combHedgeFlag, c_CombHedgeFlag);
			env->DeleteLocalRef(j_combOffsetFlag);
			env->ReleaseStringUTFChars(j_combOffsetFlag, c_combOffsetFlag);
			env->DeleteLocalRef(j_contingentCondition);
			env->ReleaseStringUTFChars(j_contingentCondition, c_contingentCondition);
			env->DeleteLocalRef(j_direction);
			env->ReleaseStringUTFChars(j_direction, c_direction);
			env->DeleteLocalRef(j_forceCloseReason);
			env->ReleaseStringUTFChars(j_forceCloseReason, c_forceCloseReason);
			env->DeleteLocalRef(j_gtdDate);
			env->ReleaseStringUTFChars(j_gtdDate, c_gtdDate);
			env->DeleteLocalRef(j_instrumentID);
			env->ReleaseStringUTFChars(j_instrumentID, c_instrumentId);
			env->DeleteLocalRef(j_investorId);
			env->ReleaseStringUTFChars(j_investorId, c_investorId);
			env->DeleteLocalRef(j_orderPriceType);
			env->ReleaseStringUTFChars(j_orderPriceType, c_orderPriceType);
			env->DeleteLocalRef(j_orderRef);
			env->ReleaseStringUTFChars(j_orderRef, c_orderRef);
			env->DeleteLocalRef(j_timeCondition);
			env->ReleaseStringUTFChars(j_timeCondition, c_timeCondition);
			env->DeleteLocalRef(j_userID);
			env->ReleaseStringUTFChars(j_userID, c_userID);
			env->DeleteLocalRef(j_volumeCondition);
			env->ReleaseStringUTFChars(j_volumeCondition, c_volumeCondition);
			printf("sending trade request");
	  
}

JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_sendOrderAction
  (JNIEnv *env, jobject callerObject, jstring brokerId, jstring password, jstring investorId, jobject orderActionRequest){
	  printf("order action!\n");
	  CThostFtdcInputOrderActionField orderActionField;
	  memset(&orderActionField,0,sizeof(orderActionField));

	  printf("getting class for OrderActionRequest\n");
	  jclass cls = env->GetObjectClass(orderActionRequest);

	  printf("getting method ID's 1 -5\n");
	  jmethodID m_actionFlagId = env->GetMethodID(cls, "getActionFlag", "()Ljava/lang/String;");
	  jmethodID m_brokerIDId = env->GetMethodID(cls, "getBrokerID", "()Ljava/lang/String;");
	  jmethodID m_exchangeIDId = env->GetMethodID(cls, "getExchangeID", "()Ljava/lang/String;");
	  jmethodID m_frontIDId = env->GetMethodID(cls, "getFrontID", "()I");
	  jmethodID m_instrumentIDId = env->GetMethodID(cls, "getInstrumentID", "()Ljava/lang/String;");

	  printf("getting method ID's 6 - 10\n");
	  jmethodID m_investorId = env->GetMethodID(cls, "getInvestorID", "()Ljava/lang/String;");
	  jmethodID m_limitPriceId = env->GetMethodID(cls, "getLimitPrice", "()D");
	  jmethodID m_orderActionRefId = env->GetMethodID(cls, "getOrderActionRef", "()I");
	  jmethodID m_orderRefId = env->GetMethodID(cls, "getOrderRef", "()Ljava/lang/String;");
	  jmethodID m_orderSysIDId = env->GetMethodID(cls, "getOrderSysID", "()Ljava/lang/String;");

	  printf("getting method ID's 11 - 14\n");
	  jmethodID m_requestId = env->GetMethodID(cls, "getRequestID", "()I");
	  jmethodID m_sessionIDId = env->GetMethodID(cls, "getSessionID", "()I");
	  jmethodID m_userIDId = env->GetMethodID(cls, "getUserID", "()Ljava/lang/String;");
	  jmethodID m_volumeChangeId = env->GetMethodID(cls, "getVolumeChange", "()I");

	  printf("creating jstrings 1 - 5\n");
	  printf("     1\n");
	  jstring j_actionFlag = (jstring)env->CallObjectMethod(orderActionRequest, m_actionFlagId, 0);
	  const char *c_actionFlag = env->GetStringUTFChars(j_actionFlag, false);
	  printf("     2\n");
	  jstring j_brokerId = (jstring)env->CallObjectMethod(orderActionRequest, m_brokerIDId, 0);
	  const char *c_brokerId = env->GetStringUTFChars(j_brokerId, false);
	  printf("     3\n");
	  jstring j_exchangeID = (jstring)env->CallObjectMethod(orderActionRequest, m_exchangeIDId, 0);
	  const char *c_exchangeID = env->GetStringUTFChars(j_exchangeID, false);
	  printf("     4\n");
	  jstring j_instrumentID = (jstring)env->CallObjectMethod(orderActionRequest, m_instrumentIDId, 0);
	  const char *c_instrumentID = env->GetStringUTFChars(j_instrumentID, false);
	  
	  jstring j_investorID = (jstring)env->CallObjectMethod(orderActionRequest, m_investorId, 0);
	  const char *c_investorID = env->GetStringUTFChars(j_investorID, false);
	  printf("     5\n");
	  printf("creating jstrings 6 - 9\n");
	  jstring j_orderRef = (jstring)env->CallObjectMethod(orderActionRequest, m_orderRefId, 0);
	  const char *c_orderRef = env->GetStringUTFChars(j_orderRef, false);

	  jstring j_orderSysID = (jstring)env->CallObjectMethod(orderActionRequest, m_orderSysIDId, 0);
	  const char *c_orderSysID = env->GetStringUTFChars(j_orderSysID, false);

	  jstring j_userID = (jstring)env->CallObjectMethod(orderActionRequest, m_userIDId, 0);
	  const char *c_userID = env->GetStringUTFChars(j_userID, false);

	  printf("invoking getters 1 - 5\n");
	  orderActionField.ActionFlag = c_actionFlag[0];
	  strcpy_s(orderActionField.BrokerID, c_brokerId);
	  strcpy_s(orderActionField.ExchangeID, c_exchangeID);
	  orderActionField.FrontID = env->CallIntMethod(orderActionRequest, m_frontIDId);
	  strcpy_s(orderActionField.InstrumentID, c_instrumentID);

	  printf("invoking getters 6 - 10\n)");
	  strcpy_s(orderActionField.InvestorID, c_investorID);
	  orderActionField.LimitPrice = env->CallDoubleMethod(orderActionRequest, m_limitPriceId);
	  orderActionField.OrderActionRef = env->CallIntMethod(orderActionRequest, m_orderActionRefId);
	  strcpy_s(orderActionField.OrderRef, c_orderRef);
	  strcpy_s(orderActionField.OrderSysID, c_orderSysID);

	  printf("invoking getters 11 - 14\n");
	  orderActionField.RequestID = env->CallIntMethod(orderActionRequest, m_requestId);
	  orderActionField.SessionID = env->CallIntMethod(orderActionRequest, m_sessionIDId);
	  strcpy_s(orderActionField.UserID, c_userID);
	  orderActionField.VolumeChange = env -> CallIntMethod(orderActionRequest, m_volumeChangeId);

	  printf("sending action request\n");
	  traderInstance ->ReqOrderAction(&orderActionField, orderActionField.RequestID);

	  env->DeleteLocalRef(j_actionFlag);
	  env->ReleaseStringUTFChars(j_actionFlag, c_actionFlag);
	  env->DeleteLocalRef(j_brokerId);
	  env->ReleaseStringUTFChars(j_brokerId, c_brokerId);
	  env->DeleteLocalRef(j_exchangeID);
	  env->ReleaseStringUTFChars(j_exchangeID, c_exchangeID);
	  env->DeleteLocalRef(j_instrumentID);
	  env->ReleaseStringUTFChars(j_instrumentID, c_instrumentID);
	  env->DeleteLocalRef(j_investorID);
	  env->ReleaseStringUTFChars(j_investorID, c_investorID);
	  env->DeleteLocalRef(j_orderRef);
	  env->ReleaseStringUTFChars(j_orderRef, c_orderRef);
	  env->DeleteLocalRef(j_orderSysID);
	  env->ReleaseStringUTFChars(j_orderSysID, c_orderSysID);
	  env->DeleteLocalRef(j_userID);
	  env->ReleaseStringUTFChars(j_userID, c_userID);
}

JNIEXPORT void JNICALL Java_nativeinterfaces_TradingNativeInterface_sendSettlementReqest
  (JNIEnv *env, jobject callerObject, jstring brokerID, jstring userID){
		CThostFtdcSettlementInfoConfirmField settlement;
		memset(&settlement,0,sizeof(settlement));
		const char *c_brokerID = env->GetStringUTFChars(brokerID, false);
		const char *c_userID = env->GetStringUTFChars(userID, false);
		strcpy_s(settlement.BrokerID,c_brokerID);
		strcpy_s(settlement.InvestorID, c_userID);
		traderInstance->ReqSettlementInfoConfirm(&settlement, 0);
		env->ReleaseStringUTFChars(brokerID, c_brokerID);
		env->ReleaseStringUTFChars(userID, c_userID);
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

