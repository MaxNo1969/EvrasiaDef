// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRViewDev.h"
#include <math.h>

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRViewDev *FRViewDev;

// ---------------------------------------------------------------------------
__fastcall TFRViewDev::TFRViewDev(TComponent* Owner) : TFrame(Owner)
{
}
void TFRViewDev::Init(CTube* _Tube, CMeas::TP _Tp, bool _check_visible)
{
	CCrossLine* CL = (_Tp == CMeas::TP::Cross) ? (CCrossLine*)&_Tube->Cross : (CCrossLine*)&_Tube->Line;
	int sensors = CL->GetSensorsCount();

	for (int s = 0; s < sensors; s++)
	{
		TFRViewZone* p = new TFRViewZone(this, _Tp, _Tube, s, true, _check_visible);
		p->Parent = this;
		AnsiString a = "FRViewZone";
		a += (_Tp == CMeas::TP::Cross) ? "C" : "L";
		a += "_";
		a += s;
		p->Name = a;
		p->OnChangeGain = NULL;
		p->OnCalibrate = NULL;
	}
	FrameResize(NULL);
	for(int i=0;i<ControlCount;i++)
	{
		if(!Controls[i]->InheritsFrom(__classid(TFRViewZone)))
			continue;
		TFRViewZone* vz=(TFRViewZone*)Controls[i];
	}
}

// ---------------------------------------------------------------------------
void TFRViewDev::SetStep(double _step)
{
	for(int i=0;i<ControlCount;i++)
	{
		if(!Controls[i]->InheritsFrom(__classid(TFRViewZone)))
			continue;
		TFRViewZone* vz=(TFRViewZone*)Controls[i];
		vz->SetStep(_step);
	}
}

void __fastcall TFRViewDev::FrameResize(TObject *Sender)
{
	int LCount=0;
	for(int i=0;i<ControlCount;i++)
	{
		if(!Controls[i]->InheritsFrom(__classid(TFRViewZone)))
			continue;
			LCount++;
	}
	if(LCount==0)
		return;
	int columns = 4;
	double x;
	x = LCount;
	x /= columns;
	int rows = (int)ceil(x);
	int w = ClientWidth / columns;
	int h = ClientHeight / rows;
	int s = 0;

	int r = 0;
	int c = 0;
	for(int i=0;i<ControlCount;i++)
	{
		if(!Controls[i]->InheritsFrom(__classid(TFRViewZone)))
			continue;
		TFRViewZone* vz=(TFRViewZone*)Controls[i];
		vz->Width = w;
		vz->Height = h;
		vz->Left = c * w;
		vz->Top = r * h;
		c++;
		if(c==columns)
		{
			c=0;
			r++;
		}
	}
}
// ---------------------------------------------------------------------------
void TFRViewDev::Draw(int _zone)
{
	for(int i=0;i<ControlCount;i++)
	{
		if(!Controls[i]->InheritsFrom(__classid(TFRViewZone)))
			continue;
		TFRViewZone* vz=(TFRViewZone*)Controls[i];
		vz->Draw(_zone);
	}
}

void TFRViewDev::FOnCalibrateWrite(TFRViewZone::OnCalibrateDef _v)
{
	for(int i=0;i<ControlCount;i++)
	{
		if(!Controls[i]->InheritsFrom(__classid(TFRViewZone)))
			continue;
		TFRViewZone* vz=(TFRViewZone*)Controls[i];
		vz->OnCalibrate=_v;
	}
}
void TFRViewDev::FOnChangeGainWrite(TFRViewZone::OnChangeGainDef _v)
{
	for(int i=0;i<ControlCount;i++)
	{
		if(!Controls[i]->InheritsFrom(__classid(TFRViewZone)))
			continue;
		TFRViewZone* vz=(TFRViewZone*)Controls[i];
		vz->OnChangeGain=_v;
	}
}
bool TFRViewDev::NeedCalibrate(int _sensor)
{
	int ivz=0;
	for(int i=0;i<ControlCount;i++)
	{
		if(!Controls[i]->InheritsFrom(__classid(TFRViewZone)))
			continue;
		TFRViewZone* vz=(TFRViewZone*)Controls[i];
		if(vz->GetSensor()==_sensor)
			return(vz->NeedCalibrate());
	}
	return(false);
}
void TFRViewDev::SetInner(bool _v)
{
	for(int i=0;i<ControlCount;i++)
	{
		if(!Controls[i]->InheritsFrom(__classid(TFRViewZone)))
			continue;
		TFRViewZone* vz=(TFRViewZone*)Controls[i];
		vz->SetInner(_v);
	}
}



