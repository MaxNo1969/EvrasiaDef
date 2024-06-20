#pragma hdrstop
#include "JZoner.h"
#include "PA.h"
#pragma package(smart_init)
#include "SignalListDef.h"
#include "SMSM.h"
#include "Protocol.h"

//---------------------------------------------------------------------------
JZoner::JZoner(Bank* _bank, IsWork _IW)
{
	bank = _bank;
	started = false;
	ReadPeriod = (DWORD)PA("Defect.Some.CheckZonePeriod").Int();
	IW = _IW;
	if (IW.Thick)
	{
		PA pa_zones("Thickness.Work.Zones");
		int Count = pa_zones.GetCount();
		for (int i = 0; i < Count; i++)
		{
			PA pa_zone = pa_zones[i];
			pa_zone.Item("ToDo").Write(false);
			pa_zone.Item("Done").Write(false);
		}
	}
//	SLD->oRESULT->Set(false);
//	SLD->oSTROBE->Set(false);
	acs=new ACS(bank,ReadPeriod);
}
JZoner::~JZoner(void)
{
	delete acs;
}


//---------------------------------------------------------------------------
void JZoner::Start()
{
	started = true;
	LastExec = GetTickCount();
}
//---------------------------------------------------------------------------

void JZoner::Exec(DWORD _tick)
{
	if (!started)
		return;
	if (_tick - LastExec < ReadPeriod)
		return;
	LastExec = _tick;
	if (IW.Thick)
	{
		PA pa_zones("Thickness.Work.Zones");
		for (; ;)
		{
			BankZoneTicks zone = bank->GetNextThickTicks(false);
			if (!zone.Ok)
				break;
			PA pa_zone = pa_zones[zone.index];
			pa_zone.Item("TickBegin").Write(zone.FirstTick);
			pa_zone.Item("TickEnd").Write(zone.LastTick);
			pa_zone.Item("Last").Write(zone.last);
			pa_zone.Item("ToDo").Write(true);
			pr(AnsiString("Send ticks: ")+zone.ToString());
		}
		int Count = pa_zones.GetCount();
		for (int i = bank->GetThickZones(); i < Count; i++)
		{
			PA pa_zone = pa_zones[i];
			if (!pa_zone.Item("Done").Bool())
				break;
			bank->AddThickZone(i, pa_zone.Item("Class").String() != "None", pa_zone.Item("Level").Double(),
				pa_zone.Item("Last").Bool());
		}
		if (bank->GetNextThickZone(true).Ok)
			SMSM::SetPost("REDRAW THICK");
	}
	if (IW.Cross)
	{
		if (bank->GetNextCrossZone(true).Ok)
			SMSM::SetPost("REDRAW CROSS");
	}
	if (IW.Line)
	{
		if (bank->GetNextLineZone(true).Ok)
			SMSM::SetPost("REDRAW LINE");
	}
	if (IW.SG)
	{
		if (bank->GetNextSGZone(true).Ok)
			SMSM::SetPost("REDRAW SG");
	}
	if(bank->CheckCompleteGetResultZones())
	{
			SMSM::SetPost("COMPLETE_ZONES");
	}
//	if(IW.Cross||IW.Line||IW.Thick)
//	{
//		for(;;)
//		{
//			BankZoneResult z=bank->GetNextResultZone();
//			if(!z.Ok)
//				break;
//			pr(z.ToString());
//			SLD->oRESULT->Set(!z.OkResult);
//			SLD->oSTROBE->Set(true);
//			Sleep(60);
//			SLD->oSTROBE->Set(false);
//			Sleep(60);
//		}
//	}
	return;
}
void JZoner::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("JZoner: ") + _msg);
}

//---------------------------------------------------------------------------
void JZoner::Exec()
{
	Exec(LastExec + ReadPeriod + 1);
}

//---------------------------------------------------------------------------
