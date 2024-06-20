// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRBorders.h"
#include "Protocol.h"
#include "uFunctions.h"
#include "Filters.h"
#include "PA.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRBorders *FRBorders;

// ---------------------------------------------------------------------------
__fastcall TFRBorders::TFRBorders(TComponent* Owner) : TFrame(Owner)
{
	SetInner(false);
	inner = false;
	OnChange = NULL;
	tp="";
}

// ---------------------------------------------------------------------------
void TFRBorders::SetInner(bool _v)
{
	EBorder11->Visible = _v;
	EBorder21->Visible = _v;
	LBorder1->Visible = _v;
	LBorder2->Visible = _v;
}

void TFRBorders::Init(AnsiString _tp)
{
	tp = _tp;
	LoadSettings();
}
void TFRBorders::LoadSettings(void)
{
	if(tp.Length()==0)
		return;
	inner = LinearFilterIn->IsFilter();
	if (tp == "Cross")
	{
		SetInner(false);
		PA pa("TSSet.Current.TSDef.Cross");
		EBorder10->Text = pa.Item("Border1").Double();
		EBorder20->Text = pa.Item("Border2").Double();
	}
	else if (tp == "Thick")
	{
		SetInner(false);
		PA pa("TSSet.Current.TSThick");
		EBorder10->Text = pa.Item("Border1").Double();
		EBorder20->Text = pa.Item("Border2").Double();
	}
	else if (tp == "Line")
	{
		SetInner(inner);
		PA pa("TSSet.Current.TSDef.Line");
		EBorder10->Text = pa.Item("Border1").Double();
		EBorder20->Text = pa.Item("Border2").Double();
		if (inner)
		{
			EBorder11->Text = pa.Item("Border1In").Double();
			EBorder21->Text = pa.Item("Border2In").Double();
		}
	}
	else
	{
		AnsiString a = "TFRBorders::Init: Не верный тип: ";
		a += tp;
		FATAL(a);
	}
}
void TFRBorders::Save(void)
{
	if (tp == "Cross")
	{
		PA pa("TSSet.Current.TSDef.Cross");
		pa.Item("Border1").Write(EBorder10->Text.ToDouble());
		pa.Item("Border2").Write(EBorder20->Text.ToDouble());
	}
	else if (tp == "Thick")
	{
		PA pa("TSSet.Current.TSThick");
		pa.Item("Border1").Write(EBorder10->Text.ToDouble());
		pa.Item("Border2").Write(EBorder20->Text.ToDouble());
	}
	else if (tp == "Line")
	{
		PA pa("TSSet.Current.TSDef.Line");
		pa.Item("Border1").Write(EBorder10->Text.ToDouble());
		pa.Item("Border2").Write(EBorder20->Text.ToDouble());
		if (inner)
		{
			pa.Item("Border1In").Write(EBorder11->Text.ToDouble());
			pa.Item("Border2In").Write(EBorder21->Text.ToDouble());
		}
	}
	if (OnChange != NULL)
		OnChange();
}

void __fastcall TFRBorders::EBorder10Exit(TObject *Sender)
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


void __fastcall TFRBorders::EBorder10KeyDown(TObject *Sender, WORD &Key,
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
