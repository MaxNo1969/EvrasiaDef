// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRSum.h"
#include "protocol.h"
#include "PA.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
*/
#pragma resource "*.dfm"
TFRSum *FRSum;

// ---------------------------------------------------------------------------
__fastcall TFRSum::TFRSum(TComponent* Owner) : TFrame(Owner)
{
	Chart1->AllowPanning = TPanningMode::pmNone;
	OnChange = NULL;
}

// ---------------------------------------------------------------------------
void TFRSum::Clear(void)
{
	for (int i = 0; i < Chart1->SeriesCount(); i++)
		Chart1->Series[i]->Clear();
	lResult->Caption = "";
	lResult->Color = clBtnFace;
	lCut1->Caption = "";
	lCut2->Caption = "";
	pNN->Caption = "";
}

// ---------------------------------------------------------------------------
void TFRSum::SetDecision(AnsiString _name, TColor _color, int _cut1, int _cut2)
{
	lResult->Caption = _name;
	lResult->Color = _color;
	if (_cut1 == 0)
		lCut1->Caption = "";
	else
		lCut1->Caption = _cut1;
	if (_cut2 == 0)
		lCut2->Caption = "";
	else
		lCut2->Caption = _cut2;
}
// ---------------------------------------------------------------------------
void __fastcall TFRSum::FrameResize(TObject *Sender)
{
	int space = 4;
	eMin_Good_Length->Left = ClientWidth - space - eMin_Good_Length->Width;
	Label8->Left = eMin_Good_Length->Left - space - Label8->Width;
	lCut2->Left = Label8->Left - space - lCut2->Width;
	Label9->Left = lCut2->Left - space * 3 - Label9->Width;
	lResult->Width = Label9->Left - space - lResult->Left;
}
// ---------------------------------------------------------------------------

void __fastcall TFRSum::eMin_Good_LengthKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)

{
	TEdit* p = (TEdit*)Sender;
	if (Key == VK_RETURN)
	{
		double ret = (double)StrToFloatDef(p->Text, -1);
		if (ret < 0)
		{
			p->Font->Color = clHotLight;
			p->Font->Style = TFontStyles() << fsBold;
			return;
		}
		p->Font->Color = clWindowText;
		p->Font->Style = TFontStyles();
		Save();
	}
	else
	{
		p->Font->Color = clHotLight;
		p->Font->Style = TFontStyles() << fsBold;
	}

}

// ---------------------------------------------------------------------------
void __fastcall TFRSum::eMin_Good_LengthExit(TObject *Sender)
{
	TEdit* p = (TEdit*)Sender;
	double ret = (double)StrToFloatDef(p->Text, -1);
	if (ret < 0)
	{
		p->SetFocus();
		return;
	}
	p->Font->Color = clWindowText;
	p->Font->Style = TFontStyles();
	Save();
}

// ---------------------------------------------------------------------------
void TFRSum::Init(void)
{
	Chart1->BottomAxis->Maximum = PA("MaxZones").Int();
	LoadSettings();
}

// ---------------------------------------------------------------------------
void TFRSum::LoadSettings(void)
{
	eMin_Good_Length->Text = PA("TSSet.Current.MinGoodLength").Int();
}

// ---------------------------------------------------------------------------
void TFRSum::Save(void)
{
	PA("TSSet.Current.MinGoodLength").Write(eMin_Good_Length->Text.ToInt());
	if (OnChange != NULL)
		OnChange();
}

// ---------------------------------------------------------------------------



