//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRLineRemote.h"
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
TFRLineRemote *FRLineRemote;

//---------------------------------------------------------------------------
__fastcall TFRLineRemote::TFRLineRemote(TComponent* Owner) : TFrame(Owner)
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
	}
	FRBordersLine->OnChange = OnChangeChild;
	FRDeads1->OnChange = OnChangeChild;
	Chart1->LeftAxis->Maximum = Chart1->SeriesCount();
	SetDefects(0);
	Tube=NULL;
}
__fastcall TFRLineRemote::~TFRLineRemote(void)
{
}

//---------------------------------------------------------------------------
void TFRLineRemote::Clear(void)
{
	for (int i = 0; i < Chart1->SeriesCount(); i++)
		Chart1->Series[i]->Clear();
	SetDefects(0);
}

void TFRLineRemote::Init(void)
{
	FRBordersLine->Init("Line");
	FRDeads1->Init("Line");
	Chart1->BottomAxis->Maximum = PA("MaxZones").Int();
	LoadSettings0();
}

void TFRLineRemote::LoadSettings(void)
{
	LoadSettings0();
	FRBordersLine->LoadSettings();
}

void TFRLineRemote::LoadSettings0(void)
{
	cbLinear->Checked = PA("Defect.Work.IsWorkLine").Bool();
}

void TFRLineRemote::SetEnabledR(bool _v)
{
	FRBordersLine->Enabled = _v;
	FRDeads1->Enabled = _v;
	cbLinear->Enabled=_v;
}

void __fastcall TFRLineRemote::cbLinearClick(TObject *Sender)
{
	PA("Defect.Work.IsWorkLine").Write(cbLinear->Checked);
	if (OnChange != NULL)
		OnChange();
}

//---------------------------------------------------------------------------

void TFRLineRemote::OnChangeChild(void)
{
	if (OnChange != NULL)
		OnChange();
}

void TFRLineRemote::SetDefects(int _val)
{
	FRDefects1->Set(_val);
}

//---------------------------------------------------------------------------
int TFRLineRemote::MinHeight(void)
{
	return (Panel1->Top + Label2->Top + Label2->Height);
}
//---------------------------------------------------------------------------
void TFRLineRemote::Draw(CTube* _Tube)
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
