#include "globals.h"

class TraderEventHandler : public CThostFtdcTraderSpi{
		public:
		// constructor，which need a valid pointer to a CThostFtdcMduserApi instance
		TraderEventHandler() {}
		~TraderEventHandler() {}

		virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool isLast){
			printf("an error happened");
		}

		virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
			JNIEnv * g_env;
			jint success = cachedJvm -> GetEnv((void**)&g_env, JNI_VERSION_1_6);
			if(success != JNI_OK){
			//	printf("attempting to resync jvm to thread\n");
				jint attachSuccess = cachedJvm ->AttachCurrentThread((void**)&g_env, NULL);
				if(attachSuccess == 0){
					//printf("resync successful!\n");
				}
				else{
					//printf("resync unsuccessful\n");
					return;
				}
			}
			list<jobject>::iterator it = observers.begin();			
			while (it != observers.end()) {
				
				jobject &obj = *it;
				jclass cls = g_env->GetObjectClass(obj);
				jmethodID mid = g_env->GetMethodID(cls, "onOrderActionResponse", "(Lbo/OrderActionRequest;)V");

				jclass parameter = g_env->FindClass("bo/OrderActionRequest");
			    jmethodID midConstructor = (g_env)->GetMethodID(parameter, "<init>", "()V");
				jobject paramObject = (g_env)->NewObject(parameter, midConstructor);

				jmethodID m_actionFlagId = g_env->GetMethodID(parameter, "setActionFlag", "(Ljava/lang/String;)V");
				jmethodID m_brokerIDId = g_env->GetMethodID(parameter, "setBrokerID", "(Ljava/lang/String;)V");
				jmethodID m_exchangeIDId = g_env->GetMethodID(parameter, "setExchangeID", "(Ljava/lang/String;)V");
				jmethodID m_frontId = g_env->GetMethodID(parameter, "setFrontID", "(I)V");
				jmethodID m_instrumentIDId = g_env->GetMethodID(parameter, "setInstrumentID", "(Ljava/lang/String;)V");

				jmethodID m_investorIDId = g_env->GetMethodID(parameter, "setInvestorID", "(Ljava/lang/String;)V");
				jmethodID m_limitPriceId = g_env->GetMethodID(parameter, "setLimitPrice", "(D)V");
				jmethodID m_orderActionRefId = g_env->GetMethodID(parameter, "setOrderActionRef", "(I)V");
				jmethodID m_orderRefId = g_env->GetMethodID(parameter, "setOrderRef", "(Ljava/lang/String;)V");
				jmethodID m_orderSysIDId = g_env->GetMethodID(parameter, "setOrderSysID", "(Ljava/lang/String;)V");

				jmethodID m_requestIDId = g_env->GetMethodID(parameter, "setRequestID", "(I)V");
				jmethodID m_sessionIDId = g_env->GetMethodID(parameter, "setSessionID", "(I)V");
				jmethodID m_userIDId = g_env->GetMethodID(parameter, "setUserID", "(Ljava/lang/String;)V");
				jmethodID m_volumeChange = g_env->GetMethodID(parameter, "setVolumeChange", "(I)V");

				
				char *actionFlag = new char[2]();
				actionFlag[0] = pInputOrderAction->ActionFlag;
				actionFlag[1] = '\0'; 
				jstring j_actionFlag = g_env->NewStringUTF(actionFlag);
				delete(actionFlag);
				g_env->CallVoidMethod(paramObject, m_actionFlagId, j_actionFlag);

				jstring j_brokerID = g_env->NewStringUTF(pInputOrderAction->BrokerID);
				g_env->CallVoidMethod(paramObject, m_brokerIDId, j_brokerID);

				jstring j_exchangeID = g_env->NewStringUTF(pInputOrderAction->ExchangeID);
				g_env->CallVoidMethod(paramObject, m_exchangeIDId, j_exchangeID);

				g_env->CallVoidMethod(paramObject, m_frontId, pInputOrderAction ->FrontID);

				jstring j_instrumentID = g_env->NewStringUTF(pInputOrderAction->InstrumentID);
				g_env->CallVoidMethod(paramObject, m_instrumentIDId, j_instrumentID);
				
				jstring j_investorID = g_env->NewStringUTF(pInputOrderAction->InvestorID);
				g_env->CallVoidMethod(paramObject, m_investorIDId, j_investorID);
				g_env->CallVoidMethod(paramObject, m_limitPriceId, pInputOrderAction->LimitPrice);
				g_env->CallVoidMethod(paramObject, m_orderActionRefId, pInputOrderAction ->OrderActionRef);
				jstring j_orderRef = g_env->NewStringUTF(pInputOrderAction->OrderRef);
				g_env->CallVoidMethod(paramObject, m_orderRefId, j_orderRef);
				jstring j_orderSysID = g_env->NewStringUTF(pInputOrderAction->OrderSysID);
				g_env->CallVoidMethod(paramObject, m_orderSysIDId, j_orderSysID);

				g_env->CallVoidMethod(paramObject, m_requestIDId, pInputOrderAction->RequestID);
				g_env->CallVoidMethod(paramObject, m_sessionIDId, pInputOrderAction->SessionID);
				jstring j_userID = g_env->NewStringUTF(pInputOrderAction->UserID);
				g_env->CallVoidMethod(paramObject, m_userIDId, j_userID);
				g_env->CallVoidMethod(paramObject, m_volumeChange, pInputOrderAction->VolumeChange);

				if (mid == 0) {
					//printf("mid was 0!!!\n");mz
					return;
				}

				g_env->CallVoidMethod(obj, mid, paramObject);
				it++;

			}
		}

		virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {
			printf("OnErrRtnOrderAction\n");
		}

		virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
			JNIEnv * g_env;
			jint success = cachedJvm -> GetEnv((void**)&g_env, JNI_VERSION_1_6);
			if(success != JNI_OK){
			//	printf("attempting to resync jvm to thread\n");
				jint attachSuccess = cachedJvm ->AttachCurrentThread((void**)&g_env, NULL);
				if(attachSuccess == 0){
					//printf("resync successful!\n");
				}
				else{
					//printf("resync unsuccessful\n");
					return;
				}
			}
			list<jobject>::iterator it = observers.begin();			
			while (it != observers.end()) {
				
				jobject &obj = *it;
				jclass cls = g_env->GetObjectClass(obj);
				jmethodID mid = g_env->GetMethodID(cls, "onSettlementResponse", "(Lbo/SettlementResponse;)V");

				jclass parameter = g_env->FindClass("bo/SettlementResponse");
			    jmethodID midConstructor = (g_env)->GetMethodID(parameter, "<init>", "()V");
				jobject paramObject = (g_env)->NewObject(parameter, midConstructor);

				jmethodID brokerIDId = g_env->GetMethodID(parameter, "setBrokerID", "(Ljava/lang/String;)V");
				jmethodID confirmDateId = g_env->GetMethodID(parameter, "setConfirmDate", "(Ljava/lang/String;)V");
				jmethodID confirmTimeId = g_env->GetMethodID(parameter, "setConfirmDate", "(Ljava/lang/String;)V");
				jmethodID investorIDId = g_env->GetMethodID(parameter, "setInvestorID", "(Ljava/lang/String;)V");

				jstring j_brokerId = g_env->NewStringUTF(pSettlementInfoConfirm->BrokerID);
				g_env->CallVoidMethod(paramObject, brokerIDId, j_brokerId);
				jstring j_confirmDate = g_env->NewStringUTF(pSettlementInfoConfirm->ConfirmDate);
				g_env->CallVoidMethod(paramObject, brokerIDId, j_confirmDate);
				jstring j_confirmTime = g_env->NewStringUTF(pSettlementInfoConfirm->ConfirmTime);
				g_env->CallVoidMethod(paramObject, confirmTimeId, j_confirmTime);
				jstring j_investorID = g_env->NewStringUTF(pSettlementInfoConfirm->InvestorID);
				g_env->CallVoidMethod(paramObject, investorIDId, j_investorID);


				if (mid == 0) {
					//printf("mid was 0!!!\n");
					return;
				}

				g_env->CallVoidMethod(obj, mid, paramObject);
				it++;

			}
		}

		virtual void OnFrontConnected(){
			printf("the front is connected");
			SetEvent(g_hEvent);
		}

		virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){

			JNIEnv * g_env;
			jint success = cachedJvm -> GetEnv((void**)&g_env, JNI_VERSION_1_6);
			if(success != JNI_OK){
				printf("attempting to resync jvm to thread\n");
				jint attachSuccess = cachedJvm ->AttachCurrentThread((void**)&g_env, NULL);
				if(attachSuccess == 0){
					//printf("resync successful!\n");
				}
				else{
					//printf("resync unsuccessful\n");
					return;
				}
			}
			int maxOrderRev = atoi(pRspUserLogin->MaxOrderRef);

			jclass parameter = g_env->FindClass("bo/LoginResponse");
			jmethodID midConstructor = (g_env)->GetMethodID(parameter, "<init>", "()V");
			jobject paramObject = (g_env)->NewObject(parameter, midConstructor);
			jmethodID maxOrderId = g_env->GetMethodID(parameter, "setMaxOrder", "(I)V");

			g_env->CallVoidMethod(paramObject, maxOrderId, maxOrderRev + 1);

			list<jobject>::iterator it = observers.begin();			
			while (it != observers.end()) {
				jobject &obj = *it;
				jclass cls = g_env->GetObjectClass(obj);
				jmethodID mid = g_env->GetMethodID(cls, "onRspUserLogin", "(Lbo/LoginResponse;)V");
								g_env->CallVoidMethod(obj, mid, paramObject);
				it++;
			}
			SetEvent(g_hEvent);


			
		}

		virtual void OnRtnTrade(CThostFtdcTradeField *pTrade){
			printf("OnRtntrade\n");

			JNIEnv * g_env;
			jint success = cachedJvm -> GetEnv((void**)&g_env, JNI_VERSION_1_6);
			if(success != JNI_OK){
			//	printf("attempting to resync jvm to thread\n");
				jint attachSuccess = cachedJvm ->AttachCurrentThread((void**)&g_env, NULL);
				if(attachSuccess == 0){
					//printf("resync successful!\n");
				}
				else{
					//printf("resync unsuccessful\n");
					return;
				}
			}
			list<jobject>::iterator it = observers.begin();			
			while (it != observers.end()) {
				
				jobject &obj = *it;
				jclass cls = g_env->GetObjectClass(obj);
				jmethodID mid = g_env->GetMethodID(cls, "onRtnTradingData", "(Lbo/TradeDataResponse;)V");

				jclass parameter = g_env->FindClass("bo/TradeDataResponse");
			    jmethodID midConstructor = (g_env)->GetMethodID(parameter, "<init>", "()V");
				jobject paramObject = (g_env)->NewObject(parameter, midConstructor);

				jmethodID brokerIDId = g_env->GetMethodID(parameter, "setBrokerID", "(Ljava/lang/String;)V");
				jmethodID brokerSequenceIDId = g_env->GetMethodID(parameter, "setBrokerOrderSeq", "(I)V");
				jmethodID businessUnitId = g_env->GetMethodID(parameter, "setBusinessUnit", "(Ljava/lang/String;)V");
				jmethodID clearingPartIDId = g_env->GetMethodID(parameter, "setClearingPartID", "(Ljava/lang/String;)V");
				jmethodID clientIDId = g_env->GetMethodID(parameter, "setClientID", "(Ljava/lang/String;)V");

				jmethodID directionId = g_env->GetMethodID(parameter, "setDirection", "(Ljava/lang/String;)V");
				jmethodID exchangeIDId = g_env->GetMethodID(parameter, "setExchangeID", "(Ljava/lang/String;)V");
				jmethodID exchangeInstIDId = g_env->GetMethodID(parameter, "setExchangeInstID", "(Ljava/lang/String;)V");
				jmethodID hedgeFlagId = g_env->GetMethodID(parameter, "setHedgeFlag", "(Ljava/lang/String;)V");
				jmethodID instrumentIDId = g_env->GetMethodID(parameter, "setInstrumentID", "(Ljava/lang/String;)V");

				jmethodID investorIDId = g_env->GetMethodID(parameter, "setInvestorID", "(Ljava/lang/String;)V");
				jmethodID offsetFlagId = g_env->GetMethodID(parameter, "setOffsetFlag", "(Ljava/lang/String;)V");
				jmethodID orderLocalIDId = g_env->GetMethodID(parameter, "setOrderLocalID", "(Ljava/lang/String;)V");
				jmethodID orderRefId = g_env->GetMethodID(parameter, "setOrderRef", "(Ljava/lang/String;)V");
				jmethodID orderSysIDId = g_env->GetMethodID(parameter, "setOrderSysID", "(Ljava/lang/String;)V");

				jmethodID participantIDId = g_env->GetMethodID(parameter, "setParticipantID", "(Ljava/lang/String;)V");
				jmethodID priceId = g_env->GetMethodID(parameter, "setPrice", "(D)V");
				jmethodID priceSourceId = g_env->GetMethodID(parameter, "setPriceSource", "(Ljava/lang/String;)V");
				jmethodID sequenceNoId = g_env->GetMethodID(parameter, "setSequenceNo", "(I)V");
				jmethodID settlementIDId = g_env->GetMethodID(parameter, "setSettlementID", "(I)V");

				jmethodID tradeDateId = g_env->GetMethodID(parameter, "setTradeDate", "(Ljava/lang/String;)V");
				jmethodID tradeIDId = g_env->GetMethodID(parameter, "setTradeID", "(Ljava/lang/String;)V");
				jmethodID traderIDId = g_env->GetMethodID(parameter, "setTraderID", "(Ljava/lang/String;)V");
				jmethodID tradeSourceId = g_env->GetMethodID(parameter, "setTradeSource", "(Ljava/lang/String;)V");
				jmethodID tradeTimeId = g_env->GetMethodID(parameter, "setTradeTime", "(Ljava/lang/String;)V");

				jmethodID tradeTypeId = g_env->GetMethodID(parameter, "setTradeType", "(Ljava/lang/String;)V");
				jmethodID tradingDayId = g_env->GetMethodID(parameter, "setTradingDay", "(Ljava/lang/String;)V");
				jmethodID tradingRoldId = g_env->GetMethodID(parameter, "setTradingRole", "(Ljava/lang/String;)V");
				jmethodID userIDId = g_env->GetMethodID(parameter, "setUserID", "(Ljava/lang/String;)V");
				jmethodID volumeId = g_env->GetMethodID(parameter, "setVolume", "(I)V");

				jstring j_brokerId = g_env->NewStringUTF(pTrade->BrokerID);
				g_env->CallVoidMethod(paramObject, brokerIDId, j_brokerId);
				
				
				g_env->CallVoidMethod(paramObject, brokerSequenceIDId, pTrade->BrokerOrderSeq);
				
				jstring j_businessUnit = g_env->NewStringUTF(pTrade->BusinessUnit);
				g_env->CallVoidMethod(paramObject, businessUnitId, j_businessUnit);
				
				jstring j_clearingPartID = g_env->NewStringUTF(pTrade->ClearingPartID);
				g_env->CallVoidMethod(paramObject, clearingPartIDId, j_clearingPartID);
				
				jstring j_clientId = g_env->NewStringUTF(pTrade->ClientID);
				g_env->CallVoidMethod(paramObject, clientIDId, j_clientId);

				char* cp_direction = new char[2]();
				cp_direction[0] = pTrade->Direction;
				cp_direction[1] = '\0';				
				jstring j_direction = g_env->NewStringUTF(cp_direction);
				delete(cp_direction);
				g_env->CallVoidMethod(paramObject, directionId, j_direction);
				
				jstring j_exchangeID = g_env->NewStringUTF(pTrade->ExchangeID);
				g_env->CallVoidMethod(paramObject, exchangeIDId, j_exchangeID);
				
				jstring j_exchangeInstID = g_env->NewStringUTF(pTrade->ExchangeInstID);
				g_env->CallVoidMethod(paramObject, exchangeInstIDId, j_exchangeInstID);

				char* cp_hedgeFlag = new char[2]();
				cp_hedgeFlag[0] = pTrade->HedgeFlag;
				cp_hedgeFlag[1] = '\0';	
				jstring j_HedgeFlag = g_env->NewStringUTF(&pTrade->HedgeFlag);
				delete(cp_hedgeFlag);
				g_env->CallVoidMethod(paramObject, hedgeFlagId, j_HedgeFlag);

				jstring j_InstrumentID = g_env->NewStringUTF(pTrade->InstrumentID);
				g_env->CallVoidMethod(paramObject, instrumentIDId, j_InstrumentID);

				jstring j_InvestorID = g_env->NewStringUTF(pTrade->InvestorID);
				g_env->CallVoidMethod(paramObject, investorIDId, j_InvestorID);
				
				char* cp_offsetFlag = new char[2]();
				cp_offsetFlag[0] = pTrade->OffsetFlag;
				cp_offsetFlag[1] = '\0';	
				jstring j_OffsetFlag = g_env->NewStringUTF(cp_offsetFlag);
				g_env->CallVoidMethod(paramObject, offsetFlagId, j_OffsetFlag);
				delete(cp_offsetFlag);

				jstring j_OrderLocalID = g_env->NewStringUTF(pTrade->OrderLocalID);
				g_env->CallVoidMethod(paramObject, orderLocalIDId, j_OrderLocalID);

				jstring j_OrderRefId = g_env->NewStringUTF(pTrade->OrderRef);
				g_env->CallVoidMethod(paramObject, orderRefId, j_OrderRefId);

				jstring j_OrderSysID = g_env->NewStringUTF(pTrade->OrderSysID);
				g_env->CallVoidMethod(paramObject, orderSysIDId, j_OrderSysID);

				jstring j_ParticipantID = g_env->NewStringUTF(pTrade->ParticipantID);
				g_env->CallVoidMethod(paramObject, participantIDId, j_ParticipantID);
				g_env->CallVoidMethod(paramObject, priceId, pTrade->Price);

				char* cp_priceSource = new char[2]();
				cp_priceSource[0] = pTrade->PriceSource;
				cp_priceSource[1] = '\0';	
				jstring j_PriceSourceId = g_env->NewStringUTF(cp_priceSource);
				delete(cp_priceSource);
				g_env->CallVoidMethod(paramObject, priceSourceId, j_PriceSourceId);
				g_env->CallVoidMethod(paramObject, sequenceNoId, pTrade->SequenceNo);
				g_env->CallVoidMethod(paramObject, settlementIDId, pTrade->SettlementID);

				jstring j_TradeDateID = g_env->NewStringUTF(pTrade->TradeDate);
				g_env->CallVoidMethod(paramObject, tradeDateId, j_TradeDateID);

				jstring j_TradeID = g_env->NewStringUTF(pTrade->TradeID);
				g_env->CallVoidMethod(paramObject, tradeIDId, j_TradeID);

				jstring j_TraderID = g_env->NewStringUTF(pTrade->TraderID);
				g_env->CallVoidMethod(paramObject, traderIDId, j_TraderID);

				char* cp_tradeSource = new char[2]();
				cp_tradeSource[0] = pTrade->TradeSource;
				cp_tradeSource[1] = '\0';	
				jstring j_TradeSourceID = g_env->NewStringUTF(cp_tradeSource);
				delete(cp_tradeSource);
				g_env->CallVoidMethod(paramObject, tradeSourceId, j_TradeSourceID);

				jstring j_TradeTimeID = g_env->NewStringUTF(pTrade->TradeTime);
				g_env->CallVoidMethod(paramObject, tradeTimeId, j_TradeTimeID);

				char* cp_tradeType = new char[2]();
				cp_tradeType[0] = pTrade->TradeType;
				cp_tradeType[1] = '\0';	
				jstring j_TraderTypeID = g_env->NewStringUTF(&pTrade->TradeType);
				delete(cp_tradeType);
				g_env->CallVoidMethod(paramObject, tradeTypeId, j_TraderTypeID);

				jstring j_TradingDay = g_env->NewStringUTF(pTrade->TradingDay);
				g_env->CallVoidMethod(paramObject, tradingDayId, j_TradingDay);
				char* cp_tradeRole = new char[2]();
				cp_tradeRole[0] = pTrade->TradingRole;
				cp_tradeRole[1] = '\0';	
				jstring j_tradingRoleID = g_env->NewStringUTF(&pTrade->TradingRole); 
				delete(cp_tradeRole);
				g_env->CallVoidMethod(paramObject, tradingRoldId, j_tradingRoleID);

				jstring j_UserID = g_env->NewStringUTF(pTrade->UserID);
				g_env->CallVoidMethod(paramObject, userIDId, j_UserID);

				g_env->CallVoidMethod(paramObject, volumeId, pTrade->Volume);

				if (mid == 0) {
					//printf("mid was 0!!!\n");
					return;
				}

				g_env->CallVoidMethod(obj, mid, paramObject);
				it++;

			}
		}

		virtual void OnRspOrderInsert (CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
			printf("OnRspOrderInsert\n");
			printf("ErrorCode=[%d], ErrorMsg=[%s]\n",pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		}

		virtual void OnRtnOrder(CThostFtdcOrderField *pOrder){
			printf("OnRtnOrder\n");
			
			JNIEnv * g_env;
			jint success = cachedJvm -> GetEnv((void**)&g_env, JNI_VERSION_1_6);
			if(success != JNI_OK){
			//	printf("attempting to resync jvm to thread\n");
				jint attachSuccess = cachedJvm ->AttachCurrentThread((void**)&g_env, NULL);
				if(attachSuccess == 0){
					//printf("resync successful!\n");
				}
				else{
					//printf("resync unsuccessful\n");
					return;
				}
			}
			list<jobject>::iterator it = observers.begin();			
			while (it != observers.end()) {
				
				jobject &obj = *it;
				jclass cls = g_env->GetObjectClass(obj);
				jmethodID mid = g_env->GetMethodID(cls, "onRtnOrder", "(Lbo/OrderInsertResponse;)V");

				jclass parameter = g_env->FindClass("bo/OrderInsertResponse");
			    jmethodID midConstructor = (g_env)->GetMethodID(parameter, "<init>", "()V");
				jobject paramObject = (g_env)->NewObject(parameter, midConstructor);

				jmethodID activeTimeId = g_env->GetMethodID(parameter, "setActiveTime", "(Ljava/lang/String;)V");
				jmethodID activeTraderIDId = g_env->GetMethodID(parameter, "setActiveTraderID", "(Ljava/lang/String;)V");
				jmethodID activeUserIDId = g_env->GetMethodID(parameter, "setActiveUserID", "(Ljava/lang/String;)V");
				jmethodID autoSuspendId = g_env->GetMethodID(parameter, "setAutoSuspend", "(I)V");
				jmethodID brokerIDId = g_env->GetMethodID(parameter, "setBrokerID", "(Ljava/lang/String;)V");

				jmethodID brokerOrderSeqId = g_env->GetMethodID(parameter, "setBrokerOrderSeq", "(I)V");
				jmethodID businessUnitId = g_env->GetMethodID(parameter, "setBusinessUnit", "(Ljava/lang/String;)V");
				jmethodID cancelTimeId = g_env->GetMethodID(parameter, "setCancelTime", "(Ljava/lang/String;)V");
				jmethodID clearingPartIDId = g_env->GetMethodID(parameter, "setClearingPartID", "(Ljava/lang/String;)V");
				jmethodID clientIDId = g_env->GetMethodID(parameter, "setClientID", "(Ljava/lang/String;)V");

				jmethodID combHedgeFlagId = g_env->GetMethodID(parameter, "setCombHedgeFlag", "(Ljava/lang/String;)V");
				jmethodID combOffsetFlagId = g_env->GetMethodID(parameter, "setCombOffsetFlag", "(Ljava/lang/String;)V");
				jmethodID contingentConditionId = g_env->GetMethodID(parameter, "setContingentCondition", "(Ljava/lang/String;)V");
				jmethodID directionId = g_env->GetMethodID(parameter, "setDirection", "(Ljava/lang/String;)V");
				jmethodID exchangeIDId = g_env->GetMethodID(parameter, "setExchangeID", "(Ljava/lang/String;)V");

				jmethodID exchangeInstIDId = g_env->GetMethodID(parameter, "setExchangeInstID", "(Ljava/lang/String;)V");
				jmethodID forceCloseReasonId = g_env->GetMethodID(parameter, "setForceCloseReason", "(Ljava/lang/String;)V");
				jmethodID frontIDId = g_env->GetMethodID(parameter, "setFrontID", "(I)V");
				jmethodID gtdDateId = g_env->GetMethodID(parameter, "setGtdDate", "(Ljava/lang/String;)V");
				jmethodID insertDateId = g_env->GetMethodID(parameter, "setInsertDate", "(Ljava/lang/String;)V");

				jmethodID insertTimeId = g_env->GetMethodID(parameter, "setInsertTime", "(Ljava/lang/String;)V");
				jmethodID installIDId = g_env->GetMethodID(parameter, "setInstallID", "(I)V");
				jmethodID instrumentIDId = g_env->GetMethodID(parameter, "setInstrumentID", "(Ljava/lang/String;)V");
				jmethodID investorIDId = g_env->GetMethodID(parameter, "setInvestorID", "(Ljava/lang/String;)V");
				jmethodID limitPriceId = g_env->GetMethodID(parameter, "setLimitPrice", "(D)V");

				jmethodID minVolumeId = g_env->GetMethodID(parameter, "setMinVolume", "(I)V");
				jmethodID notifySequenceId = g_env->GetMethodID(parameter, "setNotifySequence", "(I)V");
				jmethodID orderLocalIDId = g_env->GetMethodID(parameter, "setOrderLocalID", "(Ljava/lang/String;)V");
				jmethodID orderPriceTypeId = g_env->GetMethodID(parameter, "setOrderPriceType", "(Ljava/lang/String;)V");
				jmethodID orderRefId = g_env->GetMethodID(parameter, "setOrderRef", "(Ljava/lang/String;)V");

				jmethodID orderSourceId = g_env->GetMethodID(parameter, "setOrderSource", "(Ljava/lang/String;)V");
				jmethodID orderStatusId = g_env->GetMethodID(parameter, "setOrderStatus", "(Ljava/lang/String;)V");
				jmethodID orderSubmitStatusId = g_env->GetMethodID(parameter, "setOrderSubmitStatus", "(Ljava/lang/String;)V");
				jmethodID orderSysIDId = g_env->GetMethodID(parameter, "setOrderSysID", "(Ljava/lang/String;)V");
				jmethodID orderTypeId = g_env->GetMethodID(parameter, "setOrderType", "(Ljava/lang/String;)V");
				
				jmethodID participantIDId = g_env->GetMethodID(parameter, "setParticipantID", "(Ljava/lang/String;)V");
				jmethodID relativeOrderSysIDId = g_env->GetMethodID(parameter, "setRelativeOrderSysID", "(Ljava/lang/String;)V");
				jmethodID requestIDId = g_env->GetMethodID(parameter, "setRequestID", "(I)V");
				jmethodID sequenceNoId = g_env->GetMethodID(parameter, "setSequenceNo", "(I)V");
				jmethodID sessionIDId = g_env->GetMethodID(parameter, "setSessionID", "(I)V");

				jmethodID settlementIDId = g_env->GetMethodID(parameter, "setSettlementID", "(I)V");
				jmethodID statusMessageId = g_env->GetMethodID(parameter, "setStatusMsg", "(Ljava/lang/String;)V");
				jmethodID stopPriceId = g_env->GetMethodID(parameter, "setStopPrice", "(D)V");
				jmethodID suspendTimeId = g_env->GetMethodID(parameter, "setSuspendTime", "(Ljava/lang/String;)V");
				jmethodID swapOrderId = g_env->GetMethodID(parameter, "setSwapOrder", "(I)V");

				jmethodID timeConditionId = g_env->GetMethodID(parameter, "setTimeCondition", "(Ljava/lang/String;)V");
				jmethodID traderIDId = g_env->GetMethodID(parameter, "setTraderID", "(Ljava/lang/String;)V");
				jmethodID tradingDayId = g_env->GetMethodID(parameter, "setTradingDay", "(Ljava/lang/String;)V");
				jmethodID updateTimeId = g_env->GetMethodID(parameter, "setUpdateTime", "(Ljava/lang/String;)V");
				jmethodID userForceCloseId = g_env->GetMethodID(parameter, "setUserForceClose", "(I)V");

				jmethodID userIDId = g_env->GetMethodID(parameter, "setUserID", "(Ljava/lang/String;)V");
				jmethodID userProductInfoId = g_env->GetMethodID(parameter, "setUserProductInfo", "(Ljava/lang/String;)V");
				jmethodID volumeConditionId = g_env->GetMethodID(parameter, "setVolumeCondition", "(Ljava/lang/String;)V");
				jmethodID volumeTotalId = g_env->GetMethodID(parameter, "setVolumeTotal", "(I)V");
				jmethodID volumeTotalOrignalId = g_env->GetMethodID(parameter, "setVolumeTotalOriginal", "(I)V");
				
				jmethodID volumeTradedId = g_env->GetMethodID(parameter, "setVolumeTraded", "(I)V");
				jmethodID zceTotalTradedVolumeId = g_env->GetMethodID(parameter, "setZceTotalTradedVolume", "(I)V");

				jstring j_activeTime = g_env->NewStringUTF(pOrder->ActiveTime);
				g_env->CallVoidMethod(paramObject, activeTimeId, j_activeTime);
				jstring j_activeTraderID = g_env->NewStringUTF(pOrder->ActiveTraderID);
				g_env->CallVoidMethod(paramObject, activeTraderIDId, j_activeTraderID);
				jstring j_activeUserId = g_env->NewStringUTF(pOrder->ActiveUserID);
				g_env->CallVoidMethod(paramObject, activeUserIDId, j_activeUserId);
				g_env->CallVoidMethod(paramObject, autoSuspendId, pOrder->IsAutoSuspend);
				jstring j_brokerId = g_env->NewStringUTF(pOrder->BrokerID);
				g_env->CallVoidMethod(paramObject, brokerIDId, j_brokerId);

				g_env->CallVoidMethod(paramObject, brokerOrderSeqId, pOrder->BrokerOrderSeq);				
				jstring j_businessUnit = g_env->NewStringUTF(pOrder->BusinessUnit);
				g_env->CallVoidMethod(paramObject, businessUnitId, j_businessUnit);
				jstring j_cancelTime = g_env->NewStringUTF(pOrder->CancelTime);
				g_env->CallVoidMethod(paramObject, cancelTimeId, j_cancelTime);
				jstring j_clearingPartID = g_env->NewStringUTF(pOrder->ClearingPartID);
				g_env->CallVoidMethod(paramObject, clearingPartIDId, j_clearingPartID);
				jstring j_clientId = g_env->NewStringUTF(pOrder->ClientID);
				g_env->CallVoidMethod(paramObject, clientIDId, j_clientId);

				jstring j_combHedgeFlag = g_env->NewStringUTF(pOrder->CombHedgeFlag);
				g_env->CallVoidMethod(paramObject, combHedgeFlagId, j_combHedgeFlag);
				jstring j_combOffsetFlag = g_env->NewStringUTF(pOrder->CombOffsetFlag);
				g_env->CallVoidMethod(paramObject, combOffsetFlagId, j_combOffsetFlag);
				char* cp_contingentCondition = new char[2]();
				cp_contingentCondition[0] = pOrder->ContingentCondition;
				cp_contingentCondition[1] = '\0';
				jstring j_contingentCondition = g_env->NewStringUTF(cp_contingentCondition);
				delete(cp_contingentCondition);
				g_env->CallVoidMethod(paramObject, contingentConditionId, j_contingentCondition);
				jstring j_direction = g_env->NewStringUTF(&pOrder->Direction);
				g_env->CallVoidMethod(paramObject, directionId, j_direction);
				jstring j_exchangeId = g_env->NewStringUTF(pOrder->ExchangeID);
				g_env->CallVoidMethod(paramObject, exchangeIDId, j_exchangeId);

				jstring j_exchangeInstId = g_env->NewStringUTF(pOrder->ExchangeInstID);
				g_env->CallVoidMethod(paramObject, exchangeInstIDId, j_exchangeInstId);
				char* cp_forceCloseReason = new char[2]();
				cp_forceCloseReason[0] = pOrder->ContingentCondition;
				cp_forceCloseReason[1] = '\0';
				jstring j_forceCloseReason = g_env->NewStringUTF(cp_forceCloseReason);
				delete(cp_forceCloseReason);
				g_env->CallVoidMethod(paramObject, forceCloseReasonId, j_forceCloseReason);
				g_env->CallVoidMethod(paramObject, frontIDId, pOrder->FrontID);
				jstring j_gtdDate = g_env->NewStringUTF(pOrder->GTDDate);
				g_env->CallVoidMethod(paramObject, gtdDateId, j_gtdDate);
				jstring j_insertDate = g_env->NewStringUTF(pOrder->InsertDate);
				g_env->CallVoidMethod(paramObject, insertDateId, j_insertDate);

				jstring j_insertTime = g_env->NewStringUTF(pOrder->InsertTime);
				g_env->CallVoidMethod(paramObject, insertTimeId, j_insertTime);
				g_env->CallVoidMethod(paramObject, installIDId, pOrder->InstallID);
				jstring j_instrumentID = g_env->NewStringUTF(pOrder->InstrumentID);
				g_env->CallVoidMethod(paramObject, instrumentIDId, j_instrumentID);
				jstring j_investorID = g_env->NewStringUTF(pOrder->InvestorID);
				g_env->CallVoidMethod(paramObject, investorIDId, j_investorID);
				g_env->CallVoidMethod(paramObject, limitPriceId, pOrder->LimitPrice);

				g_env->CallVoidMethod(paramObject, minVolumeId, pOrder->MinVolume);
				g_env->CallVoidMethod(paramObject, notifySequenceId, pOrder->NotifySequence);
				jstring j_orderLocalID = g_env->NewStringUTF(pOrder->OrderLocalID);
				g_env->CallVoidMethod(paramObject, orderLocalIDId, j_orderLocalID);
				jstring j_orderPriceType = g_env->NewStringUTF(&pOrder->OrderPriceType);
				g_env->CallVoidMethod(paramObject, orderPriceTypeId, j_orderPriceType);
				jstring j_OrderRef = g_env->NewStringUTF(pOrder->OrderRef);
				g_env->CallVoidMethod(paramObject, orderRefId, j_OrderRef);
				
				jstring j_orderSource = g_env->NewStringUTF(&pOrder->OrderSource);
				g_env->CallVoidMethod(paramObject, orderSourceId, j_orderSource);
				jstring j_orderStatus = g_env->NewStringUTF(&pOrder->OrderStatus);
				g_env->CallVoidMethod(paramObject, orderStatusId, j_orderStatus);
				char* cp_orderSubmitStatus = new char[2]();
				cp_orderSubmitStatus[0] = pOrder->OrderSubmitStatus;
				cp_orderSubmitStatus[1] = '\0';
				jstring j_orderSubmitStatus = g_env->NewStringUTF(cp_orderSubmitStatus);
				delete(cp_orderSubmitStatus);
				g_env->CallVoidMethod(paramObject, orderSubmitStatusId, j_orderSubmitStatus);
				jstring j_orderSysID = g_env->NewStringUTF(pOrder->OrderSysID);
				g_env->CallVoidMethod(paramObject, orderSysIDId, j_orderSysID);
				jstring j_orderType = g_env->NewStringUTF(&pOrder->OrderType);
				g_env->CallVoidMethod(paramObject, orderTypeId, j_orderType);

				jstring j_participantID = g_env->NewStringUTF(pOrder->ParticipantID);
				g_env->CallVoidMethod(paramObject, participantIDId, j_participantID);
				jstring j_relativeOrderSysID = g_env->NewStringUTF(pOrder->RelativeOrderSysID);
				g_env->CallVoidMethod(paramObject, relativeOrderSysIDId, j_relativeOrderSysID);
				g_env->CallVoidMethod(paramObject, requestIDId, pOrder->RequestID);
				g_env->CallVoidMethod(paramObject, sequenceNoId, pOrder->SequenceNo);
				g_env->CallVoidMethod(paramObject, sessionIDId, pOrder->SessionID);

				g_env->CallVoidMethod(paramObject, settlementIDId, pOrder->SettlementID);
				jstring j_statusMsg = g_env->NewStringUTF(pOrder->StatusMsg);
				g_env->CallVoidMethod(paramObject, statusMessageId, j_statusMsg);
				g_env->CallVoidMethod(paramObject, stopPriceId, pOrder->StopPrice);
				jstring j_suspendTime = g_env->NewStringUTF(pOrder->SuspendTime);
				g_env->CallVoidMethod(paramObject, suspendTimeId, j_suspendTime);
				g_env->CallVoidMethod(paramObject, swapOrderId, pOrder->IsSwapOrder);

				jstring j_timeCondition = g_env->NewStringUTF(&pOrder->TimeCondition);
				g_env->CallVoidMethod(paramObject, timeConditionId, j_timeCondition);
				jstring j_traderID = g_env->NewStringUTF(pOrder->TraderID);
				g_env->CallVoidMethod(paramObject, traderIDId, j_traderID);
				jstring j_tradingDay = g_env->NewStringUTF(pOrder->TradingDay);
				g_env->CallVoidMethod(paramObject, tradingDayId, j_tradingDay);
				jstring j_updateTime = g_env->NewStringUTF(pOrder->UpdateTime);
				g_env->CallVoidMethod(paramObject, updateTimeId, j_updateTime);
				g_env->CallVoidMethod(paramObject, userForceCloseId, pOrder->UserForceClose);

				jstring j_userID = g_env->NewStringUTF(pOrder->UserID);
				g_env->CallVoidMethod(paramObject, userIDId, j_userID);
				jstring j_userProductInfo = g_env->NewStringUTF(pOrder->UserProductInfo);
				g_env->CallVoidMethod(paramObject, userProductInfoId, j_userProductInfo);
				char* cp_volumeCondition = new char[2]();
				cp_volumeCondition[0] = pOrder->VolumeCondition;
				cp_volumeCondition[1] = '\0';
				jstring j_volumeCondition = g_env->NewStringUTF(cp_volumeCondition);
				delete(cp_volumeCondition);
				g_env->CallVoidMethod(paramObject, volumeConditionId, j_volumeCondition);
				g_env->CallVoidMethod(paramObject, volumeTotalId, pOrder->VolumeTotal);
				g_env->CallVoidMethod(paramObject, volumeTotalOrignalId, pOrder->VolumeTotalOriginal);

				g_env->CallVoidMethod(paramObject, volumeTradedId, pOrder->VolumeTraded);
				g_env->CallVoidMethod(paramObject, zceTotalTradedVolumeId, pOrder->ZCETotalTradedVolume);

				if (mid == 0) {
					//printf("mid was 0!!!\n");
					return;
				}

				g_env->CallVoidMethod(obj, mid, paramObject);
				it++;

			}

		}

		virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo){
			printf("OnErrRtnOrderInsert\n");
			JNIEnv * g_env;
			jint success = cachedJvm -> GetEnv((void**)&g_env, JNI_VERSION_1_6);
			if(success != JNI_OK){
			//	printf("attempting to resync jvm to thread\n");
				jint attachSuccess = cachedJvm ->AttachCurrentThread((void**)&g_env, NULL);
				if(attachSuccess == 0){
					//printf("resync successful!\n");
				}
				else{
					//printf("resync unsuccessful\n");
					return;
				}
			}
			list<jobject>::iterator it = observers.begin();			
			while (it != observers.end()) {
				
				jobject &obj = *it;
				jclass cls = g_env->GetObjectClass(obj);
				jmethodID mid = g_env->GetMethodID(cls, "onRspError", "(Lbo/ErrorResult;)V");

				jclass parameter = g_env->FindClass("bo/ErrorResult");
			    jmethodID midConstructor = (g_env)->GetMethodID(parameter, "<init>", "()V");
				jobject paramObject = (g_env)->NewObject(parameter, midConstructor);

				jmethodID errorIDId = g_env->GetMethodID(parameter, "setErrorId", "(I)V");
				jmethodID errorMessageId = g_env->GetMethodID(parameter, "setErrorMessage", "(Ljava/lang/String;)V");
				
				g_env->CallVoidMethod(paramObject, errorIDId, pRspInfo->ErrorID);
				jstring j_errorMessage = g_env->NewStringUTF(pRspInfo->ErrorMsg);
				g_env->CallVoidMethod(paramObject, errorMessageId, j_errorMessage);


				if (mid == 0) {
					//printf("mid was 0!!!\n");
					return;
				}

				g_env->CallVoidMethod(obj, mid, paramObject);
				it++;

			}
		}



	private:
		// a pointer of CThostFtdcMduserApi instance
		//CThostFtdcTraderApi *m_pUserApi;
};