// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRButtons.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRButtons *FRButtons;

// ---------------------------------------------------------------------------
__fastcall TFRButtons::TFRButtons(TComponent* Owner) : TFrame(Owner)
{
	ROnClick = NULL;
	SBReturn->Visible = false;
	SBPass->Visible = false;
	int space=SBSOP->Left-(SBWork->Left+SBWork->Width);
//	SBTest->Left=SBView->Left+SBView->Width+space;
//	SBManage->Left=SBTest->Left+SBTest->Width+space;

	SBManage->Left=SBView->Left+SBView->Width+space;
	SBCancel->Left=SBManage->Left+SBManage->Width+space;
	Enable();
}

// ---------------------------------------------------------------------------
void TFRButtons::Disable(void)
{
	SBWork->Enabled = false;
	SBSOP->Enabled = false;
	SBView->Enabled = false;
	SBReturn->Enabled = false;
	SBPass->Enabled = false;
	SBTest->Enabled = false;
	SBManage->Enabled = false;
	SBCancel->Enabled = true;
}

// ---------------------------------------------------------------------------
void TFRButtons::Enable(void)
{
	SBWork->Enabled = true;
	SBWork->Caption = "Работа";
	SBSOP->Enabled = true;
	SBView->Enabled = true;
	SBReturn->Enabled = true;
	SBPass->Enabled = true;
	SBTest->Enabled = true;
	SBManage->Enabled = true;
	SBCancel->Enabled = false;
}
// ---------------------------------------------------------------------------

void __fastcall TFRButtons::SBWorkClick(TObject *Sender)
{
	if (SBWork->Caption == "Продолжить")
	{
		SBWork->Enabled = false;
		SBWork->Caption = "Работа";
		SBView->Enabled = false;
		if (ROnClick != NULL)
			ROnClick("ReStart");
	}
	else
	{
		Disable();
		if (ROnClick != NULL)
			ROnClick("Work");
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFRButtons::SBViewClick(TObject *Sender)
{
	if (ROnClick != NULL)
		ROnClick("View");
}
// ---------------------------------------------------------------------------

void __fastcall TFRButtons::SBReturnClick(TObject *Sender)
{
	Disable();
	if (ROnClick != NULL)
		ROnClick("Return");
}
// ---------------------------------------------------------------------------

void __fastcall TFRButtons::SBPassClick(TObject *Sender)
{
	Disable();
	if (ROnClick != NULL)
		ROnClick("Pass");
}
// ---------------------------------------------------------------------------

void __fastcall TFRButtons::SBTestClick(TObject *Sender)
{
	Disable();
	if (ROnClick != NULL)
		ROnClick("Test");
}
// ---------------------------------------------------------------------------

void __fastcall TFRButtons::SBManageClick(TObject *Sender)
{
	if (ROnClick != NULL)
		ROnClick("Manage");
}
// ---------------------------------------------------------------------------

void __fastcall TFRButtons::SBCancelClick(TObject *Sender)
{
	SBCancel->Enabled = false;
	if (ROnClick != NULL)
		ROnClick("Cancel");
	Enable();
}

// ---------------------------------------------------------------------------
void TFRButtons::Interrupt()
{
	SBWork->Caption = "Продолжить";
	SBWork->Enabled = true;
}

// ---------------------------------------------------------------------------
void __fastcall TFRButtons::SBSOPClick(TObject *Sender)
{
	if (ROnClick != NULL)
		ROnClick("СОП");
}
// ---------------------------------------------------------------------------
