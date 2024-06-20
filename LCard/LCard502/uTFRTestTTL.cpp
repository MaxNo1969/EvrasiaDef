//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRTestTTL.h"
#include "CatchTTL.h"
#include "Protocol.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRTestTTL *FRTestTTL;
//---------------------------------------------------------------------------
__fastcall TFRTestTTL::TFRTestTTL(TComponent* Owner)
	: TFrame(Owner)
{
	started=false;
}
__fastcall TFRTestTTL::~TFRTestTTL(void)
{
	jCollectTTL.Stop(GetTickCount());
}
//---------------------------------------------------------------------------
void __fastcall TFRTestTTL::SpeedButton1Click(TObject *Sender)
{
	if (SpeedButton1->Down)
	{
		jCollectTTL.Start();
		started=true;
		SpeedButton1->Caption = "Отключить";
	}
	else
	{
		jCollectTTL.Stop(GetTickCount());
		started=false;
		SpeedButton1->Caption = "Включить";
	}
}
void TFRTestTTL::prs(AnsiString _msg)
{
	StatusBarBottom->SimpleText = _msg;
	TPr::pr(AnsiString("TFRTestTTL: ")+_msg);
}
//---------------------------------------------------------------------------
void TFRTestTTL::Exec(void)
{
	if(!jCollectTTL.IsStarted())
		return;
	if(!jCollectTTL.Exec(GetTickCount()))
	{
		prs(jCollectTTL.GetErrorMsg());
	}
	for(;;)
	{
		SignalEvent* ev=CatchTTL::GetNext();
		if(ev==NULL)
			break;
		prs(ev->Tostring());
	}
}

