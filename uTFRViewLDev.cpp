// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRViewLDev.h"
#include <VCLTee.Series.hpp>
#include "Classer.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#pragma link "Chart"
#pragma link "TeEngine"
#pragma link "TeeProcs"
*/
#pragma resource "*.dfm"
TFRViewLDev *FRViewLDev;

// ---------------------------------------------------------------------------
__fastcall TFRViewLDev::TFRViewLDev(TComponent* Owner) : TFrame(Owner)
{
	onClickSeries = NULL;
}

// ---------------------------------------------------------------------------
void TFRViewLDev::Init(CTube* _Tube, CMeas::TP _Tp, int _max_zones)
{
	Tube = _Tube;
	CL = (_Tp == CMeas::TP::Cross) ? (CCrossLine*)&Tube->Cross : (CCrossLine*)&Tube->Line;
	max_zones = _max_zones;
	Head=(_Tp == CMeas::TP::Cross) ? "Поперечный контроль" : "Продольный контроль";
	Chart1->Title->Caption = Head;
	Chart1->BottomAxis->Visible = true;
	Chart1->BottomAxis->Automatic = false;
	Chart1->BottomAxis->Minimum = 0;
	Chart1->BottomAxis->Maximum = _max_zones;
	Chart1->LeftAxis->Visible = true;
	Chart1->LeftAxis->Automatic = false;
	Chart1->LeftAxis->Minimum = 0;
	Chart1->LeftAxis->Maximum = CL->MSensor2.Count();
	Chart1->BottomAxis->EndPosition = 99;
	for (int i = 0; i < CL->MSensor2.Count(); i++)
	{
		TBarSeries* s = new TBarSeries(Chart1);
		s->ParentChart = Chart1;
		Chart1->AddSeries(s);

		s->ColorEachPoint = true;
		s->Marks->Visible = false;
		s->BarWidthPercent = 100;
		s->Emboss->Color = 8553090;
		s->Emboss->HorizSize = 2;
		s->MultiBar = mbStacked;
		s->Shadow->Visible = false;
		s->SideMargins = false;
		s->XValues->Name = "X";
		s->XValues->Order = loAscending;
		s->YValues->Name = "Bar";
		s->YValues->Order = loNone;
		s->OffsetPercent = 50;
	}
}

void TFRViewLDev::Draw(void)
{
	Chart1->LeftAxis->Maximum = CL->MSensor2.Count();
	int zones = Tube->Cross.MZone.Count();
	for (int s = 0; s < CL->MSensor2.Count(); s++)
	{
		Chart1->Series[s]->Tag = s;
		Chart1->Series[s]->Clear();
		for (int z = 0; z < max_zones; z++)
			if (z < zones)
				Chart1->Series[s]->AddXY(z, 1, "", Classer::ClassColor(CL->MZone[z]->MSensor[s]->DClass));
			else
				Chart1->Series[s]->Add(0, "", clWhite);
	}
}

void TFRViewLDev::ReDraw(void)
{
	for (int z = 0; z < CL->MZone.Count(); z++)
	{
		CZone* Z = CL->MZone[z];
		for (int s = 0; s < CL->MSensor2.Count(); s++)
		{
			CSensor* S = Z->MSensor[s];
			Chart1->Series[s]->ValueColor[z] = Classer::ClassColor(S->DClass);
		}
	}
}

void TFRViewLDev::FOnClickSeries(OnClickSeriesDef _v)
{
	onClickSeries = _v;
}

void __fastcall TFRViewLDev::Chart1ClickSeries(TCustomChart *Sender, TChartSeries *Series, int ValueIndex, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	Chart1->SetFocus();
	if (onClickSeries != NULL)
		onClickSeries(ValueIndex);
}

void TFRViewLDev::ColorZone(int _zone)
{
	if (_zone < 0)
		return;
	for (int s = 0; s < Chart1->SeriesCount(); s++)
		Chart1->Series[s]->ValueColor[_zone] = Classer::ClassColor(CL->MZone[_zone]->MSensor[s]->DClass);
	Chart1->Title->Caption = Head;
}

void TFRViewLDev::ColorZone(int _zone, TColor _color)
{
	Chart1->SetFocus();
	if (_zone < 0)
		return;
	for (int s = 0; s < Chart1->SeriesCount(); s++)
		Chart1->Series[s]->ValueColor[_zone] = _color;
	Chart1->Title->Caption = Head + ", зона: "+(_zone+1);
}
void TFRViewLDev::FOnKeyDown(TKeyEvent _v)
{
	Chart1->OnKeyDown = _v;
}

