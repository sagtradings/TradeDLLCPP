#include "globals.h"

class LoginEventHandler : public CThostFtdcTraderSpi{
		public:
		// constructor，which need a valid pointer to a CThostFtdcMduserApi instance
		LoginEventHandler(CThostFtdcTraderApi *pUserApi) : m_pUserApi(pUserApi) {}
		~LoginEventHandler() {}

		virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool isLast){
			printf("an error happened");
		}

		virtual void OnFrontConnected(){
			printf("the front is connected");
			CThostFtdcReqUserLoginField reqUserLogin;
			// get BrokerID
			

			

		}

		virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
			JNIEnv * g_env;
			jint success = cachedJvm -> GetEnv((void**)&g_env, JNI_VERSION_1_6);
			if(success != JNI_OK){
				//printf("attempting to resync jvm to thread\n");
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
				jmethodID mid = g_env->GetMethodID(cls, "onRspUserLogin", "()V");
								g_env->CallVoidMethod(obj, mid);
				it++;
			}
			SetEvent(g_hEvent);
			

			
		}

		virtual void OnRtnTrade(CThostFtdcTradeField *pTrade){
			printf("OnRtntrade");
		}

		virtual void OnRspOrderInsert (CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
			printf("OnRspOrderInsert");
		}

		virtual void OnRtnOrder(CThostFtdcOrderField *pOrder){
			printf("OnRtnOrder");
		}

		virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo){
			printf("OnErrRtnOrderInsert");
		}

		virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo){
			printf("OnErrRtnOrderAction");
		}

	private:
		// a pointer of CThostFtdcMduserApi instance
		CThostFtdcTraderApi *m_pUserApi;
};