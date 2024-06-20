#pragma hdrstop
#include "ThReturn.h"
#include "uFunctions.h"
#include "protocol.h"
#include "SMSM.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall ThReturn::ThReturn(TIniFile*_ini) : ThBase(_ini,"Return")
{
}
// ---------------------------------------------------------------------------
void __fastcall ThReturn::Execute()
{
	JReturn jReturn=JReturn(ini);
	PostStatus1("Возрат");
	PostStatus2("");
	for (; ;)
	{
		if (Terminated)
			break;
		jReturn.Exec();
		if (jReturn.IsComplete())
			break;
		if (jReturn.IsError())
		{
			PostStatus2(jReturn.GetErrorMsg());
			break;
		}
		Sleep(500);
		if (Terminated)
			break;
	}
	SMSM::SetPost("COMPLETE");
}

// ---------------------------------------------------------------------------
