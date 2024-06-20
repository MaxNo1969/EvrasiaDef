// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRSOP.h"
#include "uCSelect.h"
#include "PA.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRSOP *FRSOP;

// ---------------------------------------------------------------------------
__fastcall TFRSOP::TFRSOP(TComponent* Owner) : TFrame(Owner)
{

}

// ---------------------------------------------------------------------------
void TFRSOP::Init()
{
	Load();
	cbEtalonView->Checked = PA("Defect.SOP.ViewEtalonCheck").Bool();
	Load();
}

// ---------------------------------------------------------------------------
void __fastcall TFRSOP::cbSelectEtalonChange(TObject *Sender)
{
	PA("Defect.SOP.SOPPaint").Write(cbSelectEtalon->Text);
}

// ---------------------------------------------------------------------------
void __fastcall TFRSOP::cbEtalonViewClick(TObject *Sender)
{
	PA("Defect.SOP.ViewEtalonCheck").Write(cbEtalonView->Checked);
}
// ---------------------------------------------------------------------------
void TFRSOP::Load(void)
{
	AnsiString SOP = PA("Defect.SOP.SOPPaint").String();
	cbSelectEtalon->Items->Clear();
	for (CSelect S("SELECT SOP FROM EtalonDefect order by SOP"); !S.Eof();
	S.Next())
		cbSelectEtalon->Items->Add(S.AsAnsiString("SOP"));
	int index = cbSelectEtalon->Items->IndexOf(SOP);
	if (index >= 0)
		cbSelectEtalon->ItemIndex = index;
	else
	{
		if (cbSelectEtalon->Items->Count > 0)
			cbSelectEtalon->ItemIndex = 0;
	}
	PA("Defect.SOP.SOPPaint").Write(cbSelectEtalon->Text);
}

