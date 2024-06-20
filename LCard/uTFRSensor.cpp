//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRSensor.h"
#include "protocol.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
TFRSensor *FRSensor;

//---------------------------------------------------------------------------
__fastcall TFRSensor::TFRSensor(TComponent* Owner): TFrame(Owner)
{
	OnPop=NULL;
	SetEnabledR(false);
	pop_item=0;
}
//---------------------------------------------------------------------------
__fastcall TFRSensor::TFRSensor(TComponent* Owner, RChannel_parameters _ch_par, AnsiString _title) : TFrame(Owner)
{
	Parent=(TWinControl*)Owner;
	OnPop=NULL;
	SetEnabledR(false);
	pop_item=0;
	Init(_ch_par, _title);
}
//---------------------------------------------------------------------------
void TFRSensor::Init(RChannel_parameters _ch_par,AnsiString _title)
{
#ifdef LCARD502R
	CBRange->Items->Clear();
	CBRange->AddItem("±10", NULL);
	CBRange->AddItem("±5", NULL);
	CBRange->AddItem("±2", NULL);
	CBRange->AddItem("±1", NULL);
	CBRange->AddItem("±0.5", NULL);
	CBRange->AddItem("±0.2", NULL);
	CBMode->Items->Clear();
	CBMode->AddItem("С общей землей", NULL);
	CBMode->AddItem("Дифференциальный", NULL);
	CBMode->AddItem("Измерение нуля", NULL);
#endif
#ifdef LCARD791R
	CBRange->Items->Clear();
	CBRange->AddItem("1", NULL);
	CBRange->AddItem("2", NULL);
	CBRange->AddItem("4", NULL);
	CBRange->AddItem("8", NULL);
	CBRange->AddItem("16", NULL);
	CBRange->AddItem("32", NULL);
	CBRange->AddItem("64", NULL);
	CBRange->AddItem("128", NULL);
	CBMode->Items->Clear();
	CBMode->AddItem("С общей землей", NULL);
	CBMode->AddItem("Дифференциальный", NULL);
#endif
	ch_par = _ch_par;
	if(ch_par.title=="?")
		LName->Caption = _title;
	else
		LName->Caption = ch_par.title;
	CBRange->ItemIndex = CBRange->Items->IndexOf(ch_par.range);
	if (CBRange->ItemIndex < 0)
		CBRange->ItemIndex = 0;
	SEChannel->Value = ch_par.logicalChannel;
	CBMode->ItemIndex = ch_par.collectedMode;
}
//---------------------------------------------------------------------------
void TFRSensor::SetEnabledR(bool _v)
{
	SEChannel->Enabled = _v;
	CBRange->Enabled = _v;
	CBMode->Enabled = _v;
}

//---------------------------------------------------------------------------
void TFRSensor::SaveSettings(void)
{
#ifdef LCARD502R
	ch_par.range = CBRange->ItemIndex;
#endif
#ifdef LCARD791R
	ch_par->range = CBRange->Text.ToInt();
#endif

	ch_par.logicalChannel = SEChannel->Value;
	ch_par.collectedMode = CBMode->ItemIndex;
	//TPr::pr(AnsiString("+++ ")+ch_par->ToString());
}

//---------------------------------------------------------------------------
void TFRSensor::SetFocused(TFRSensor* _p)
{
	if(pop_item==1)
		_p->CBRange->ItemIndex = CBRange->ItemIndex;
	else if (pop_item==2)
		_p->CBMode->ItemIndex = CBMode->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TFRSensor::N1Click(TObject *Sender)
{
	pop_item=1;
	if(OnPop!=NULL)
		OnPop(this);
}
//---------------------------------------------------------------------------

void __fastcall TFRSensor::N2Click(TObject *Sender)
{
	pop_item=2;
	if(OnPop!=NULL)
		OnPop(this);
}
//---------------------------------------------------------------------------


