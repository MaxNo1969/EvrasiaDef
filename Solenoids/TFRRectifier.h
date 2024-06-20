//---------------------------------------------------------------------------

#ifndef TFRRectifierH
#define TFRRectifierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "JRectifier.h"
//---------------------------------------------------------------------------
class TFRRectifier : public TFrame
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TSpeedButton *SpeedButton1;
	TStaticText *ST_U;
	TLabel *lLinearVoltage;
	TStaticText *ST_I;
	TLabel *lLinearAmperage;
	TStatusBar *StatusBarBottom;
	TStaticText *ST_R;
	TLabel *Label2;
	TLabel *Label3;
	TStaticText *ST_Time;
	void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
	JRectifier* jRectifier;
	void prs(AnsiString _msg);
	char tp;
public:		// User declarations
	__fastcall TFRRectifier(TComponent* Owner);
	__fastcall ~TFRRectifier(void);
	void Init(JRectifier* _jRectifier,char _Tp);
	void Exec(void);
	void Clear(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRRectifier *FRRectifier;
//---------------------------------------------------------------------------
#endif
