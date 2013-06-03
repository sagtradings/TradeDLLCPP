#include "globals.h"
class TraderEventHandler : public CThostFtdcTraderSpi{
			public:
		// constructor，which need a valid pointer to a CThostFtdcMduserApi instance
		TraderEventHandler(CThostFtdcTraderApi *);
		~TraderEventHandler();

			private:
		// a pointer of CThostFtdcMduserApi instance
		CThostFtdcTraderApi *m_pUserApi;
};