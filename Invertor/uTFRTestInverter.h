//---------------------------------------------------------------------------

#ifndef uTFRTestInverterH
#define uTFRTestInverterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Inverter.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFRTestInverter : public TFrame
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSpeedButton *SpeedButton1;
	TStatusBar *StatusBar1;
	TEdit *Edit1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton5;
	TSpeedButton *SpeedButton6;
	TLabel *Label1;
	TLabel *Title;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton5Click(TObject *Sender);
	void __fastcall SpeedButton6Click(TObject *Sender);
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
	Inverter* inverter;
	void prs(AnsiString _msg);
public:		// User declarations
	__fastcall TFRTestInverter(TComponent* Owner);
	__fastcall ~TFRTestInverter(void);
	void Init(bool _line, CInv* _Inv);
	void SetTitle(AnsiString _title);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRTestInverter *FRTestInverter;
//---------------------------------------------------------------------------
#endif
