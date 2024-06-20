// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFViewZoneS.h"
#include "uFunctions.h"
#include "PA.h"
#include "Classer.h"
#include <VCLTee.Series.hpp>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#pragma link "Chart"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "Series"
#pragma link "ArrowCha"
*/
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TFViewZoneS::TFViewZoneS(TComponent* Owner, CMeas::TP _Tp,
	AnsiString _title) : TForm(Owner)
{
	title = _title;
	Tp = _Tp;
	Tube = NULL;
}

// ---------------------------------------------------------------------------
void __fastcall TFViewZoneS::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == 27)
		((TForm*)Sender)->Close();
}

// ---------------------------------------------------------------------------
void __fastcall TFViewZoneS::FormCreate(TObject *Sender)
{
	PA("Defect.Wins").LoadFormPos(this);
	PA pa("Defect.ViewZone");
	SBSource->Down = pa.Item("ViewZoneSSource").Bool();
	SBMedian->Down = pa.Item("ViewZoneSMedian").Bool();
	SBFilterIn->Down = pa.Item("ViewZoneSFilterIn").Bool();
	SBFilterOut->Down = pa.Item("ViewZoneSFilterOut").Bool();
	Chart1->Series[0]->Visible = SBSource->Down;
	Chart1->Series[1]->Visible = SBMedian->Down;
	Chart1->Series[2]->Visible = SBFilterOut->Down;
	Chart1->Series[3]->Visible = SBFilterIn->Down;
	Out10->Visible = SBFilterOut->Down;
	Out11->Visible = SBFilterOut->Down;
	Out20->Visible = SBFilterOut->Down;
	Out21->Visible = SBFilterOut->Down;
	In10->Visible = SBFilterIn->Down;
	In11->Visible = SBFilterIn->Down;
	In20->Visible = SBFilterIn->Down;
	In21->Visible = SBFilterIn->Down;
	SetMetric(0, 0);
}

// ---------------------------------------------------------------------------
void __fastcall TFViewZoneS::FormDestroy(TObject *Sender)
{
	PA pa("Defect.ViewZone");
	pa.Item("ViewZoneSSource").Write(SBSource->Down);
	pa.Item("ViewZoneSMedian").Write(SBMedian->Down);
	pa.Item("ViewZoneSFilterIn").Write(SBFilterIn->Down);
	pa.Item("ViewZoneSFilterOut").Write(SBFilterOut->Down);
	PA("Defect.Wins").SaveFormPos(this);
}

// ---------------------------------------------------------------------------
void TFViewZoneS::SetCaption(AnsiString _cap)
{
	Caption = title + " " + _cap;
}

void TFViewZoneS::SetBorder(TLineSeries* _series, double _level, TColor _color)
{
	_series->Clear();
	_series->AddXY(0, _level, "", _color);
	_series->AddXY(Series1->MaxXValue(), _level, "", _color);
}

void TFViewZoneS::SetMetric(double _start, double _zone_size)
{
	start = _start;
	zone_size = _zone_size;
	if (start < 0)
		start = 0;
	if (zone_size < 0)
		zone_size = 0;
}

void __fastcall TFViewZoneS::Chart1ClickBackground(TCustomChart *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	double x, y;
	Chart1->Series[0]->GetCursorValues(x, y);
	if (x < 0)
		x = 0;
	Chart1->Series[0]->Count();
	double Range = start + x * zone_size / Chart1->Series[0]->Count();
	AnsiString a = "Расстояние: ~";
	a += (int)Range;
	a += " мм";
	StatusBar1->Panels->Items[0]->Text = a;
}

// ---------------------------------------------------------------------------
void TFViewZoneS::Clear(void)
{
	for (int i = 0; i < Chart1->SeriesCount(); i++)
		Chart1->Series[i]->Clear();
};

void __fastcall TFViewZoneS::SBSourceClick(TObject *Sender)
{
	Chart1->Series[0]->Visible = ((TSpeedButton*)Sender)->Down;
}
// ---------------------------------------------------------------------------

void __fastcall TFViewZoneS::SBMedianClick(TObject *Sender)
{
	Chart1->Series[1]->Visible = ((TSpeedButton*)Sender)->Down;
}
// ---------------------------------------------------------------------------

void __fastcall TFViewZoneS::SBFilterOutClick(TObject *Sender)
{
	bool v = ((TSpeedButton*)Sender)->Down;
	Chart1->Series[2]->Visible = v;
	Out10->Visible = v;
	Out11->Visible = v;
	Out20->Visible = v;
	Out21->Visible = v;
}
// ---------------------------------------------------------------------------

void __fastcall TFViewZoneS::SBFilterInClick(TObject *Sender)
{
	bool v = ((TSpeedButton*)Sender)->Down;
	Chart1->Series[3]->Visible = v;
	In10->Visible = v;
	In11->Visible = v;
	In20->Visible = v;
	In21->Visible = v;
}

// ---------------------------------------------------------------------------
void TFViewZoneS::BorderVisible(AnsiString _mark, bool _v)
{
}

void TFViewZoneS::Draw(CTube* _Tube, int _zone, int _sensor)
{
	Tube = _Tube;
	curr_zone = _zone;
	curr_sens = _sensor;
	Draw();
}

void TFViewZoneS::Draw(void)
{
	Clear();
	if (Tube == NULL)
		return;
	SetCaption(AnsiString("Датчик ") + (curr_sens + 1) + ", зона " + curr_zone);
	CCrossLine* CL = (Tp == CMeas::TP::Cross) ? (CCrossLine*)&Tube->Cross :
		(CCrossLine*)&Tube->Line;

	int lsize = CL->MZone[curr_zone]->MSensor[curr_sens]->Size();
	CSensor* S = CL->MZone[curr_zone]->MSensor[curr_sens];
	double lgain = CL->MSensor2[curr_sens]->Gain;
	for (int m = 0; m < lsize; m++)
	{
		CMeas* M = S->MMeas[m];
		AddSource(M->Source*lgain);
		AddMedian(M->Median*lgain);
		AddFilteredOut(M->FilterOut*lgain);
		AddFilteredIn(M->FilterIn*lgain);
	}
	SetBorderOut1(CL->borders[0], Classer::ClassColor(CL->borders[0],
		CL->borders));
	if (CL->borders[1] != 0)
		SetBorderOut2(CL->borders[1], Classer::ClassColor(CL->borders[1],
		CL->borders));
	int lZoneLength = CL->MZone[0]->VZoneLength;
	SetMetric(curr_zone*lZoneLength, lZoneLength);
	/* TODO : Последняя зона плавающей длины */
}

void __fastcall TFViewZoneS::FormKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
	switch (Key)
	{
	case VK_LEFT:
		if (curr_zone > 0)
		{
			curr_zone--;
			Draw();
		}
		break;
	case VK_RIGHT:
		{
			CCrossLine* CL = (Tp == CMeas::TP::Cross) ?
				(CCrossLine*)&Tube->Cross : (CCrossLine*)&Tube->Line;
			if (curr_zone + 1 < CL->Size())
			{
				curr_zone++;
				Draw();
			}
		} break;
	case VK_UP:
		{
			CCrossLine* CL = (Tp == CMeas::TP::Cross) ?
				(CCrossLine*)&Tube->Cross : (CCrossLine*)&Tube->Line;
			if (curr_sens + 1 < CL->GetSensorsCount())
			{
				curr_sens++;
				Draw();
			}
		} break;
	case VK_DOWN:
		if (curr_sens > 0)
		{
			curr_sens--;
			Draw();
		}
		break;
	case VK_ESCAPE:
		Close();
		break;
	}

}
// ---------------------------------------------------------------------------
