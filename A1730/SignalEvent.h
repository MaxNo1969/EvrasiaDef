#ifndef SignalEventH
#define SignalEventH
#include "System.hpp"

//#include "Signal.h"

class SignalEvent
{
public:
//	enum class EType { SIGNAL, STROBE, CONTROL1, CONTROL2, CONTROL3 };
	SignalEvent(void)
	{
		signal=NULL;
		tick=0;
		value=false;
		name=NULL;
//		Tp=EType::SIGNAL;
	}
//	EType Tp;
	void* signal;
	DWORD tick;
	bool value;
	AnsiString name;
	AnsiString Tostring(void);
};

#endif
