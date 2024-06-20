// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRCross.h"
#include "PA.h"
#include "Classer.h"
// ---------------------------------------------------------------------------
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
TFRCross *FRCross;

// ---------------------------------------------------------------------------
__fastcall TFRCross::TFRCross(TComponent* Owner) : TFrame(Owner)
{
	FRBordersCross->OnChange = OnChangeChild;
	FRDeads1->OnChange = OnChangeChild;
	Chart1->AllowPanning = TPanningMode::pmNone;
	mark_zone = 0;
	mark_sensor = 0;
	mark_is = false;
	mark_color = clWhite;
	OnClick = NULL;
	OnDblClick = NULL;
	OnChange = NULL;
	SetDefects(0);
	SensorFormD = NULL;
	SensorFormS = NULL;
	Tube = NULL;
}

__fastcall TFRCross::~TFRCross(void)
{
	if (SensorFormD != NULL)
		delete SensorFormD;
	if (SensorFormS != NULL)
		delete SensorFormS;
}

// ---------------------------------------------------------------------------
void TFRCross::OnChangeChild(void)
{
	if (OnChange != NULL)
		OnChange();
}

void TFRCross::Clear(void)
{
	for (int i = 0; i < Chart1->SeriesCount(); i++)
		Chart1->Series[i]->Clear();
	MarkerOff();
	SetDefects(0);
	Tube = NULL;
	if (SensorFormD != NULL)
		SensorFormD->Hide();
	if (SensorFormS != NULL)
		SensorFormS->Hide();
}

void TFRCross::Init(void)
{
	FRBordersCross->Init("Cross");
	FRDeads1->Init("Cross");
	Chart1->BottomAxis->Maximum = PA("MaxZones").Int();
	LoadSettings0();
}

void TFRCross::LoadSettings0(void)
{
	cbCross->Checked = PA("Defect.Work.IsWorkCross").Bool();
}

void TFRCross::LoadSettings(void)
{
	LoadSettings0();
	FRBordersCross->LoadSettings();
	FRDeads1->LoadSettings();
	int lsensors_a = PA("TSSet.Current.TSDef.Cross.L502Chs").GetCount();
	Chart1->SeriesList->Clear();
	for (int i = 0; i < lsensors_a; i++)
	{
		TBarSeries* s = new TBarSeries(Chart1);

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
		s->OnDblClick = SeriesDblClick;

		Chart1->AddSeries(s);
	}
	Chart1->LeftAxis->Minimum = 0;
	Chart1->LeftAxis->Maximum = lsensors_a;
	Chart1->Refresh();
}

void TFRCross::SetEnabledR(bool _v)
{
	FRBordersCross->Enabled = _v;
	FRDeads1->Enabled = _v;
	cbCross->Enabled = _v;
}

void TFRCross::MarkerSet(int _zone, int _sensor)
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

void TFRCross::MarkerOff(void)
{
	if (!mark_is)
		return;
	mark_is = false;
	if (Chart1->Series[mark_sensor]->Count() > mark_zone)
		Chart1->Series[mark_sensor]->ValueColor[mark_zone] = mark_color;
}

// ---------------------------------------------------------------------------
void __fastcall TFRCross::SeriesDblClick(TChartSeries *Sender, int ValueIndex,
	TMouseButton Button, TShiftState Shift, int X, int Y)
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
			SensorFormD = new TFViewZoneD(this, CMeas::TP::Cross, "Поперечный");
		SensorFormD->Draw(Tube, zone, sensor);
		SensorFormD->Show();
	}
	else
	{
		if (SensorFormS == NULL)
			SensorFormS = new TFViewZoneS(this,CMeas::TP::Cross, "Поперечный");
		SensorFormS->Draw(Tube, zone, sensor);
		SensorFormS->Show();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFRCross::SeriesClick(TChartSeries *Sender, int ValueIndex,
	TMouseButton Button, TShiftState Shift, int X, int Y)
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
// ---------------------------------------------------------------------------

void TFRCross::SetDefects(int _val)
{
	FRDefects1->Set(_val);
}

// ---------------------------------------------------------------------------
void __fastcall TFRCross::cbCrossClick(TObject *Sender)
{
	PA("Defect.Work.IsWorkCross").Write(cbCross->Checked);
	if (OnChange != NULL)
		OnChange();
}

// ---------------------------------------------------------------------------
int TFRCross::MinHeight(void)
{
	return (Panel1->Top + Label2->Top + Label2->Height);
}

// ---------------------------------------------------------------------------
void TFRCross::Draw(CTube* _Tube)
{
	Clear();
	Tube = _Tube;
	CCross* Cross = &Tube->Cross;
//	CZone* Z = Cross->MZone;
	int lsensors = Cross->GetSensorsCount();
	int defects = 0;
	for (int z = 0; z < Chart1->BottomAxis->Maximum; z++)
	{
		int s_defects = 0;
		for (int s = 0; s < lsensors; s++)
		{
			if (z < Cross->Size())
			{
				CZone* Z = Cross->MZone[z];
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
