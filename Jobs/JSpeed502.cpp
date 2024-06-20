#pragma hdrstop
#include "JSpeed502.h"
#include "Protocol.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
JSpeed502::JSpeed502(AnsiString _type, CInv* _Inv)
{
	Reset();
	type = _type;
	if (_Inv == NULL)
		inverter = NULL;
	else
	{
		inverter = new Inverter(type != "Thick", _Inv);
		AddAlarm(SLD->iCC, true, 50);
	}
}

// ---------------------------------------------------------------------------
JSpeed502::~JSpeed502(void)
{
	if (inverter != NULL)
		delete inverter;
}

// ---------------------------------------------------------------------------
void JSpeed502::SetError(AnsiString _msg)
{
	cmd = ECmd::None;
	state = ECmd::Stop;
	step = 0;
	if (inverter != NULL)
		inverter->stopRotation();
	if (!error)
		errorMsg = _msg;
	error = true;
	DropAlarms();
}

// ---------------------------------------------------------------------------
void JSpeed502::SetSpeed(void)
{
	if (inverter == NULL)
		return;
	SetSpeed(inverter->DefaultSpeed());
}

// ---------------------------------------------------------------------------
void JSpeed502::SetSpeed(int _frequency)
{
	if (inverter == NULL)
		return;
	if (cmd != ECmd::None)
	{
		SetError("�� ��������� ���������� ��������");
		return;
	}
	frequency = _frequency;
	cmd = frequency <= 0 ? cmd = ECmd::Stop : cmd = ECmd::Speed;
	if (cmd == ECmd::Stop && state == ECmd::Stop)
		cmd = ECmd::None;
	step = 0;
}

// ---------------------------------------------------------------------------
void JSpeed502::Exec(void)
{
	if (inverter == NULL)
		return;
	if (error)
		return;
	Job::Exec();
	if (error)
	{
		SetError("");
		return;
	}
	ExecCheck();
	if (cmd == ECmd::None)
		return;
	if (cmd == ECmd::Stop)
		ExecStop();
	else if (cmd == ECmd::Speed)
		ExecSpeed();
}

// ---------------------------------------------------------------------------
void JSpeed502::ExecCheck(void)
{
	if (state != ECmd::Speed)
		return;
	CInv::State inv_state = inverter->GetCurrentState();
//	pr(inv_state.Tostring());
	if (inv_state.error)
	{
		SetError(inverter->GetErrorMsg());
		return;
	}
	// AddAlarm(iPCHA, true);
	// AddAlarm(iPCHRUN, true);

	if (!inv_state.iRUN)
	{
		SetError("������ �� RUN");
		return;
	}
	if (!inv_state.iABC)
	{
		SetError("������ ABC (��A)");
		return;
	}
}

// ---------------------------------------------------------------------------
void JSpeed502::ExecStop()
{
	switch (step)
	{
	case 0:
		if (!inverter->stopRotation())
		{
			SetError("�� ���� ���������� ��������");
			return;
		}
		pr("���� ������ PCHRUN 5 �");
		startTick = GetTickCount();
		step = 1;
	case 1:
		if (GetTickCount() - startTick > 2000)
		{
			SetError("�� �� ��������� ������ PCHRUN �� 5 �");
			break;
		}
		CInv::State inv_state = inverter->stateRead();
		if (!inv_state.error && !inv_state.iRUN)
		{
			cmd = ECmd::None;
			state = ECmd::Stop;
			step = 0;
		}
	}
}

// ---------------------------------------------------------------------------
void JSpeed502::ExecSpeed()
{
	switch (step)
	{
	case 0:
			// if (!inverter->ResetErrors())
			// {
			// SetError("�� ������� Reset");
			// return;
			// }
		if (!inverter->setParameterSpeed(frequency))
		{
			SetError("�� ���� ��������� ��������");
			return;

		}
		if (!inverter->startRotation())
		{
			SetError("�� ���� �������� ��������");
			return;
		}
		pr("���� ��������� PCHRUN 2 �");
		startTick = GetTickCount();
		step = 1;
	case 1:
		if (GetTickCount() - startTick > 2000)
		{
			SetError("�� ��������� ��������� PCHRUN �� 2 �");
			break;
		}
		CInv::State inv_state = inverter->GetCurrentState();
		if (!inv_state.error && inv_state.iRUN)
		{
			state = ECmd::Speed;
			cmd = ECmd::None;
			step = 0;
		}
	}
}

// ---------------------------------------------------------------------------

void JSpeed502::Reset(void)
{
	Job::Reset();
	if (inverter != NULL)
		inverter->stopRotation();
	cmd = ECmd::None;
	state = ECmd::Stop;
	step = 0;
}

// ---------------------------------------------------------------------------
int JSpeed502::GetSpeed()
{
	if (inverter == NULL)
		return (0);
	if (error)
		return (-1);
	return (inverter->getParameterSpeed());
}
// ---------------------------------------------------------------------------
