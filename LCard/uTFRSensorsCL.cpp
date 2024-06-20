#include <vcl.h>
#pragma hdrstop
#include "uTFRSensorsCL.h"
#pragma package(smart_init)
#pragma link "uTFRSensors"
#pragma resource "*.dfm"
TFRSensorsCL *FRSensorsCL;
//---------------------------------------------------------------------------
__fastcall TFRSensorsCL::TFRSensorsCL(TComponent* Owner)
	: TFrame(Owner)
{
}
void TFRSensorsCL::Init(LCardChGroup* _Cross,LCardChGroup* _Line)
{
	FRCross->Init(_Cross);
	FRLine->Init(_Line);
}
//---------------------------------------------------------------------------
void TFRSensorsCL::Save(void)
{
	FRCross->Save();
	FRLine->Save();
}
//---------------------------------------------------------------------------
void TFRSensorsCL::SetEnabledR(bool _v)
{
	FRCross->SetEnabledR(_v);
	FRLine->SetEnabledR(_v);
}
//---------------------------------------------------------------------------

