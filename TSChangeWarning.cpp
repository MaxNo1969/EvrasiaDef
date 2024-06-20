//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TSChangeWarning.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTSChangeWarningForm *TSChangeWarningForm;
//---------------------------------------------------------------------------
__fastcall TTSChangeWarningForm::TTSChangeWarningForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTSChangeWarningForm::bOKClick(TObject *Sender)
{
	ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TTSChangeWarningForm::bCancelClick(TObject *Sender)
{
	ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
