#pragma hdrstop
#include "JTransport502.h"
#include "SignalListDef.h"
#include "Protocol.h"
#include "PA.h"
#include "CatchTTL.h"
#pragma package(smart_init)

JTransport502::JTransport502(Bank* _bank, IsWork _IW, JSpeed502* _lineSpeed,
	JSpeed502* _thickSpeed)
{
	lineSpeed = _lineSpeed;
	thickSpeed = _thickSpeed;
	L = new TList();
	DimensionPars Pars;
	ZoneLength = PA("ZoneSize").Int();
	TimeoutSG = PA("Defect.SolidGroup.Timeout").Int() * 1000;
	IW = _IW;
#ifdef TTL_SIGNALS
	SetL502(&Pars);
#else
	SetA1730(&Pars);
#endif;
	teSGOn = NULL;
	teSGOff = NULL;
	// #ifdef RADOP
	// if (IW.SG)
	// {
	// teSGOn = new TESignal(SLD->iMPTUBE, true, Pars.SGSensors);
	// teSGOff = new TESignal(SLD->iMPTUBE, false, Pars.SGSensors);
	// }
	// #endif

	startTick = 0;
	testLastZone = 0;
	step = 0;
	TubeSpeed_mm_ms = PA("Some.TestTubeSpeed").Int();
	TubeSpeed_mm_ms /= 1000;
	TubeLengthTest = PA("Some.TestTubeLength").Int();
	bank = _bank;
	error = false;
	errorMsg = "";
}

void JTransport502::SetL502(DimensionPars* Pars)
{
	if (IW.Thick)
	{
		teOn = new TESignal(CatchTTL::ByName("TCONTROL"), true, Pars->TIn);
		teOff0 = new TESignal(CatchTTL::ByName("TCONTROL"), false, Pars->TOut);
	}
	else if (IW.Cross)
	{
		teOn = new TESignal(CatchTTL::ByName("CCONTROL"), true, Pars->CIn);
		teOff0 = new TESignal(CatchTTL::ByName("CCONTROL"), false, Pars->COut);
	}
	else if (IW.Line)
	{
		teOn = new TESignal(CatchTTL::ByName("LCONTROL"), true, Pars->LIn);
		teOff0 = new TESignal(CatchTTL::ByName("LCONTROL"), false, Pars->LOut);
	}
	else
	{
		teOn = NULL;
		teOff0 = NULL;
	}
	if (teOn != NULL)
	{
		teStrobe = new TEStrobe(CatchTTL::ByName("STROBE"), true,
			teOn->Position(), ZoneLength);
	}
	else
	{
		teStrobe = NULL;
	}

	if (IW.Line)
		teOff1 = new TESignal(CatchTTL::ByName("LCONTROL"), false, Pars->LOut);
	else if (IW.Cross)
		teOff1 = new TESignal(CatchTTL::ByName("CCONTROL"), false, Pars->COut);
	else if (IW.Thick)
		teOff1 = new TESignal(CatchTTL::ByName("TCONTROL"), false, Pars->TOut);
	else
		teOff1 = NULL;
	if (teOff0 != NULL && teOff1 != NULL)
	{
		if (teOff0->Position() == teOff1->Position())
		{
			delete teOff1;
			teOff1 = NULL;
		}
	}
	teTC_On = NULL;
	teTC_Off = NULL;

	teLC_On = NULL;
	teLC_Off = NULL;

	if (IW.Thick)
	{
		teTC_On = new TESignal(CatchTTL::ByName("TCONTROL"), true, 0);
		teTC_Off = new TESignal(CatchTTL::ByName("TCONTROL"), false, 0);
	}
	if (IW.Line)
	{
		teLC_On = new TESignal(CatchTTL::ByName("LCONTROL"), true, 0);
		teLC_Off = new TESignal(CatchTTL::ByName("LCONTROL"), false, 0);
	}
}

void JTransport502::SetA1730(DimensionPars* Pars)
{
	if (IW.Thick)
	{
		teOn = new TESignal(SLD->iTCONTROL, true, Pars->TIn);
		teOff0 = new TESignal(SLD->iTCONTROL, false, Pars->TOut);
	}
	else if (IW.Cross)
	{
		teOn = new TESignal(SLD->iCCONTROL, true, Pars->CIn);
		teOff0 = new TESignal(SLD->iCCONTROL, false, Pars->COut);
	}
	// else if (IW.Line)
	// {
	// teOn = new TESignal(SLD->iLCONTROL, true, Pars->LIn);
	// teOff0 = new TESignal(SLD->iLCONTROL, false, Pars->LOut);
	// }
	else
	{
		teOn = NULL;
		teOff0 = NULL;
	}
	if (teOn != NULL)
	{
		teStrobe = new TEStrobe(SLD->iSTROBE, true, teOn->Position(),
		ZoneLength);
	}
	else
	{
		teStrobe = NULL;
	}

	// if (IW.Line)
	// teOff1 = new TESignal(SLD->iLCONTROL, false, Pars->LOut);
	// else if (IW.Cross)
	if (IW.Cross)
		teOff1 = new TESignal(SLD->iCCONTROL, false, Pars->COut);
	else if (IW.Thick)
		teOff1 = new TESignal(SLD->iTCONTROL, false, Pars->TOut);
	else
		teOff1 = NULL;
	if (teOff0 != NULL && teOff1 != NULL)
	{
		if (teOff0->Position() == teOff1->Position())
		{
			delete teOff1;
			teOff1 = NULL;
		}
	}
	teTC_On = NULL;
	teTC_Off = NULL;

	teLC_On = NULL;
	teLC_Off = NULL;

	if (IW.Thick)
	{
		teTC_On = new TESignal(SLD->iTCONTROL, true, 0);
		teTC_Off = new TESignal(SLD->iTCONTROL, false, 0);
	}
	// if (IW.Line)
	// {
	// teLC_On = new TESignal(SLD->iLCONTROL, true, 0);
	// teLC_Off = new TESignal(SLD->iLCONTROL, false, 0);
	// }
}

JTransport502::~JTransport502(void)
{
	if (teOn != NULL)
		delete teOn;
	if (teOff0 != NULL)
		delete teOff0;
	if (teOff1 != NULL)
		delete teOff1;
	if (teStrobe != NULL)
		delete teStrobe;
	if (teSGOn != NULL)
		delete teSGOn;
	if (teSGOff != NULL)
		delete teSGOff;
	for (int i = 0; i < L->Count; i++)
		delete(Bank::TickPosition*)L->Items[i];
	delete L;
}

void JTransport502::Start(void)
{
	startTick = GetTickCount();
	testLastZone = 0;
	step = 0;
	started = true;
}

int JTransport502::CalcDelta(DWORD _tick)
{
	double V = teStrobe->Speed();
	double T = _tick - teStrobe->When();
	int S = (int)(V * T);
	pr(AnsiString("Delta: V=") + V);
	pr(AnsiString("Delta: T=") + T);
	pr(AnsiString("Delta: S=") + S);
	return (S);
}

bool JTransport502::Exec(DWORD _tick)
{
	if (!started)
		return (true);
	for (; ;)
	{
		SignalEvent* event = SLD->CatchGetNext();
		if (event == NULL)
			break;
		if (teOn != NULL)
		{
			switch (step)
			{
			case 0:
					// Ждем начала
				if (!teOn->Check(event))
					break;
				pr(teOn->ToString());
				L->Add(new Bank::TickPosition(teOn->When(), teOn->Position()));
				teStrobe->first_tick = teOn->When();
				step = 2;
			case 2:
					// Собираем стробы
				if (teStrobe->Check(event))
				{
					pr(teStrobe->ToString());
					L->Add(new Bank::TickPosition(teStrobe->When(),
						teStrobe->Position()));
				}
				if (!teOff0->Check(event))
					break;
				// Если снялся контроль - вычисляем длину трубы.
				pr(teOff0->ToString());
				{
					int curr_position =
						teStrobe->Position() + CalcDelta(teOff0->When());
					int TubeLength = curr_position - teOff0->Position();
					pr(AnsiString("TubeLength=") + TubeLength);
					pr(AnsiString("TubeLength1=") + (TubeLength + 1));
					bank->SetTubeLength(TubeLength);
					L->Add(new Bank::TickPosition(teOff0->When(),
						curr_position + 1));
				} step = 3;
				if (teOff1 == NULL)
				{
					step = 4;
					break;
				}
			case 3:
					// Собираем стробы
				if (teStrobe->Check(event))
				{
					pr(teStrobe->ToString());
					L->Add(new Bank::TickPosition(teStrobe->When(),
						teStrobe->Position()));
				}
				if (!teOff1->Check(event))
					break;
				// Если пришел последний контроль - завершаем работу
				pr(teOff1->ToString());
				L->Add(new Bank::TickPosition(teOff1->When(),
					teStrobe->Position() + CalcDelta(teOff1->When())));
				step = 4;
			case 4:
				break;
			}
			if (teOff0->Was())
			{
				// Если Знаем конец трубы - сбрасываем зоны в банк
				for (int i = 0; i < L->Count; i++)
				{
					Bank::TickPosition* p = (Bank::TickPosition*)L->Items[i];
					bank->AddTickPosition(p->tick, p->position);
					delete p;
				}
				L->Clear();
			}
			else
			{
				// Если НЕ знаем конец трубы - сбрасываем в банк только те стробы,
				// после которых уже пришли стробы на длину, не менее длины
				// между первым и последним контролем.
				//
				// Иначе говоря зедержим тот строб, которым может оказаться за границей трубы, чтобы не выдать зону из воздуха.
				if (L->Count != 0)
				{
					Bank::TickPosition* p =
						(Bank::TickPosition*)L->Items[L->Count - 1];
					int last_position = p->position;
					for (; ;)
					{
						Bank::TickPosition* p =
							(Bank::TickPosition*)L->Items[0];
						if (last_position - p->position > teOff0->Position() -
							teOn->Position())
						{
							bank->AddTickPosition(p->tick, p->position);
							delete p;
							L->Remove(p);
						}
						else
						{
//							AnsiString a = "";
//							a += last_position;
//							a += "-";
//							a += p->position;
//							a+=">";
//							a+=teOff0->Position();
//							a+="-";
//							a+=teOn->Position();
//							pr(a);
							break;
						}
						if (L->Count == 0)
							break;
					}
				}
			}
		}
		if (teSGOn != NULL)
		{
			if (!teSGOn->Was())
			{
				if (teSGOn->Check(event))
				{
					pr(teSGOn->ToString());
					bank->FirstTickSG1(teSGOn->When());
					if (TimeoutSG > 0)
						bank->LastTickSG1(teSGOn->When() + TimeoutSG);
				}
			}
			else
			{
				if (TimeoutSG <= 0)
				{
					if (!teSGOff->Was())
					{
						if (teSGOff->Check(event))
						{
							pr(teSGOff->ToString());
							bank->LastTickSG1(teSGOff->When());

						}
					}
				}
			}
		}
		if (teTC_On != NULL)
		{
			if (!teTC_On->Was())
				teTC_On->Check(event);
			else
			{
				if (!teTC_Off->Was())
				{
					if (teTC_Off->Check(event))
					{
						thickSpeed->Reset();
						// SLD->oTSOLPOW->Set(false);
					}
				}
			}
		}
		// if (teLC_On != NULL)
		// {
		// if (!teLC_On->Was())
		// teLC_On->Check(event);
		// else
		// {
		// if (!teLC_Off->Was())
		// {
		// if (teLC_Off->Check(event))
		// {
		// lineSpeed->Reset();
		// SLD->oLSOLPOW->Set(false);
		// }
		// }
		// }
		// }
	}
	return (true);
}

bool JTransport502::ExecTest(DWORD _tick)
{
	if (!started)
		return (true);
	for (int i = testLastZone; ; i++)
	{
		int position = (i + 1) * ZoneLength;
		if (position > TubeLengthTest)
			return (false);
		double zoneperiod = ZoneLength / TubeSpeed_mm_ms;
		DWORD tick = startTick + (int)((i + 1) * zoneperiod);
		if (tick >= _tick)
			return (true);
		bank->AddTickPosition(tick, position);
		testLastZone = i + 1;
	}
	return (true);
}

void JTransport502::Report(void)
{
}

void JTransport502::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("JTransport502: ") + _msg);
}
