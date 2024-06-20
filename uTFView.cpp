// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFView.h"
#include "uFunctions.h"
#include "Protocol.h"
#include "PA.h"
#include "Filters.h"
#include "Classer.h"
#include <math.h>

#pragma package(smart_init)
/*
#pragma link "uTFRViewDev"
#pragma link "uTFRViewLDev"
*/
#pragma resource "*.dfm"

TFView *FView;

__fastcall TFView::TFView(TComponent* Owner, CTube* _Tube) : TForm(Owner)
{
	int CrossPos = -1; // Начальная позиция Поперечного
	int LinearPos = -1; // Начальная позиция Продольного
	GainEnable = true; // Начальная позиция Навального
	Tube = _Tube;
	CSensors = Tube->Cross.GetSensorsCount();
	LSensors = Tube->Line.GetSensorsCount();
	Tube->Cross.PushGains();
	Tube->Line.PushGains();
}

void __fastcall TFView::FormCreate(TObject *Sender)
{
	PA("Defect.Wins").LoadFormPos(this);
	inited = false;
	max_zones = PA("MaxZones").Int();
	ViewFormInit();
	SelectedColor = (TColor)PA("Colors.eSelectedZone").Int();
	need_repaint = false;
}

// ---------------------------------------------------------------------------
void __fastcall TFView::FormDestroy(TObject *Sender)
{
	PA("Defect.Some.RangeStep").Write(RangeValue());
	PA("Defect.Wins").SaveFormPos(this);
}
// ---------------------------------------------------------------------------

void TFView::ViewFormInit()
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

	FRViewLDevL->Init(Tube, CMeas::TP::Line, max_zones);
	FRViewLDevL->OnKeyDown = ViewLinearChartKeyDown;
	FRViewLDevL->OnClickSeries = LineMove;
	FRViewDevL->Init(Tube, CMeas::TP::Line, false);
	FRViewDevL->OnChangeGain = GainChangeL;
	FRViewDevL->SetInner(LinearFilterIn->IsFilter());
	FRViewDevL->SetStep(val);

	FormResize(this);
	FRViewLDevC->Draw();
	FRViewLDevL->Draw();

	Refresh();
}

int TFView::RangeIndex(double _val)
{
	for (int i = 0; i < CBStep->Items->Count; i++)
	{
		AnsiString s = CBStep->Items->Strings[i];
		if (CBStep->Items->Strings[i].ToDouble() == _val)
			return (i);
	}
	return (0);
}

double TFView::RangeValue()
{
	return (CBStep->Text.ToDouble());
}

void TFView::CrossMove(int _pos)
{
	FRViewLDevL->ColorZone(LinePos);
	LinePos = -1;
	FRViewDevL->Visible = false;

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

void TFView::LineMove(int _pos)
{
	FRViewLDevC->ColorZone(CrossPos);
	CrossPos = -1;
	FRViewDevC->Visible = false;

	FRViewLDevL->ColorZone(LinePos);
	LinePos = _pos;
	if (LinePos < -1)
		LinePos = -1;
	if (LinePos >= Tube->Line.Size())
		LinePos = Tube->Line.Size() - 1;
	if (LinePos < 0)
	{
		FRViewDevL->Visible = false;
		return;
	}
	FRViewDevL->Draw(LinePos);
	FRViewDevL->Visible = true;
	FRViewLDevL->ColorZone(LinePos, SelectedColor);
}

void __fastcall TFView::EditKeyPress(TObject *Sender, wchar_t &Key)
{
	if (!((Key >= '0' && Key <= '9') || (Key == VK_BACK) || (Key == ',')))
		Key = 0x00;
}

void __fastcall TFView::ViewCrossChartKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_ESCAPE)
		Close();
	else
	{
		if (Key == VK_UP || Key == VK_DOWN)
			LineMove(CrossPos);
		if (Key == VK_RIGHT)
			CrossMove(CrossPos + 1);
		else if (Key == VK_LEFT)
			CrossMove(CrossPos - 1);
	}
}

void __fastcall TFView::ViewLinearChartKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_ESCAPE)
		Close();
	else
	{
		if (Key == VK_UP || Key == VK_DOWN)
			CrossMove(LinePos);
		if (Key == VK_RIGHT)
			LineMove(LinePos + 1);
		else if (Key == VK_LEFT)
			LineMove(LinePos - 1);
	}
}

void __fastcall TFView::FormResize(TObject *Sender)
{
	if (!inited)
		return;

	FRViewLDevC->Width = ClientWidth - FRViewLDevC->Left;
	FRViewLDevL->Left = FRViewLDevC->Left;
	FRViewLDevL->Width = FRViewLDevC->Width;

	FRViewDevC->Left = FRViewLDevC->Left;
	FRViewDevC->Top = CBStep->Top + CBStep->Height;
	FRViewDevC->Width = FRViewLDevC->Width;
	FRViewDevC->Height = ClientHeight - FRViewDevC->Top;

	FRViewDevL->Left = FRViewDevC->Left;
	FRViewDevL->Top = FRViewDevC->Top;
	FRViewDevL->Width = FRViewDevC->Width;
	FRViewDevL->Height = FRViewDevC->Height;
}

void TFView::GainChangeC(int _sensor, double _gain)
{
	Tube->Cross.MSensor2[_sensor]->Gain = _gain;
	Tube->Cross.CalcClass();
	FRViewLDevC->ReDraw();
	CrossMove(CrossPos);
	Tube->Cross.FromFile = true; // чтобы нельзя было подстроить для сверки
	need_repaint = true;
}

void TFView::GainChangeL(int _sensor, double _gain)
{
	Tube->Line.MSensor2[_sensor]->Gain = _gain;
	Tube->Line.CalcClass();
	FRViewLDevL->ReDraw();
	LineMove(LinePos);
	Tube->Line.FromFile = true; // чтобы нельзя было подстроить для сверки
	need_repaint = true;
}

void TFView::Calibrate(TFRViewZone* _arc)
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

void __fastcall TFView::CBStepChange(TObject *Sender)
{
	double val = StrToFloatDef(CBStep->Text, 1);
	FRViewDevC->SetStep(val);
	FRViewDevL->SetStep(val);
}

void __fastcall TFView::FormClose(TObject *Sender, TCloseAction &Action)
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
