//---------------------------------------------------------------------------

#ifndef uTFRTestTTLH
#define uTFRTestTTLH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "JCollectTTL.h"
//---------------------------------------------------------------------------
class TFRTestTTL : public TFrame
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TSpeedButton *SpeedButton1;
	TStatusBar *StatusBarBottom;
	void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
	bool started;
	JCollectTTL jCollectTTL;
	void prs(AnsiString _msg);
public:		// User declarations
	__fastcall TFRTestTTL(TComponent* Owner);
	__fastcall ~TFRTestTTL(void);
	void Exec(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRTestTTL *FRTestTTL;
//---------------------------------------------------------------------------
#endif
