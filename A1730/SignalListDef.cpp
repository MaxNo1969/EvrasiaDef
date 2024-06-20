#pragma hdrstop
#include "SignalListDef.h"
#pragma package(smart_init)
SignalListDef* SLD = NULL;

SignalListDef::SignalListDef() :
	save1730("Defect.PCIE1730.Save1730"),
	catchSignals(3, 300)
{
	(iCC = Find("���� ����������", true))->AddHint("iCC");
	(iTCYCLE = Find("���� ���1", true))->AddHint("iTCYCLE");
	(iCCYCLE = Find("���� ���2", true))->AddHint("iCCYCLE");
	(iSTROBE = Find("����� ����", true))->AddHint("iSTROBE");
	(iREADY = Find("����������", true))->AddHint("iREADY");
	(iTCONTROL = Find("�������� 1", true))->AddHint("iTCONTROL");
	(iCCONTROL = Find("�������� 2", true))->AddHint("iCCONTROL");
	(oTPCHPOW = Find("������� �� ���1", false))->AddHint("oTPCHPOW");
	(oTSCANPOW = Find("������� �� ���1", false))->AddHint("oTSCANPOW");
	(oTWORK = Find("������ ���1", false))->AddHint("oTWORK");
	(oCWORK = Find("������ ���2", false))->AddHint("oCWORK");
	(oSHIFT = Find("����������", false))->AddHint("oSHIFT");
	(oSTROBE = Find("�����", false))->AddHint("oSTROBE");
	(oRESULT = Find("���������", false))->AddHint("oRESULT");

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
	//AlarmList->Add("��� ������� ���� ����������");
	//wasAlarm = true;
	//}
	//if (LinearCycle)
	//{
	//if (iCYCLE_TS->WasConst0(false, 50))
	//{
	//AlarmList->Add("������ ������ ����");
	//wasAlarm = true;
	//}
	//}
	//if (InvA)
	//{
	//if (iPCHA->WasConst0(false, 50))
	//{
	//AlarmList->Add("������: ������ ����� ���� �� �");
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
