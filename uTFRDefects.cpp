// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRDefects.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRDefects *FRDefects;

// ---------------------------------------------------------------------------
__fastcall TFRDefects::TFRDefects(TComponent* Owner) : TFrame(Owner)
{
}

// ---------------------------------------------------------------------------
void TFRDefects::Set(int _val)
{
	if (_val == 0)
		Panel1->Caption = "";
	else
		Panel1->Caption = _val;
}
