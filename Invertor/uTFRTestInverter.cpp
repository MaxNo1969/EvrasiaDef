//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRTestInverter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRTestInverter *FRTestInverter;

//---------------------------------------------------------------------------
__fastcall TFRTestInverter::TFRTestInverter(TComponent* Owner) : TFrame(Owner)
{
	inverter = NULL;
}

//---------------------------------------------------------------------------
__fastcall TFRTestInverter::~TFRTestInverter(void)
{
	if (inverter != NULL)
		delete inverter;
}

//---------------------------------------------------------------------------
void TFRTestInverter::Init(bool _line, CInv* _Inv)
{
	inverter = new Inverter(_line,_Inv);
	Label1->Caption = AnsiString("Абонент: ") + inverter->GetAbonent();
}

//---------------------------------------------------------------------------
void __fastcall TFRTestInverter::SpeedButton1Click(TObject *Sender)
{
	if (inverter == NULL)
	{
		SpeedButton1->Down = false;
		return;
	}
	if (SpeedButton1->Down)
	{
		if (!inverter->startRotation())
		{
			SpeedButton1->Down = false;
			prs(AnsiString("startRotation: Ошибка: ") + inverter->GetErrorMsg());
			return;
		}
		SpeedButton1->Caption = "Стоп";
		prs("startRotation: Ok");
	}
	else
	{
		if (!inverter->stopRotation())
		{
			prs(AnsiString("stopRotation: Ошибка: ") + inverter->GetErrorMsg());
			SpeedButton1->Down = true;
			return;
		}
		SpeedButton1->Caption = "Пуск";
		prs("stopRotation: Ok");
	}
}

//---------------------------------------------------------------------------
void TFRTestInverter::prs(AnsiString _msg)
{
	StatusBar1->SimpleText = _msg;
}
//---------------------------------------------------------------------------

void __fastcall TFRTestInverter::SpeedButton5Click(TObject *Sender)
{
	if (!inverter->ResetErrors())
		prs(AnsiString("ResetErrors: Ошибка: ") + inverter->GetErrorMsg());
	else
		prs("ResetErrors: Ok");
}

//---------------------------------------------------------------------------
void __fastcall TFRTestInverter::SpeedButton6Click(TObject *Sender)
{
	if (!inverter->NETManage())
		prs(AnsiString("NETManage: Ошибка: ") + inverter->GetErrorMsg());
	else
		prs("NETManage: Ok");
}
//---------------------------------------------------------------------------

void __fastcall TFRTestInverter::SpeedButton4Click(TObject *Sender)
{
	CInv::State state=inverter->stateRead();
	if(state.error)
		prs(AnsiString("stateRead: Ошибка: ") + inverter->GetErrorMsg());
	else
		prs(state.Tostring());
}
//---------------------------------------------------------------------------

void __fastcall TFRTestInverter::SpeedButton2Click(TObject *Sender)
{
	if (!inverter->setParameterSpeed(Edit1->Text.ToInt()))
		prs(AnsiString("SetParameterSpeed: Ошибка: ") + inverter->GetErrorMsg());
	else
		prs("setParameterSpeed: Ok");
}
//---------------------------------------------------------------------------

void __fastcall TFRTestInverter::SpeedButton3Click(TObject *Sender)
{
	int val = inverter->getParameterSpeed();
	if (val < 0)
		prs(AnsiString("getParameterSpeed: Ошибка: ") + inverter->GetErrorMsg());
	else
		prs("getParameterSpeed: Ok");
	Edit1->Text = val;
}
//---------------------------------------------------------------------------
void TFRTestInverter::SetTitle(AnsiString _title)
{
	Title->Caption=_title;
}

