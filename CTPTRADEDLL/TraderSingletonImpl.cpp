#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "TradeEventHandler.cpp"

class TraderSingletonImpl{
	public :

		 static CThostFtdcTraderApi*  createTraderInstance(){
			if(TraderSingletonImpl :: creationFlag == false){

			}
			return traderInstance;

		 }
		private:
			static bool creationFlag;
			static CThostFtdcTraderApi *traderInstance;
			~TraderSingletonImpl();
		    TraderSingletonImpl();

};
