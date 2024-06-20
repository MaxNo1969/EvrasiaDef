//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFWinWork.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFWinWork *FWinWork;
//---------------------------------------------------------------------------
__fastcall TFWinWork::TFWinWork(TComponent* Owner)
	: TForm(Owner)
{
	On=true;
}
//---------------------------------------------------------------------------
void __fastcall TFWinWork::bWinWorkOkClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
