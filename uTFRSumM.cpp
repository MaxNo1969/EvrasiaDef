// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRSumM.h"
#include "protocol.h"
#include "PA.h"
#include "Classer.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
*/
#pragma resource "*.dfm"
TFRSumM *FRSumM;

// ---------------------------------------------------------------------------
__fastcall TFRSumM::TFRSumM(TComponent* Owner) : TFrame(Owner)
{
	// Chart1->AllowPanning = TPanningMode::pmNone;
	OnChange = NULL;
	OnDecision = NULL;
	InMetr = true;
	if (!InMetr)
	{
		Chart1->BottomAxis->MinorGrid->Visible = false;
		Chart1->BottomAxis->MinorTickCount = 0;
	}
	isEnable = true;
	mult = 1;
	max_zones = 0;
}

// ---------------------------------------------------------------------------
void TFRSumM::Clear(void)
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
void TFRSumM::SetDecision(AnsiString _name, TColor _color, double _cut1,
	double _cut2)
{
	lResult->Caption = _name;
	lResult->Color = _color;
	if (_cut1 == 0)
		lCut1->Caption = "";
	else
	{
		AnsiString s;
		s.cat_printf("%0.1f", _cut1);
		lCut1->Caption = s;

	}
	if (_cut2 == 0)
		lCut2->Caption = "";
	else
	{
		AnsiString s;
		s.cat_printf("%0.1f", _cut2);
		lCut2->Caption = s;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TFRSumM::FrameResize(TObject *Sender)
{
	int space = 4;
	eMin_Good_Length->Left = ClientWidth - space - eMin_Good_Length->Width;
	Label8->Left = eMin_Good_Length->Left - space - Label8->Width;
	lCut2->Left = Label8->Left - space - lCut2->Width;
	Label9->Left = lCut2->Left - space * 3 - Label9->Width;
	lResult->Width = Label9->Left - space - lResult->Left;
}
// ---------------------------------------------------------------------------

void __fastcall TFRSumM::eMin_Good_LengthKeyDown(TObject *Sender, WORD &Key,
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
void __fastcall TFRSumM::eMin_Good_LengthExit(TObject *Sender)
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
void TFRSumM::Init(void)
{
	max_zones = PA("MaxZones").Int();
	ZoneLength=PA("ZoneSize").Int();
	if (InMetr)
	{
		mult = ZoneLength;
		mult /= 1000;
		Chart1->BottomAxis->Maximum = max_zones * mult;
	}
	else
	{
		mult=1;
		Chart1->BottomAxis->Maximum = max_zones;
	}
	LoadSettings();
}

// ---------------------------------------------------------------------------
void TFRSumM::LoadSettings(void)
{
	eMin_Good_Length->Text = PA("TSSet.Current.MinGoodLength").Int();
}

// ---------------------------------------------------------------------------
void TFRSumM::Save(void)
{
	PA("TSSet.Current.MinGoodLength").Write(eMin_Good_Length->Text.ToInt());
	if (OnChange != NULL)
		OnChange();
}

// ---------------------------------------------------------------------------

void __fastcall TFRSumM::lResultClick(TObject *Sender)
{
	if (!isEnable)
		return;
	if (OnDecision != NULL)
		OnDecision();
}

// ---------------------------------------------------------------------------
int TFRSumM::MinHeight(void)
{
	return (Panel1->Top + Label1->Top + Label1->Height);
}

// ---------------------------------------------------------------------------
void TFRSumM::SetEnabledR1(bool _v)
{
	eMin_Good_Length->Enabled = _v;
}

void TFRSumM::SetEnabledResult(bool _v)
{
	isEnable = _v;
}

void TFRSumM::SetTubeLenght(double _length)
{
	pNN->Caption = _length;
}

void TFRSumM::Draw(CTube* _Tube)
{
	CSum* SM = &_Tube->RSum;
	for (int z = 0; z <= max_zones; z++)
	{
		double pos = z * mult;
		if (z < SM->Size())
			Chart1->Series[0]->AddXY(pos, 1, "", Classer::ClassColor(SM->MZone[z]->DClass));
		else
			Chart1->Series[0]->AddXY(pos, 0, "", clWhite);
	}
	double dcut1 = SM->cut1;
	dcut1 *= ZoneLength;
	dcut1 /= 1000;
	double dcut2 = 0;
	if (SM->cut2 != 0)
	{
		dcut2 = SM->Size() - SM->cut2 + 1;
		dcut2 *= ZoneLength;
		dcut2 /= 1000;
		dcut2 = -dcut2;
	}
	SetDecision(Classer::ClassString(SM->DClass), Classer::ClassColor(SM->DClass), dcut1, dcut2);
	pr(AnsiString("Draw: нарисовали зон: ")+SM->Size());
}
void TFRSumM::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("TFRSumM: ")+_msg);
}


