//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRThick.h"
#include "math.h"
#include "PA.h"
#include "Classer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "uTFRBorders"
#pragma link "uTFRSplit"
#pragma link "uTFRDefects"
*/
#pragma resource "*.dfm"
TFRThick *FRThick;

//---------------------------------------------------------------------------
__fastcall TFRThick::TFRThick(TComponent* Owner) : TFrame(Owner)
{
	OnChange = NULL;
	Chart1->AllowPanning = TPanningMode::pmNone;
	FRBordersThick->OnChange = OnChangeChild;
	SetDefects(0);
}

//---------------------------------------------------------------------------
void TFRThick::OnChangeChild(void)
{
	if (OnChange != NULL)
		OnChange();
}

//---------------------------------------------------------------------------
void TFRThick::Clear(void)
{
	for (int i = 0; i < Chart1->SeriesCount(); i++)
		Chart1->Series[i]->Clear();
	SetDefects(0);
	SetMinThick(0.0, 0);
}

//---------------------------------------------------------------------------
void TFRThick::Init(void)
{
	FRBordersThick->Init("Thick");
	Chart1->BottomAxis->Maximum = PA("MaxZones").Int();
	LoadSettings0();
	Chart1->LeftAxis->Minimum = 0;
	Chart1->LeftAxis->Maximum = 10;
}

//---------------------------------------------------------------------------
void TFRThick::LoadSettings0(void)
{
	cbThick->Checked = PA("Thickness.Work.IsWork").Bool();
	Chart1->LeftAxis->Maximum = PA("TSSet.Current.TSThick.MaxThickness").Int();
}

//---------------------------------------------------------------------------
void TFRThick::LoadSettings(void)
{
	LoadSettings0();
	FRBordersThick->LoadSettings();
}

//---------------------------------------------------------------------------
void TFRThick::SetEnabledR(bool _v)
{
	FRBordersThick->Enabled = _v;
	cbThick->Enabled=_v;
}

//---------------------------------------------------------------------------
void __fastcall TFRThick::FrameResize(TObject *Sender)
{
	int space = 4;
	Chart1->Left = 0;
	Chart1->Width = ClientWidth;
	Chart1->Top = FRBordersThick->Top + FRBordersThick->Height + space;
	Chart1->Height = ClientHeight - Chart1->Top;
}

//---------------------------------------------------------------------------
void TFRThick::SetDefects(int _val)
{
	FRDefects1->Set(_val);
}

//---------------------------------------------------------------------------
void TFRThick::SetMinThick(double _val, int _nn)
{
	if (_val == 0.0)
	{
		Panel2->Caption = "";
		Panel1->Caption = "";
	}
	else
	{
		AnsiString ss;
		double val = floor(_val * 10 + 0.5) / 10;
		ss.printf("%0.1f", val);
		Panel2->Caption = ss;
		Panel1->Caption = _nn;
	}
}

//---------------------------------------------------------------------------
void __fastcall TFRThick::cbThickClick(TObject *Sender)
{
	PA("Thickness.Work.IsWork").Write(cbThick->Checked);
	if (OnChange != NULL)
		OnChange();

}

//---------------------------------------------------------------------------
int TFRThick::MinHeight(void)
{
	return (Panel3->Top + Label3->Top + Label3->Height);
}
//---------------------------------------------------------------------------
void TFRThick::Draw(CTube* _Tube)
{
	Clear();
	int defects = 0;
	CThick* Thick=&_Tube->Thick;
	Clear();
	/* TODO : ѕроверить на всех Draw предварительную очистку */
	for (int z = 0; z < Chart1->BottomAxis->Maximum; z++)
	{
		if (z < Thick->Size())
		{
			CZoneThick* Z=Thick->MZone[z];
			Chart1->Series[0]->AddXY(z, Z->Level, "", Classer::ClassColor(Z->DClass));
			if (Z->DClass==0||Z->DClass==1)
				defects++;
		}
		else
			Chart1->Series[0]->Add(0, "", clWhite);
	}
	SetDefects(defects);
	if(Thick->Size()!=0)
		SetMinThick(Thick->MinThick,Thick->posMinThick+1);
}

