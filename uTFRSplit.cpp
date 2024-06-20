//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRSplit.h"
#include "PA.h"
#include "Protocol.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRSplit *FRSplit;

//---------------------------------------------------------------------------
__fastcall TFRSplit::TFRSplit(TComponent* Owner) : TFrame(Owner)
{
	mouse_split = false;
}

void TFRSplit::Init(int _index, TFrame* _up, int _upMinHeight, TFrame* _down, int _downMinHeight)
{
	index=_index;
	up = _up;
	down = _down;
	upMinHeight = _upMinHeight;
	downMinHeight = _downMinHeight;
	PA pa("Some");
	AnsiString nm="Splitter";
	nm+=index;
	Top = pa.Item(nm).Int();

	//Top = up->Top + up->Height;
	//int dtop = down->Top;
	//down->Top = Top + Height;
	//down->Height = dtop + down->Height - down->Top;
}

//---------------------------------------------------------------------------
void __fastcall TFRSplit::FrameMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	mouse_split = true;
	mouse_Y = Y;
	SetCapture(Handle);
}

//---------------------------------------------------------------------------
void __fastcall TFRSplit::FrameMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	mouse_split = false;
	ReleaseCapture();
}

//---------------------------------------------------------------------------
void __fastcall TFRSplit::FrameMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	if (!mouse_split)
		return;
	//pr(AnsiString().sprintf("X=%d Y=%d mX=%d mY=%d", X, Y, mouse_X, mouse_Y));
	//if (OnSplit != NULL)
	//OnSplit(Parent, Y - mouse_Y);
	int cH = up->Height + (Y - mouse_Y);
	if (cH < upMinHeight)
		return;
	int bottom = down->Top + down->Height;
	if (bottom - (Top + (Y - mouse_Y) + Height) < downMinHeight)
		return;
	Top = Top + (Y - mouse_Y);
	up->Height = cH;
	//pr(up->Height);
	//pr(Y - mouse_Y);
	down->Top = down->Top + (Y - mouse_Y);
	down->Height = bottom - down->Top;
}

//---------------------------------------------------------------------------
void TFRSplit::pr(AnsiString _msg)
{
	TPr::pr(_msg);
}

//---------------------------------------------------------------------------
void TFRSplit::Save(void)
{
	PA pa("Some");
	AnsiString nm="Splitter";
	nm+=index;
	pa.Item(nm).Write(Top);
}
//---------------------------------------------------------------------------
