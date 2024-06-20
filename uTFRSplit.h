//---------------------------------------------------------------------------

#ifndef uTFRSplitH
#define uTFRSplitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

//---------------------------------------------------------------------------
class TFRSplit : public TFrame
{
__published: //IDE-managed Components
	void __fastcall FrameMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall FrameMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall FrameMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

private: //User declarations
	int index;
	bool mouse_split;
	int mouse_Y;
	TFrame* up;
	TFrame* down;
	int upMinHeight;
	int downMinHeight;
	void pr(AnsiString _msg);

public: //User declarations

	__fastcall TFRSplit(TComponent* Owner);
	void Init(int _index, TFrame* _up, int _upMinHeight, TFrame* _down, int _downMinHeight);
	void Save(void);
};

//---------------------------------------------------------------------------
extern PACKAGE TFRSplit *FRSplit;
//---------------------------------------------------------------------------
#endif
