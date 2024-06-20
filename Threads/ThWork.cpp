#pragma hdrstop
#include "ThWork.h"
#include "SMSM.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall ThWork::ThWork(IsWork _IW, Bank* _bank) : ThBase("ThWork"),
	jWork(_IW, _bank)
{
	IW=_IW;
}

// ---------------------------------------------------------------------------
void __fastcall ThWork::Execute()
{
	for (; ;)
	{
		if (Terminated)
		{
			PPR("Прервано пользователем");
			SMSM::SetPost("ERROR");
			return;
		}
		jWork.Exec();
		if (jWork.IsError())
			return;
		if (jWork.IsComplete())
		{
			PPR("Труба получена");
			SMSM::SetPost("COMPLETE");
			return;
		}
		Sleep(50);
	}
}
// ---------------------------------------------------------------------------

