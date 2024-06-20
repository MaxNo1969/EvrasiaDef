// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFRRectifier.h"
#include "uFunctions.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRRectifier *FRRectifier;

// ---------------------------------------------------------------------------
__fastcall TFRRectifier::TFRRectifier(TComponent* Owner) : TFrame(Owner)
{
	jRectifier = NULL;
}

// ---------------------------------------------------------------------------
__fastcall TFRRectifier::~TFRRectifier(void)
{
}

void TFRRectifier::Clear(void)
{
	if (jRectifier != NULL)
	{
		if (!jRectifier->Stop(tp))
			FATAL("Не могу отключить выпрямитель");
	}
}

void TFRRectifier::Init(JRectifier* _jRectifier, char _tp)
{
	jRectifier=_jRectifier;
	tp=_tp;
	Clear();
	if (jRectifier->GetIU(tp) == 'U')
	{
		lLinearAmperage->Font->Color = clBlue;
		lLinearVoltage->Font->Color = clWindowText;
	}
	else
	{
		lLinearAmperage->Font->Color = clWindowText;
		lLinearVoltage->Font->Color = clBlue;
	}
}

void __fastcall TFRRectifier::SpeedButton1Click(TObject *Sender)
{
	if (jRectifier == NULL)
	{
		SpeedButton1->Down = false;
		return;
	}
	if (SpeedButton1->Down)
	{
		if (!jRectifier->Start(tp))
		{
			SpeedButton1->Down = false;
			prs(jRectifier->GetErrorMsg());
			return;
		}
		SpeedButton1->Caption = "Отключить";
	}
	else
	{
		if (!jRectifier->Stop(tp))
		{
			SpeedButton1->Down = false;
			prs(jRectifier->GetErrorMsg());
			return;
		}
		SpeedButton1->Caption = "Включить";
	}

}

void TFRRectifier::prs(AnsiString _msg)
{
	StatusBarBottom->SimpleText = _msg;
}

void TFRRectifier::Exec(void)
{
	if (jRectifier == NULL)
		return;
	jRectifier->Exec();
	Rectifier::State LastState=jRectifier->GetState(tp);
	if (!LastState.started)
		return;
	if (LastState.error)
	{
		prs(LastState.errorMsg);
		return;
	}
	ST_I->Caption = FloatToStrF(LastState.OutputCurrent, ffFixed, 3, 0);
	ST_U->Caption = FloatToStrF(LastState.OutputVoltage, ffFixed, 3, 0);
	ST_R->Caption = FloatToStrF(LastState.Resistance(), ffFixed, 3, 0);
	ST_Time->Caption=LastState.ResidualTime();
	ST_R->Font->Color =LastState.Overheat()?clRed:clWindowText;
}
