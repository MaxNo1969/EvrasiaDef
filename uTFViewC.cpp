// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFViewC.h"
#include "uFunctions.h"
#include "Protocol.h"
#include "PA.h"
#include "Filters.h"
#include "Classer.h"
#include <math.h>

#pragma package(smart_init)
#pragma link "uTFRViewDev"
#pragma link "uTFRViewLDev"
#pragma resource "*.dfm"

TFViewC *FViewC;

__fastcall TFViewC::TFViewC(TComponent* Owner, CTube* _Tube) : TForm(Owner)
{
	int CrossPos = -1; // Начальная позиция Поперечного
	int LinearPos = -1; // Начальная позиция Продольного
	GainEnable = true; // Начальная позиция Навального
	Tube = _Tube;
	CSensors = Tube->Cross.GetSensorsCount();
	Tube->Cross.PushGains();
	Tube->Line.PushGains();
}

void __fastcall TFViewC::FormCreate(TObject *Sender)
{
	PA("Defect.Wins").LoadFormPos(this);
	inited = false;
	max_zones = PA("MaxZones").Int();
	ViewFormInit();
	SelectedColor = (TColor)PA("Colors.eSelectedZone").Int();
	need_repaint = false;
}

// ---------------------------------------------------------------------------
void __fastcall TFViewC::FormDestroy(TObject *Sender)
{
	PA("Defect.Some.RangeStep").Write(RangeValue());
	PA("Defect.Wins").SaveFormPos(this);
}
// ---------------------------------------------------------------------------

void TFViewC::ViewFormInit()
{
	inited = true;
	CBStep->ItemIndex = RangeIndex(PA("Defect.Some.RangeStep").Double());
	if (CBStep->ItemIndex < 0)
		CBStep->ItemIndex = 0;
	double val = StrToFloatDef(CBStep->Text, 1);

	FRViewLDevC->Init(Tube, CMeas::TP::Cross, max_zones);
	FRViewLDevC->OnKeyDown = ViewCrossChartKeyDown;
	FRViewLDevC->OnClickSeries = CrossMove;
	FRViewDevC->Init(Tube, CMeas::TP::Cross, true);
	FRViewDevC->OnChangeGain = GainChangeC;
	FRViewDevC->OnCalibrate = Calibrate;
	FRViewDevC->SetStep(val);

	FormResize(this);
	FRViewLDevC->Draw();

	Refresh();
}

int TFViewC::RangeIndex(double _val)
{
	for (int i = 0; i < CBStep->Items->Count; i++)
	{
		AnsiString s = CBStep->Items->Strings[i];
		if (CBStep->Items->Strings[i].ToDouble() == _val)
			return (i);
	}
	return (0);
}

double TFViewC::RangeValue()
{
	return (CBStep->Text.ToDouble());
}

void TFViewC::CrossMove(int _pos)
{
	LinePos = -1;

	FRViewLDevC->ColorZone(CrossPos);
	CrossPos = _pos;
	if (CrossPos < -1)
		CrossPos = -1;
	if (CrossPos >= Tube->Cross.MZone.Count())
		CrossPos = Tube->Cross.MZone.Count() - 1;
	if (CrossPos < 0)
	{
		FRViewDevC->Visible = false;
		return;
	}
	FRViewDevC->Draw(CrossPos);
	FRViewDevC->Visible = true;
	FRViewLDevC->ColorZone(CrossPos, SelectedColor);
}

void __fastcall TFViewC::EditKeyPress(TObject *Sender, wchar_t &Key)
{
	if (!((Key >= '0' && Key <= '9') || (Key == VK_BACK) || (Key == ',')))
		Key = 0x00;
}

void __fastcall TFViewC::ViewCrossChartKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_ESCAPE)
		Close();
	else
	{
		if (Key == VK_RIGHT)
			CrossMove(CrossPos + 1);
		else if (Key == VK_LEFT)
			CrossMove(CrossPos - 1);
	}
}


void __fastcall TFViewC::FormResize(TObject *Sender)
{
	if (!inited)
		return;

	FRViewLDevC->Width = ClientWidth - FRViewLDevC->Left;

	FRViewDevC->Left = FRViewLDevC->Left;
	FRViewDevC->Top = CBStep->Top + CBStep->Height;
	FRViewDevC->Width = FRViewLDevC->Width;
	FRViewDevC->Height = ClientHeight - FRViewDevC->Top;
}

void TFViewC::GainChangeC(int _sensor, double _gain)
{
	Tube->Cross.MSensor2[_sensor]->Gain = _gain;
	Tube->Cross.CalcClass();
	FRViewLDevC->ReDraw();
	CrossMove(CrossPos);
	Tube->Cross.FromFile = true; // чтобы нельзя было подстроить для сверки
	need_repaint = true;
}

void TFViewC::Calibrate(TFRViewZone* _arc)
{
	bool* mb = new bool[CSensors];
	for (int s = 0; s < CSensors; s++)
		mb[s] = FRViewDevC->NeedCalibrate(s);
	Tube->Cross.Calibrate(CrossPos, _arc->GetSensor(), mb);
	delete mb;
	Tube->Cross.FromFile = true; // чтобы нельзя было подстроить для сверки
	need_repaint = true;
	Tube->Cross.CalcClass();
	FRViewLDevC->ReDraw();
	CrossMove(CrossPos);
}

void __fastcall TFViewC::CBStepChange(TObject *Sender)
{
	double val = StrToFloatDef(CBStep->Text, 1);
	FRViewDevC->SetStep(val);
}

void __fastcall TFViewC::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (need_repaint)
	{
		if (Application->MessageBoxW(L"Сохранить настройки", L"Сохранение", MB_YESNO) == IDNO)
		{
			Tube->Cross.PopGains();
			Tube->Line.PopGains();
			Tube->Cross.CalcClass();
			Tube->Line.CalcClass();
			Tube->CalcSum();
		}
		else
		{
			Tube->Cross.SaveGain();
			Tube->Line.SaveGain();
		}
	}
}
