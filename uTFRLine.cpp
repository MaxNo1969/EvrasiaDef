//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRLine.h"
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
#pragma link "uTFRDeads"
#pragma link "uTFRSplit"
#pragma link "uTFRDefects"
*/
#pragma resource "*.dfm"
TFRLine *FRLine;

//---------------------------------------------------------------------------
__fastcall TFRLine::TFRLine(TComponent* Owner) : TFrame(Owner)
{
	Chart1->AllowPanning = TPanningMode::pmNone;

	for (int i = 0; i < Chart1->SeriesCount(); i++)
	{
		Chart1->Series[i]->ColorEachPoint = true;
		Chart1->Series[i]->Marks->Visible = false;
		((TBarSeries*) Chart1->Series[i])->BarWidthPercent = 100;
		((TBarSeries*) Chart1->Series[i])->MultiBar = mbStacked;
		((TBarSeries*) Chart1->Series[i])->SideMargins = false;
		((TBarSeries*) Chart1->Series[i])->OffsetPercent = 50;
		Chart1->Series[i]->OnClick = SeriesClick;
		Chart1->Series[i]->OnDblClick = SeriesDblClick;
	}
	mark_zone = 0;
	mark_sensor = 0;
	mark_is = false;
	mark_color = clWhite;
	OnClick = NULL;
	OnDblClick = NULL;
	OnChange = NULL;
	FRBordersLine->OnChange = OnChangeChild;
	FRDeads1->OnChange = OnChangeChild;
	Chart1->LeftAxis->Maximum = Chart1->SeriesCount();
	SetDefects(0);
	Tube=NULL;
}
__fastcall TFRLine::~TFRLine(void)
{
	if (SensorFormD != NULL)
		delete SensorFormD;
	if (SensorFormS != NULL)
		delete SensorFormS;
}

//---------------------------------------------------------------------------
void TFRLine::Clear(void)
{
	for (int i = 0; i < Chart1->SeriesCount(); i++)
		Chart1->Series[i]->Clear();
	MarkerOff();
	SetDefects(0);
	if (SensorFormD != NULL)
		SensorFormD->Hide();
	if (SensorFormS != NULL)
		SensorFormS->Hide();
}

void TFRLine::Init(void)
{
	FRBordersLine->Init("Line");
	FRDeads1->Init("Line");
	Chart1->BottomAxis->Maximum = PA("MaxZones").Int();
	LoadSettings0();
}

void TFRLine::LoadSettings(void)
{
	LoadSettings0();
	FRBordersLine->LoadSettings();
}

void TFRLine::LoadSettings0(void)
{
	cbLinear->Checked = PA("Defect.Work.IsWorkLine").Bool();
}

void TFRLine::SetEnabledR(bool _v)
{
	FRBordersLine->Enabled = _v;
	FRDeads1->Enabled = _v;
	cbLinear->Enabled=_v;
}

void __fastcall TFRLine::cbLinearClick(TObject *Sender)
{
	PA("Defect.Work.IsWorkLine").Write(cbLinear->Checked);
	if (OnChange != NULL)
		OnChange();
}

//---------------------------------------------------------------------------
void TFRLine::MarkerSet(int _zone, int _sensor)
{
	MarkerOff();
	if (_sensor < 0 || _sensor >= Chart1->SeriesCount())
		return;
	if (_zone < 0 || _zone >= Chart1->Series[_sensor]->Count())
		return;
	mark_sensor = _sensor;
	mark_zone = _zone;
	mark_color = Chart1->Series[_sensor]->ValueColor[_zone];
	mark_is = true;
	Chart1->Series[_sensor]->ValueColor[_zone] = clNavy;
}

void TFRLine::MarkerOff(void)
{
	if (!mark_is)
		return;
	mark_is = false;
	if (Chart1->Series[mark_sensor]->Count() > mark_zone)
		Chart1->Series[mark_sensor]->ValueColor[mark_zone] = mark_color;
}

//---------------------------------------------------------------------------
void __fastcall TFRLine::SeriesDblClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button, TShiftState Shift,
	int X, int Y)
{
	if (Tube == NULL)
		return;
	int zone = ValueIndex;
	int sensor;
	for (int i = 0; i < Chart1->SeriesCount(); i++)
	{
		if (Chart1->Series[i] == Sender)
		{
			sensor = i;
			break;
		}
	}
	MarkerSet(zone, sensor);
	if (!Shift.Contains(ssCtrl))
	{
		if (SensorFormD == NULL)
			SensorFormD = new TFViewZoneD(this, CMeas::TP::Line, "Продольный");
		SensorFormD->Draw(Tube, zone, sensor);
		SensorFormD->Show();
	}
	else
	{
		if (SensorFormS == NULL)
			SensorFormS = new TFViewZoneS(this,CMeas::TP::Line, "Продольный");
		SensorFormS->Draw(Tube, zone, sensor);
		SensorFormS->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFRLine::SeriesClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button, TShiftState Shift,
	int X, int Y)
{
	if (OnClick == NULL)
	{
		MarkerOff();
		return;
	}
	int zone = ValueIndex;
	int sensor;
	for (int i = 0; i < Chart1->SeriesCount(); i++)
	{
		if (Chart1->Series[i] == Sender)
		{
			sensor = i;
			break;
		}
	}
	bool IsCtrl = Shift.Contains(ssCtrl);
	MarkerSet(zone, sensor);
	OnClick(zone, sensor, IsCtrl);
}

//---------------------------------------------------------------------------
void TFRLine::OnChangeChild(void)
{
	if (OnChange != NULL)
		OnChange();
}

void TFRLine::SetDefects(int _val)
{
	FRDefects1->Set(_val);
}

//---------------------------------------------------------------------------
int TFRLine::MinHeight(void)
{
	return (Panel1->Top + Label2->Top + Label2->Height);
}
//---------------------------------------------------------------------------
void TFRLine::Draw(CTube* _Tube)
{
	Tube=_Tube;
	Clear();

	CLine* Line = &_Tube->Line;
	int lsensors = Line->GetSensorsCount();
	int defects = 0;
	for (int z = 0; z < Chart1->BottomAxis->Maximum; z++)
	{
		int s_defects = 0;
		for (int s = 0; s < lsensors; s++)
		{
			if (z < Line->Size())
			{
				CZone* Z = Line->MZone[z];
				int dclass = Z->MSensor[s]->DClass;
				Chart1->Series[s]->AddXY(z, 1, "", Classer::ClassColor(dclass));
				if (dclass == 0 || dclass == 1)
					s_defects++;
			}
			else
				Chart1->Series[s]->Add(0, "", clWhite);
			if (s_defects > 0)
				defects++;
		}
	}
	SetDefects(defects);
}
