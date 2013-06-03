#include <windows.h>
#include<jni.h>
#include<list>
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include"stdio.h"

using namespace std;

extern HANDLE g_hEvent;
extern list<jobject> observers;
extern JavaVM * cachedJvm;