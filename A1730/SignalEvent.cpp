//---------------------------------------------------------------------------


#pragma hdrstop

#include "SignalEvent.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
AnsiString SignalEvent::Tostring(void)
{
	AnsiString ret="SignalEvent: ";
	ret+="tick=";
	ret+=tick;
	ret+=" value=";
	ret+=value?"true":"false";
	ret+=" name=";
	ret+=name;
	return(ret);
}

