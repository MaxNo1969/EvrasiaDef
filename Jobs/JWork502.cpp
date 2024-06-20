// ---------------------------------------------------------------------------

#pragma hdrstop

#include "JWork502.h"
#include "SMSM.h"

// ---------------------------------------------------------------------------

#pragma package(smart_init)

JWork502::JWork502(IsWork _IW, Bank* _bank) : jZoner(_bank, _IW),
	Inv(PA("Defect.ComPortConverters")),
//	lineSpeed("Line", _IW.Line ? &Inv : NULL),
	thickSpeed("Thick", _IW.Thick ? &Inv : NULL), collect(_bank, _IW),
//	crossSolenoid(PA("Defect.Cross.Solenoid"), &collect),
//	lineSolenoid(PA("Defect.Line.Solenoid"), &collect),
//	thickSolenoid(PA("Thickness.Solenoid"), &collect),
	jTransport(_bank, _IW, NULL, &thickSpeed)
{
	IW = _IW;
	bank = _bank;
//	modBus.OnProtocol=pr;
	SLD->oTPCHPOW->Set(true);
	PA("Thickness.Work.Command").Write("None");
}

JWork502::~JWork502(void)
{
	pr("Finish() деструктор");
	Finish();
}

void JWork502::Finish(void)
{
	pr("Finish() inside");
	SLD->CatchStop();
	SLD->oCWORK->Set(false);
	SLD->oTWORK->Set(false);
	SLD->oTSCANPOW->Set(false);
	PA("Thickness.Work.Command").Write("None");
}

void JWork502::Exec()
{
	if (complete)
		return;
	if (error)
		return;
	DWORD tick = GetTickCount();
	Job::Exec();
	if (error)
	{
		ppr(GetErrorMsg());
		SMSM::SetPost("ERROR");
		return;
	}
//	lineSpeed.Exec();
//	if (lineSpeed.IsError())
//	{
//		SetError(lineSpeed.GetErrorMsg());
//		ppr(lineSpeed.GetErrorMsg());
//		SMSM::SetPost("ERROR");
//		return;
//	}
	jRectifier.Exec();
	if (jRectifier.IsError())
	{
		SetError(jRectifier.GetErrorMsg());
		ppr(jRectifier.GetErrorMsg());
		SMSM::SetPost("ERROR");
		return;
	}
	thickSpeed.Exec();
	if (thickSpeed.IsError())
	{
		SetError(thickSpeed.GetErrorMsg());
		ppr(thickSpeed.GetErrorMsg());
		SMSM::SetPost("ERROR");
		return;
	}
	collect.Exec(tick);
	if (collect.IsError())
	{
		SetError(collect.GetErrorMsg());
		ppr(collect.GetErrorMsg());
		SMSM::SetPost("ERROR");
		return;
	}
	jTransport.Exec(tick);
	if (jTransport.IsError())
	{
		SetError(jTransport.GetErrorMsg());
		ppr(jTransport.GetErrorMsg());
		SMSM::SetPost("ERROR");
		return;
	}
	jZoner.Exec();

	switch (step)
	{
	case 0:
		SMSM::SetPost("STATUS1", "Работа");
		ppr("");
		PA("Thickness.Work.Command").Write("None");
		AddAlarm(SLD->iCC, true, 50);
		ppr("Ждем ЦИКЛы бескончено");
		step = 1;
	case 1:
		if (IW.Cross)
		{
			if (!SLD->iCCYCLE->Get())
				break;
			AddAlarm(SLD->iCCYCLE, true);
		}
//		if (IW.Line)
//		{
//			if (!SLD->iLCYCLE->Get())
//				break;
//			AddAlarm(SLD->iLCYCLE, true);
//		}
		if (IW.Thick)
		{
			if (!SLD->iTCYCLE->Get())
				break;
			AddAlarm(SLD->iTCYCLE, true);
		}
//		if (IW.SG)
//		{
//			if (!SLD->iMPON->Get())
//				break;
//			AddAlarm(SLD->iMPON, true);
//		}
		step = 10;
		ppr("Ждем ГОТОВНОСТЬ бескончено");
	case 10:
		if (!SLD->iREADY->Get())
			break;
		SLD->oSHIFT->Set(false);
		SLD->oRESULT->Set(false);
		SLD->oSTROBE->Set(false);
		SMSM::SetPost("CLEAR");
		pr("Задержка 2с");
		Sleep(2000);
		if (IW.Thick)
			ppr("Ждем Толщиномер бесконечно");
		step = 2;
	case 2:
		if (IW.Thick)
		{
			if (PA("Thickness.Work.State").String() != "Ready")
				break;
		}
//		if (IW.Line)
//			lineSpeed.SetSpeed();
		if (IW.Thick)
			thickSpeed.SetSpeed();
		ppr("Ждем скорости");
		step = 3;
	case 3:
//		if (!lineSpeed.IsComplete())
//			break;
		if (!thickSpeed.IsComplete())
			break;
		ppr("Включаем магнитные поля");
		if(IW.Cross)
			jRectifier.Start('c');
		if(IW.Thick)
			jRectifier.Start('t');
//		if (IW.Cross)
//			SLD->oCSOLPOW->Set(true);
//		if (IW.Line)
//			SLD->oLSOLPOW->Set(true);
//		if (IW.Thick)
//			SLD->oTSOLPOW->Set(true);
//		ppr("Ждем магнитные поля 1 с");
//		startTick = tick;
//		step = 4;
//	case 4:
//		if (tick - startTick > 1000)
//		{
//			SetError("Не не дождались магнитных полей");
//			break;
//		}
//		if (IW.Cross)
//		{
//			if (!crossSolenoid.Ok())
//				break;
//		}
//		if (IW.Line)
//		{
//			if (!lineSolenoid.Ok())
//				break;
//		}
//		if (IW.Thick)
//		{
//			if (!thickSolenoid.Ok())
//				break;
//		}
		if (IW.Thick)
		{
			PA("Thickness.Work.Command").Write("Start");
			ppr("Ждем Работы толщиномера 10 с");
		}
		startTick = tick;
		step = 5;
	case 5:
		if (IW.Thick)
		{

			if (tick - startTick > 10000)
			{
				SetError("Не дождались работы Толщиномера за 10 с");
				break;
			}
			if (PA("Thickness.Work.State").String() != "Work")
				break;
		}
		PA("Thickness.Work.Command").Write("None");
		SLD->oSHIFT->Set(false);
		SLD->oRESULT->Set(false);
		SLD->oSTROBE->Set(false);
		SLD->oCWORK->Set(IW.Cross);
//		SLD->oLWORK->Set(IW.Line);
		SLD->oTWORK->Set(IW.Thick);
//		SLD->oMEASURE->Set(true);
		ppr("Включаем сканирующие");
//		SLD->oLSCANPOW->Set(IW.Line);
		SLD->oTSCANPOW->Set(IW.Thick);
		ppr("Ждем окончания сбора данных");
		SLD->CatchClear();
		SLD->CatchStart();
		jTransport.Start();
		collect.Start();
		jZoner.Start();
		bank->Start(IW);
		step = 6;
	case 6:
		if (!bank->IsComplete())
			break;
		if (IW.Thick)
			ppr("Ждем окончания работы Толщиномера");
		step = 7;
	case 7:
		if (IW.Thick)
		{
			if (PA("Thickness.Work.State").String() == "Work")
				break;
		}
		step = 8;
	case 8:
		ppr("Ждем снятия сигналов КОНТРОЛЬ");
		if (IW.Thick)
		{
			if (SLD->iTCONTROL->Get())
				break;
		}
//		if (IW.Line)
//		{
//			if (SLD->iLCONTROL->Get())
//				break;
//		}
		if (IW.Cross)
		{
			if (SLD->iCCONTROL->Get())
				break;
		}
		Finish();
		complete = true;
		ppr("Данные собраны");
		SMSM::SetPost("VIEW");
	}
	if (error)
	{
		ppr(GetErrorMsg());
		SMSM::SetPost("ERROR");
		return;
	}
}
