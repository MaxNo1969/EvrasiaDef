#pragma hdrstop
#include "ACS.h"
#include "Protocol.h"
#include "SignalListDef.h"

#pragma package(smart_init)

ACS::ACS(Bank* _bank, int _period)
{
	bank = _bank;
	period = _period;
}

__fastcall ACS::~ACS(void)
{
}

void __fastcall ACS::Execute()
{
	for (; ;)
	{
		DoBank();
		if (Terminated)
			break;
		Sleep(period);
	}
}

void ACS::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("ACS: ") + _msg);
}
void ACS::DoBank()
{
	for (; ;)
	{
			BankZoneResult z=bank->GetNextResultZone();
			if(!z.Ok)
				break;
			pr(z.ToString());
			SLD->oRESULT->Set(!z.OkResult);
			SLD->oSTROBE->Set(true);
			Sleep(60);
			SLD->oSTROBE->Set(false);
			Sleep(60);
	}
}

