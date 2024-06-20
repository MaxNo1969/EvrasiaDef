//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uFRSigPanel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRSigPanel *FRSigPanel;

//---------------------------------------------------------------------------
__fastcall TFRSigPanel::TFRSigPanel(TComponent* Owner, CSignal* _signal) : TFrame(Owner)
{
	signal = _signal;
	ByHint(true);
}

void TFRSigPanel::ByHint(bool _val)
{
		AnsiString idx = signal->GetDev();
		int index = signal->GetIndex();
		if (index >= 16)
		{
			idx += "Ä";
			index -= 16;
		}
		idx += "[";
		idx += index;
		idx += "]";
	if (_val)
	{
		Panel1->Hint = AnsiString(" ") + signal->hint;
		Panel1->Caption = idx + " " + signal->GetName();
	}
	else
	{
		Panel1->Caption = AnsiString(" ") + signal->hint;
		Panel1->Hint = idx + " " + signal->GetName();
	}

}

//---------------------------------------------------------------------------
void TFRSigPanel::CheckSignal(void)
{
	if (signal->IsInput())
	{
		if (signal->Get())
			Panel1->Color = clLime;
		else
			Panel1->Color = clBtnFace;
	}
	else
	{
		if (signal->Get())
			Panel1->Color = clRed;
		else
			Panel1->Color = clBtnFace;
	}
	//Panel1->Refresh();
	//Panel1->Repaint();
}
