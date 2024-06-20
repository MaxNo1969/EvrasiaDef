//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRDeads.h"
#include "uFunctions.h"
#include "PA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRDeads *FRDeads;

//---------------------------------------------------------------------------
__fastcall TFRDeads::TFRDeads(TComponent* Owner) : TFrame(Owner)
{
	OnChange = NULL;
	tpp = "";
}

//---------------------------------------------------------------------------
void __fastcall TFRDeads::EStartExit(TObject *Sender)
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

//---------------------------------------------------------------------------
void __fastcall TFRDeads::EStartKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
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

//---------------------------------------------------------------------------
void TFRDeads::Init(AnsiString _tp)
{
	tpp = _tp;
	LoadSettings();
}

//---------------------------------------------------------------------------
void TFRDeads::LoadSettings(void)
{
	if (tpp.Length() == 0)
		return;
	PA pa;
	if (tpp == "Cross")
		pa = PA("TSSet.Current.TSDef.Cross");
	else if (tpp == "Line")
		pa = PA("TSSet.Current.TSDef.Line");
	else
	{
		AnsiString a = "TFRDeads::Init: Не верный тип: ";
		a += tpp;
		FATAL(a);
	}
	EStart->Text = pa.Item("DeadZoneStart").Int();
	EFinish->Text = pa.Item("DeadZoneFinish").Int();
}

//---------------------------------------------------------------------------
void TFRDeads::Save(void)
{
	PA pa;
	if (tpp == "Cross")
		pa = PA("TSSet.Current.TSDef.Cross");
	else if (tpp == "Line")
		pa = PA("TSSet.Current.TSDef.Line");
	pa.Item("DeadZoneStart").Write(EStart->Text.ToInt());
	pa.Item("DeadZoneFinish").Write(EFinish->Text.ToInt());
	if (OnChange != NULL)
		OnChange();
}
