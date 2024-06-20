#pragma hdrstop
#include "Protocol.h"
#include "Inverter.h"
#include "InverterPars.h"
// ------------------------------------------------------------------------------

#pragma package(smart_init)

// ------------------------------------------------------------------------------
Inverter::Inverter(bool _line, CInv* _Inv)
{
	InverterPars Pars;
	Pars.Load(_line);
	inverter = _Inv;
	// inverter->OnProtocol = OnProtocol;
	testThread = NULL;
	cs = new TCriticalSection();
	abonent = Pars.Abonent;
	SpeedRegister = Pars.SpeedRegister;
	speed = Pars.Frequency;
}

// ------------------------------------------------------------------------------
Inverter::~Inverter()
{
	stopRotation();
	delete cs;
}

// ------------------------------------------------------------------------------
bool Inverter::setParameterSpeed(int value)
{
	bool ret;
	cs->Enter();
	{
		ret = inverter->SetFrequency(abonent, IntToStr(80 + SpeedRegister),
			value * 100);
	} cs->Leave();
	return (ret);
}

// ------------------------------------------------------------------------------
bool Inverter::setSpeed(void)
{
	return (setParameterSpeed(speed));
}

// ------------------------------------------------------------------------------
int Inverter::getParameterSpeed(void)
{
	int ret;
	cs->Enter();
	{
		ret = inverter->GetFrequency(abonent, "0" + IntToStr(SpeedRegister));
		if (ret > 0)
			ret /= 100;
	} cs->Leave();
	return (ret);
}

// ------------------------------------------------------------------------------
bool Inverter::startRotation()
{
	if (testThread != NULL)
		return (true);
	// inverter->SetMode(abonent, 0);

	bool ok;
	for (int i = 0; i < 5; i++)
	{
		ok = inverter->Reset9966(abonent);
		if (ok)
			break;
	}
	for (int i = 0; i < 5; i++)
	{
		if (setSpeed())
			break;
	}
	inverter->SetMode(abonent, 0);
	/*
	 if (ok)
	 break;
	 AnsiString a="Inverter::startRotation: Не проходит Reset9966(";
	 a+=abonent;
	 a+=")";
	 OnProtocol(a);
	 Sleep(1000);
	 */
	// }
	// if(!ok)
	// return false;

	// Sleep(1000);
	// AnsiString a = "ПРИВЕТ!";
	// OnProtocol(a);
	/*
	 if(!inverter->SetMode(abonent, 0))
	 {
	 OnProtocol(AnsiString("Inverter::startRotation: Не проходит StateWrite ")+abonent);
	 return false;
	 }
	 */
	CInv::State state = inverter->GetCurrentState();
	state.oSTF = true;
	state.oRH = true;
	bool aaa_ok;
	for (int i = 0; i < 5; i++)
	{
		aaa_ok = inverter->StateWrite(abonent, state);
		if (aaa_ok)
			break;
	}
	if (!aaa_ok)
	{
		OnProtocol(AnsiString
			("Inverter::startRotation: Не проходит StateWrite ") + abonent);
		return false;
	}
	testThread = new rotationThread(inverter, cs, abonent);
	return true;
}

// ------------------------------------------------------------------------------
bool Inverter::stopRotation()
{
	if (testThread == NULL)
		return (true);
	delete testThread;
	testThread = NULL;
	CInv::State state = inverter->GetCurrentState();
	state.oSTF = false;
	state.oRH = false;
	if (!inverter->StateWrite(abonent, state))
		return false;
	return true;
}

// ------------------------------------------------------------------------------
CInv::State Inverter::stateRead()
{
	CInv::State ret;
	cs->Enter();
	{
		ret = inverter->StateRead(abonent);
	} cs->Leave();
	return (ret);
}

// ------------------------------------------------------------------------------
bool Inverter::NETManage()
{
	bool ret;
	cs->Enter();
	{
		ret = inverter->SetMode(abonent, 0);
	} cs->Leave();
	return (ret);
}

// ------------------------------------------------------------------------------
bool Inverter::ResetErrors()
{
	bool ret;
	cs->Enter();
	{
		ret = inverter->Reset9966(abonent);
	} cs->Leave();
	return (ret);
}

// ------------------------------------------------------------------------------
void Inverter::OnProtocol(AnsiString _msg)
{
	TPr::pr(_msg);
}

// ------------------------------------------------------------------------------
AnsiString Inverter::GetErrorMsg()
{
	return (inverter->GetErrorMsg());
}

CInv::State Inverter::GetCurrentState()
{
	CInv::State ret;
	cs->Enter();
	{
		if (testThread == NULL)
		{
			ret.error = true;
		}
		else
			ret = testThread->CurrentState;
	} cs->Leave();
	return(ret);
}

// ******************************************************************************
__fastcall rotationThread::rotationThread(CInv* _inv, TCriticalSection* _cs,
	int _abonent)
{
	inv = _inv;
	cs = _cs;
	abonent = _abonent;
}

void __fastcall rotationThread::Execute()
{
	for (; ;)
	{
		cs->Enter();
		{
			CurrentState = inv->StateRead(abonent);
		} cs->Leave();
		if (Terminated)
			break;
		Sleep(500);

	}
}
