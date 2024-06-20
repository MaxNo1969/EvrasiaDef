#ifndef uTFTest502H
#define uTFTest502H
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFRTEstSolenoid502.h"
#include <ExtCtrls.hpp>
#include "uTFRTestInverter.h"
#include "uTFRTestInverters.h"
#include "TFRRectifier.h"
#include "JRectifier.h"
#include "uTFRTestTTL.h"
//---------------------------------------------------------------------------
class TFTest502 : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TFRTestInverters *FRTestInverters1;
	TFRRectifier *FRRectCross;
	TFRRectifier *FRRectThick;
	TFRTestTTL *FRTestTTL1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
//	JCollect502 jCollect502;
	JRectifier jRectifier;
	void pr(AnsiString _msg);
public:		// User declarations
	__fastcall TFTest502(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFTest502 *FTest502;
//---------------------------------------------------------------------------
#endif
