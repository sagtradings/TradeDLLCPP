#include "globals.h"

class TraderEventHandler : public CThostFtdcTraderSpi{
		public:
		// constructor，which need a valid pointer to a CThostFtdcMduserApi instance
		TraderEventHandler(CThostFtdcTraderApi *pUserApi) : m_pUserApi(pUserApi) {}
		~TraderEventHandler() {}

		virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool isLast){
			printf("an error happened");
		}

		virtual void OnFrontConnected(){
			printf("the front is connected");
			CThostFtdcReqUserLoginField reqUserLogin;
			// get BrokerID
			
			const char  *userID = "00000008";
			const char  *password = "123321";
			const char  *brokerID = "1013";
			strcpy_s(reqUserLogin.UserID, userID);
		
			strcpy_s(reqUserLogin.Password, password);
			strcpy_s(reqUserLogin.BrokerID, brokerID);
			
			//delete userID;
			//delete password;
			//delete brokerID;


			// send the login request
			m_pUserApi->ReqUserLogin(&reqUserLogin, 0);
			

		}

		virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
			if (pRspInfo->ErrorID != 0) {
				// login failure, the client should handle this error.
				printf("Failed to login, errorcode=%d errormsg=%s requestid=%d=%d", pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast);
				return;
			}
			const char * instrument = "IF1307";
			CThostFtdcInputOrderField orderField;
			memset(&orderField,0,sizeof(orderField));
			const char  *userID = "00000008";
			const char  *password = "123321";
			const char  *brokerID = "1013";
			strcpy_s(orderField.BrokerID, brokerID);
			strcpy_s(orderField.UserID, userID);
			strcpy_s(orderField.InstrumentID, instrument);
			strcpy_s(orderField.InvestorID, userID);
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
			m_pUserApi->ReqOrderInsert(&orderField, 0);
			
			//printf("marketDataSubscribed");

			
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