//---------------------------------------------------------------------------

#ifndef uFSignalsStateH
#define uFSignalsStateH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <vcl.h>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "SignalList.h"
//---------------------------------------------------------------------------
class TFSignalsState : public TForm
{
__published:	// IDE-managed Components
	TTimer *InOutTimer;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall InOutTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
private:	// User declarations
	void CheckSignals(void);
	SignalList* SL;
	int space;
public:		// User declarations
	__fastcall TFSignalsState(TComponent* Owner,SignalList* _SL);
	void LoadSettings(void);

};
//---------------------------------------------------------------------------
extern PACKAGE TFSignalsState *FSignalsState;
//---------------------------------------------------------------------------
#endif

