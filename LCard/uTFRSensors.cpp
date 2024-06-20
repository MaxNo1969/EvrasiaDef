#include <vcl.h>
#pragma hdrstop
#include "uTFRSensors.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRSensors *FRSensors;

//---------------------------------------------------------------------------
__fastcall TFRSensors::TFRSensors(TComponent* Owner) : TFrame(Owner)
{
}
void TFRSensors::Init(LCardChGroup* _channels)
{
	int space = 4;
	int hspace = 3;
	int ltop;
	ltop = space + 20;

	for (int i = 0; i < _channels->Count(); i++)
	{
		AnsiString title = "Датчик ";
		title += i;
		TFRSensor* p = new TFRSensor(gSensors, _channels->Item(i), title);
		p->OnPop=SetAll;
		AnsiString a = "S_";
		a += i;
		p->Name = a;
		p->Left = hspace;
		p->Top = ltop;
		ltop += p->Height + space;
	}
}

//---------------------------------------------------------------------------
void TFRSensors::Save(void)
{
	for (int i = 0; i < gSensors->ControlCount; i++)
	{
		TControl* p = gSensors->Controls[i];
		if (p->ClassName() == "TFRSensor")
			((TFRSensor*)p)->SaveSettings();
	}
}
//---------------------------------------------------------------------------
void TFRSensors::SetEnabledR(bool _v)
{
	for (int i = 0; i < gSensors->ControlCount; i++)
	{
		TControl* p = gSensors->Controls[i];
		if (p->ClassName() == "TFRSensor")
			((TFRSensor*)p)->SetEnabledR(_v);
	}
}
//---------------------------------------------------------------------------
void TFRSensors::SetAll(TFRSensor* _p)
{
	for (int i = 0; i < gSensors->ControlCount; i++)
	{
		TControl* p = gSensors->Controls[i];
		if (p->ClassName() != "TFRSensor")
			continue;
		TFRSensor* pp=(TFRSensor*)p;
		if(pp==_p)
			continue;
		_p->SetFocused(pp);
	}
}
//---------------------------------------------------------------------------

