#pragma hdrstop
#include "ThTest.h"
#pragma package(smart_init)
#include "uFunctions.h"
#include "protocol.h"
#include "JZoner.h"
#include "SMSM.h"

#include "JTransport502.h"

//---------------------------------------------------------------------------
__fastcall ThTest::ThTest(Bank* _bank) : IW(true, true, false, false),ThBase("ThTest"),
	jCollect502(_bank, IW)

{
	bank = _bank;
}

//---------------------------------------------------------------------------
void __fastcall ThTest::Execute()
{
	bank->Start(IW);
	SMSM::SetPost("CLEAR");

	JTransport502 jTransport = JTransport502(bank, IW,NULL,NULL);
	JZoner jZoner = JZoner(bank, IW);
	jTransport.Start();
	Sleep(100);
	jCollect502.Start();
	jZoner.Start();
	for (; ;)
	{
		DWORD tick = GetTickCount();
		if (Terminated)
			break;
		jCollect502.Exec(tick);
		jZoner.Exec(tick);
		if (!jTransport.ExecTest(tick))
			break;
		if (Terminated)
			break;
		Sleep(100);
		if (Terminated)
			break;
	}
	DWORD tick = GetTickCount();
	jCollect502.Stop(tick);
	jZoner.Exec();
	SMSM::SetPost("COMPLETE");
}
//---------------------------------------------------------------------------
