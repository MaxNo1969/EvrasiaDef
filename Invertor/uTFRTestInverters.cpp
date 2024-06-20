//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRTestInverters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#pragma link "uTFRTestInverter"
*/
#pragma resource "*.dfm"
TFRTestInverters *FRTestInverters;

//---------------------------------------------------------------------------
__fastcall TFRTestInverters::TFRTestInverters(TComponent* Owner) : TFrame(Owner)
{
	Inv = NULL;
	ThickInverter->SetTitle("ЧП толщиномера");
}

//------------------------------------------------------------------------
__fastcall TFRTestInverters::~TFRTestInverters(void)
{
	if (Inv != NULL)
		delete Inv;
}

//---------------------------------------------------------------------------
void TFRTestInverters::Init()
{
	if (Inv != NULL)
		delete Inv;
	Inv = new CInv(PA("Defect.ComPortConverters"));
	ThickInverter->Init(false, Inv);
}
//---------------------------------------------------------------------------
