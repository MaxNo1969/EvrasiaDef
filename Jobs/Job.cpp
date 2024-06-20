#pragma hdrstop
#include "Job.h"
#include "Protocol.h"
#include "SMSM.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
Job::Job(void)
{
	Reset();
	LA.reserve(10);
	complete = false;
}

//---------------------------------------------------------------------------
void Job::ResetError()
{
	error = false;
	errorMsg = "";
}

//---------------------------------------------------------------------------
void Job::AddAlarm(CSignal* _signal)
{
	AnsiString a = "AddAlarm: ";
	a += _signal->GetName();
	a += _signal->Get() ? " 1" : " 0";
	TPr::pr(a);
	for (vector<Alarm>::iterator it = LA.begin(); it != LA.end(); it++)
	{
		if (it->signal == _signal)
		{
			it->need = _signal->Get();
			return;
		}
	}
	Alarm p;
	p.signal = _signal;
	p.need = _signal->Get();
	LA.push_back(p);
}

//---------------------------------------------------------------------------
void Job::AddAlarm(CSignal* _signal, bool _need)
{
	AnsiString a = "AddAlarm: ";
	a += _signal->GetName();
	a += _need ? " 1" : " 0";
	TPr::pr(a);
	for (vector<Alarm>::iterator it = LA.begin(); it != LA.end(); it++)
	{
		if (it->signal == _signal)
		{
			it->need = _need;
			return;
		}
	}
	Alarm p;
	p.signal = _signal;
	p.need = _need;
	LA.push_back(p);
}

void Job::AddAlarm(CSignal* _signal, bool _need, int _period)
{
	AnsiString a = "AddAlarm: ";
	a += _signal->GetName();
	a += _need ? " 1" : " 0";
	TPr::pr(a);
	for (vector<Alarm>::iterator it = LA.begin(); it != LA.end(); it++)
	{
		if (it->signal == _signal)
		{
			it->need = _need;
			return;
		}
	}
	Alarm p;
	p.signal = _signal;
	p.need = _need;
	p.period = _period;
	LA.push_back(p);
}

//---------------------------------------------------------------------------
void Job::DropAlarm(CSignal* _signal)
{
	AnsiString a = "DropAlarm: ";
	a += _signal->GetName();
	TPr::pr(a);
	for (vector<Alarm>::iterator it = LA.begin(); it != LA.end(); it++)
	{
		if (it->signal == _signal)
		{
			LA.erase(it);
			return;
		}
	}
}

//---------------------------------------------------------------------------
void Job::Exec()
{
	if (error)
		return;
	for (vector<Alarm>::iterator it = LA.begin(); it != LA.end(); it++)
	{

		if (it->period != 0)
		{
			if (it->signal->Get() != it->need)
				error = true;
		}
		else
		{
			if (it->signal->WasConst(!it->need, it->period))
				error = true;
		}
		if (error == true)
		{
			error = true;
			errorMsg = "Ошибка! ";
			if (it->need)
				errorMsg += "Пропал";
			else
				errorMsg += "Появился";
			errorMsg += " сигнал ";
			errorMsg += it->signal->GetName();
			return;
		}
	}
}

//---------------------------------------------------------------------------
void Job::Reset(void)
{
	error = false;
	errorMsg = "";
	LA.clear();
}

//---------------------------------------------------------------------------
void Job::pr(AnsiString _msg)
{
	TPr::pr(_msg);
}

//---------------------------------------------------------------------------
void Job::ppr(AnsiString _msg)
{
	pr(_msg);
	SMSM::SetPost("STATUS2", _msg);
}

//---------------------------------------------------------------------------
bool Job::IsComplete()
{
	return (complete);
}

//---------------------------------------------------------------------------
void Job::SetError(AnsiString _msg)
{
	if (!error)
		errorMsg = _msg;
	error = true;
}
//---------------------------------------------------------------------------
