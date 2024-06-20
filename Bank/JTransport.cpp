#pragma hdrstop
#include "JTransport.h"
#include "SignalListDef.h"
#include "protocol.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
JTransport::Point::Point(TIniFile* _ini, CSignal* _signal, bool _On)
{
	On = _On;
	tick = 0;
	signal = _signal;
	position = _ini->ReadInteger("Dimensions", _signal->hint, 0);
}

// ---------------------------------------------------------------------------
AnsiString JTransport::Point::ToString(void)
{
	AnsiString a = signal->hint;
	a += " ";
	a += (On ? "On" : "Off");
	a += " ";
	a += (int)position;
	a += " ";
	a += tick;
	return (a);
}

// ---------------------------------------------------------------------------
bool JTransport::Point::Check(bool _half)
{
	if (tick == 0)
	{
		CSignal::ValCh vc;
		bool ret = false;
		if (On)
		{
			vc = signal->GetCh();
			ret = vc.value;
		}
		else if (_half)
		{
			vc = signal->GetCh();
			ret = !vc.value;
		}
		if (ret)
			tick = vc.last_changed;
		return (ret);
	}
	return (false);
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
JTransport::JTransport(TIniFile* _ini, Bank* _bank, bool _IsThick,
	bool _IsCross, bool _IsLine)
{
	IsThick = _IsThick;
	IsCross = _IsCross;
	IsLine = _IsLine;

	bank = _bank;
	MP.reserve(10);

	// MP.push_back(Point(_ini, SLD->iBASE1_TS, true));
	if (IsThick)
	{
		MP.push_back(Point(_ini, SLD->iSQTIN, true));
		MP.push_back(Point(_ini, SLD->iSQTOUT, true));
	}
	if (IsCross)
	{
		MP.push_back(Point(_ini, SLD->iSQCIN, true));
		MP.push_back(Point(_ini, SLD->iSQCOUT, true));
	}
	if (IsLine)
	{
		MP.push_back(Point(_ini, SLD->iSQLIN, true));
		MP.push_back(Point(_ini, SLD->iSQLOUT, true));
	}
	MP.push_back(Point(_ini, SLD->iBASE2_TS, true));

	MP.push_back(Point(_ini, SLD->iBASE1_TS, false));
	if (IsThick)
	{
		MP.push_back(Point(_ini, SLD->iSQTIN, false));
		MP.push_back(Point(_ini, SLD->iSQTOUT, false));
	}
	if (IsCross)
	{
		MP.push_back(Point(_ini, SLD->iSQCIN, false));
		MP.push_back(Point(_ini, SLD->iSQCOUT, false));
	}
	if (IsLine)
	{
		MP.push_back(Point(_ini, SLD->iSQLIN, false));
		MP.push_back(Point(_ini, SLD->iSQLOUT, false));
	}
	MP.push_back(Point(_ini, SLD->iBASE2_TS, false));

	TubeSpeed_mm_ms = _ini->ReadInteger(" Default ", " TestTubeSpeed ", 350);
	TubeSpeed_mm_ms /= 1000;
	TubeLengthTest = _ini->ReadInteger(" Default ", " TestTubeLength ", 9000);
	TubeLength = 0;
	startTick = 0;
	started = false;
	error = false;
	errorMsg = " ";
	p_length_test = Find(SLD->iBASE1_TS, false);
	if (IsLine)
		p_speed0 = Find(SLD->iSQLOUT, true);
	else if (IsCross)
		p_speed0 = Find(SLD->iSQCOUT, true);
	if (IsThick)
		p_speed0 = Find(SLD->iSQTOUT, true);
	p_speed1 = Find(SLD->iBASE2_TS, true);
	p_base2_on = Find(SLD->iBASE2_TS, true);
	p_base1_off = Find(SLD->iBASE1_TS, false);
	p_half = Find(SLD->iBASE2_TS, true);
	half = false;
}

// ---------------------------------------------------------------------------
JTransport::Point* JTransport::Find(CSignal* _signal, bool _On)
{
	for (unsigned int i = 0; i < MP.size(); i++)
	{
		if (MP[i].signal == _signal && MP[i].On == _On)
			return (&MP[i]);
	}
	return (NULL);
}

// ---------------------------------------------------------------------------
bool JTransport::ExecTest(DWORD _tick)
{
	if (startTick == 0)
	{
		startTick = _tick + 2000;
		startTick = _tick;
		for (unsigned int i = 0; i < MP.size(); i++)
		{
			if (MP[i].On)
				MP[i].tick =
					(DWORD)(startTick + MP[i].position / TubeSpeed_mm_ms);
			else
				MP[i].tick =
					(DWORD)(startTick + (MP[i].position + TubeLengthTest)
				/ TubeSpeed_mm_ms);
		}
	}
	for (unsigned int i = 0; i < MP.size(); i++)
	{
		Point* p = &MP[i];
		if (p->tick != 0)
		{
			if (p->tick <= _tick)
			{
				if (p->On)
					bank->AddTickPosition(p->tick, p->position);
				else
					bank->AddTickPosition(p->tick,
					p->position + TubeLengthTest);
				p->tick = 0;
				pr(p->ToString());
				if (p == p_length_test)
					bank->SetTubeLength((int)TubeLengthTest);
			}
		}
	}
	if (MP[MP.size() - 1].tick == 0)
		pr(" Finished ");
	return (MP[MP.size() - 1].tick != 0);
}

// ---------------------------------------------------------------------------
bool JTransport::Exec(DWORD _tick)
{
	if (!started)
		return (true);
	if (error)
		return (true);
	for (unsigned int i = 0; i < MP.size(); i++)
	{
		Point* p = &MP[i];
		if (p->Check(half))
		{
			pr(p->ToString());
			if (i > 0)
			{
				Point* p_prev = &MP[i - 1];
				if (p_prev->tick == 0)
				{
					error = true;
					errorMsg = p->signal->hint;
					errorMsg += " ";
					errorMsg += p->On ? "установлен" : "снят";
					errorMsg += " раньше, чем ";
					errorMsg += p_prev->On ? "установлен" : "снят";
					errorMsg += " ";
					errorMsg += p_prev->signal->hint;
					pr(errorMsg);
					return (true);
				}
			}
			if (p == p_base1_off)
			{
				double S = p_speed1->position - p_speed0->position;
				double T = p_speed1->tick - p_speed0->tick;
				double V = S / T;

				pr("A1");
				pr(p_base2_on->tick);
				pr("A2");
				pr(p_base1_off->tick);
				pr("A3");
				double Tl = p_base1_off->tick - p_base2_on->tick;
				double Sl = V * Tl;
				TubeLength =
					(int)(Sl + p_base2_on->position - p_base1_off->position);
				bank->SetTubeLength((int)TubeLength);
				AnsiString a = " ";
				a.printf(" V(% 0.3f) = S(% 0.3f) / T(% 0.3f)", V, S, T);
				pr(a);
				a.printf(" Sl(% 0.3f) = V(% 0.3f) * Tl(% 0.3f)", Sl, V, Tl);
				pr(a);
				a.printf(" length = % d ", TubeLength);
				pr(a);
			}
			bank->AddTickPosition(p->tick, p->position + TubeLength);
			if (p == p_half)
				half = true;
		}
	}
	return (MP[MP.size() - 1].tick != 0);
}

// ---------------------------------------------------------------------------
void JTransport::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("TRT: ") + _msg);
}

// ---------------------------------------------------------------------------
void JTransport::Start(void)
{
	started = true;
	for (unsigned int i = 0; i < MP.size(); i++)
	{
		Point* p = &MP[i];
		p->tick = 0;
	}
}

// ---------------------------------------------------------------------------
void JTransport::Report(void)
{
	for (unsigned int i = 0; i < MP.size(); i++)
	{
		pr(MP[i].ToString());
	}
}
// ---------------------------------------------------------------------------
