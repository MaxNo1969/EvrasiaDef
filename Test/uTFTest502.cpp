//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "uTFTest502.h"
#include "uFunctions.h"
#include "Protocol.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TFRTEstSolenoid502"
#pragma link "uTFRTestInverter"
#pragma link "uTFRTestInverters"
#pragma link "TFRRectifier"
#pragma link "uTFRTestTTL"
#pragma resource "*.dfm"
TFTest502 *FTest502;

//---------------------------------------------------------------------------
__fastcall TFTest502::TFTest502(TComponent* Owner) : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TFTest502::FormCreate(TObject *Sender)
{
	PA("Defect.Wins").LoadFormPos(this);
	FRRectCross->Init(&jRectifier,'c');
	FRRectThick->Init(&jRectifier,'t');
	FRTestInverters1->Init();
}
//---------------------------------------------------------------------------

void __fastcall TFTest502::FormDestroy(TObject * Sender)
{
	FRRectCross->Clear();
	FRRectThick->Clear();
	PA("Defect.Wins").SaveFormPos(this);
}
//---------------------------------------------------------------------------

void __fastcall TFTest502::Timer1Timer(TObject * Sender)
{
	FRRectCross->Exec();
	FRRectThick->Exec();
	FRTestTTL1->Exec();
}
//---------------------------------------------------------------------------
void TFTest502::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("TFTest502: ") + _msg);
}

