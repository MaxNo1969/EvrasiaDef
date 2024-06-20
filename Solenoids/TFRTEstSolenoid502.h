//---------------------------------------------------------------------------

#ifndef TFRTEstSolenoid502H
#define TFRTEstSolenoid502H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "Solenoid.h"
#include "JCollect502.h"
#include "SignalListDef.h"

//---------------------------------------------------------------------------
class TFRTEstSolenoid502 : public TFrame
{
__published: //IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TLabel *lLinearTemperature;
	TLabel *lLinearResistance;
	TLabel *lLinearVoltage;
	TLabel *lLinearAmperage;
	TStatusBar *StatusBarBottom;
	TSpeedButton *SpeedButton1;
	TStaticText *ST_I;
	TStaticText *ST_U;
	TStaticText *ST_T;
	TStaticText *ST_R;
	void __fastcall SpeedButton1Click(TObject *Sender);
private: //User declarations
	Solenoid solenoid;
	CSignal* SOLPOW;
public: //User declarations
	__fastcall TFRTEstSolenoid502(TComponent* Owner);
	__fastcall ~TFRTEstSolenoid502(void);
	void Init(PA _pa, AnsiString _TypeOfControl, AnsiString _title, JCollect502* _jCollect502);
	void Exec(void);
	//__fastcall ~TFRTEstSolenoid502(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRTEstSolenoid502 *FRTEstSolenoid502;
//---------------------------------------------------------------------------
#endif
