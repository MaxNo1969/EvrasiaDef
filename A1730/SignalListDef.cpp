#pragma hdrstop
#include "SignalListDef.h"
#pragma package(smart_init)
SignalListDef* SLD = NULL;

SignalListDef::SignalListDef() :
	save1730("Defect.PCIE1730.Save1730"),
	catchSignals(3, 300)
{
	(iCC = Find("ÖÅÏÈ ÓÏĞÀÂËÅÍÈß", true))->AddHint("iCC");
	(iTCYCLE = Find("ÖÈÊË ÌÍÊ1", true))->AddHint("iTCYCLE");
	(iCCYCLE = Find("ÖÈÊË ÌÍÊ2", true))->AddHint("iCCYCLE");
	(iSTROBE = Find("ÑÒĞÎÁ ÇÎÍÛ", true))->AddHint("iSTROBE");
	(iREADY = Find("ÃÎÒÎÂÍÎÑÒÜ", true))->AddHint("iREADY");
	(iTCONTROL = Find("ÊÎÍÒĞÎËÜ 1", true))->AddHint("iTCONTROL");
	(iCCONTROL = Find("ÊÎÍÒĞÎËÜ 2", true))->AddHint("iCCONTROL");
	(oTPCHPOW = Find("ÏÈÒÀÍÈÅ Ï× ÌÍÊ1", false))->AddHint("oTPCHPOW");
	(oTSCANPOW = Find("Ïèòàíèå ÑÓ ÌÍÊ1", false))->AddHint("oTSCANPOW");
	(oTWORK = Find("Ğàáîòà ÌÍÊ1", false))->AddHint("oTWORK");
	(oCWORK = Find("Ğàáîòà ÌÍÊ2", false))->AddHint("oCWORK");
	(oSHIFT = Find("ÏÅĞÅÊËÀÄÊÀ", false))->AddHint("oSHIFT");
	(oSTROBE = Find("ÑÒĞÎÁ", false))->AddHint("oSTROBE");
	(oRESULT = Find("ĞÅÇÓËÜÒÀÒ", false))->AddHint("oRESULT");

	CrossCycle = false;
	LinearCycle = false;
	InvA = false;

	catchSignals.AddSignal(0, iSTROBE);
	catchSignals.AddSignal(1, iTCONTROL);
	catchSignals.AddSignal(2, iCCONTROL);
}
__fastcall SignalListDef::~SignalListDef(void)
{
}


void SignalListDef::SetCrossCycle(bool _v)
{
	cs->Enter();
	{
		CrossCycle = _v;
	} cs->Leave();
}

void SignalListDef::SetLinearCycle(bool _v)
{
	cs->Enter();
	{
		LinearCycle = _v;
	} cs->Leave();
}

void SignalListDef::SetInvA(bool _v)
{
	cs->Enter();
	{
		InvA = _v;
	} cs->Leave();
}

bool SignalListDef::CheckAlarm(void)
{
	//if (iCC->WasConst0(false, 50))
	//{
	//AlarmList->Add("Íåò ñèãíàëà öåïè óïğàâëåíèÿ");
	//wasAlarm = true;
	//}
	//if (LinearCycle)
	//{
	//if (iCYCLE_TS->WasConst0(false, 50))
	//{
	//AlarmList->Add("Ïğîïàë ñèãíàë Öèêë");
	//wasAlarm = true;
	//}
	//}
	//if (InvA)
	//{
	//if (iPCHA->WasConst0(false, 50))
	//{
	//AlarmList->Add("Àâàğèÿ: ïğîïàë ñèíàë Ïğîä Ï× À");
	//wasAlarm = true;
	//}
	//}
	//if (wasAlarm)
	//prAlarm();
	return (wasAlarm);
}

void SignalListDef::SetAlarm(bool _on)
{
	SetAlarm0(_on);
	cs->Enter();
	{
		InvA = false;
	} cs->Leave();
}

void SignalListDef::Drop(DWORD _tick)
{
}

void SignalListDef::Save(DWORD _in, DWORD _out)
{
	if (iCCYCLE->value)
		save1730.Add(_in, _out);
}

void SignalListDef::Catch(void)
{
	catchSignals.Exec();
}

void SignalListDef::CatchClear(void)
{
	cs->Enter();
	{
		catchSignals.Clear();
	} cs->Leave();
}

void SignalListDef::CatchStart(void)
{
	cs->Enter();
	{
		catchSignals.Start();
	} cs->Leave();
}
void SignalListDef::CatchStop(void)
{
	cs->Enter();
	{
		catchSignals.Stop();
	} cs->Leave();
}

void SignalListDef::CatchReport(void)
{
	cs->Enter();
	{
		catchSignals.Report();
	} cs->Leave();
}

SignalEvent* SignalListDef::CatchGetNext(void)
{
	SignalEvent* ret;
	cs->Enter();
	{
		ret = catchSignals.GetNext();
	} cs->Leave();
	return (ret);
}
