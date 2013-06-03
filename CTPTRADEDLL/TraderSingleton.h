
#include "TradeHandler.h"

class TraderSingleton{
	public :
		 static CThostFtdcTraderApi* createTraderInstance();
		 static bool creationFlag;
		 ~TraderSingleton();
	private:
		
		
		TraderSingleton();
		

};
