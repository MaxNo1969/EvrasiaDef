//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFRTEstSolenoid502.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRTEstSolenoid502 *FRTEstSolenoid502;

//---------------------------------------------------------------------------
__fastcall TFRTEstSolenoid502::TFRTEstSolenoid502(TComponent* Owner) : TFrame(Owner)
{
	lLinearResistance->Visible = !solenoid.ByTemp();
	ST_R->Visible = !solenoid.ByTemp();
	lLinearTemperature->Visible = solenoid.ByTemp();
	ST_T->Visible = solenoid.ByTemp();
	SOLPOW = NULL;
	StatusBarBottom->Font->Color=clRed;
}

//---------------------------------------------------------------------------
__fastcall TFRTEstSolenoid502::~TFRTEstSolenoid502(void)
{
	if (SOLPOW != NULL)
		SOLPOW->Set(false);
}

//---------------------------------------------------------------------------
void TFRTEstSolenoid502::Init(PA _pa, AnsiString _TypeOfControl, AnsiString _title, JCollect502* _jCollect502)
{
	Label1->Caption = _title;
	solenoid.LoadSettings(_pa);
	solenoid.jCollect = _jCollect502;

	lLinearResistance->Visible = !solenoid.ByTemp();
	ST_R->Visible = !solenoid.ByTemp();
	lLinearTemperature->Visible = solenoid.ByTemp();
	ST_T->Visible = solenoid.ByTemp();
//	if (_TypeOfControl == "Cross")
//		SOLPOW = SLD->oCSOLPOW;
//	else if (_TypeOfControl == "Line")
//		;
//	//		SOLPOW = SLD->oLSOLPOW;
//	else
//		SOLPOW = SLD->oTSOLPOW;
//	SOLPOW->Set(false);
}

//---------------------------------------------------------------------------
void TFRTEstSolenoid502::Exec(void)
{
	if (solenoid.jCollect == NULL)
		return;
	if (!SpeedButton1->Down)
		return;
	ST_I->Caption = FloatToStrF(solenoid.getAmperage(), ffFixed, 3, 0);
	ST_U->Caption = FloatToStrF(solenoid.getVoltage(), ffFixed, 3, 0);
	ST_R->Caption = FloatToStrF(solenoid.getResist(), ffFixed, 3, 0);
	ST_T->Caption = FloatToStrF(solenoid.getTemp(), ffFixed, 3, 0);

	ST_T->Font->Color = solenoid.OkTemp()? clBlack : clRed;
	ST_R->Font->Color = solenoid.OkResist()? clBlack : clRed;

	if(solenoid.ByTemp())
		StatusBarBottom->SimpleText=ST_T->Font->Color==clRed?"Превышение уровня":"";
	else
		StatusBarBottom->SimpleText=ST_R->Font->Color==clRed?"Превышение уровня":"";
	return;
}

//---------------------------------------------------------------------------
void __fastcall TFRTEstSolenoid502::SpeedButton1Click(TObject *Sender)
{
	if (solenoid.jCollect == NULL)
	{
		SpeedButton1->Down = false;
	}
	if (SpeedButton1->Down)
	{
		SOLPOW->Set(true);
		SpeedButton1->Caption = "Отключить";
	}
	else
	{
		SOLPOW->Set(false);
		ST_I->Caption = "";
		ST_U->Caption = "";
		ST_R->Caption = "";
		ST_T->Caption = "";
		SpeedButton1->Caption = "Включить";
	}

}
//---------------------------------------------------------------------------
