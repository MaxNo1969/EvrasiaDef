//---------------------------------------------------------------------------

#ifndef uTFRDeadsH
#define uTFRDeadsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFRDeads : public TFrame
{
__published:	// IDE-managed Components
	TEdit *EFinish;
	TLabel *Label13;
	TEdit *EStart;
	TLabel *Label5;
	void __fastcall EStartExit(TObject *Sender);
	void __fastcall EStartKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	void Save(void);
	AnsiString tpp;
	AnsiString section;
public:		// User declarations
	__fastcall TFRDeads(TComponent* Owner);
	void Init(AnsiString _tp);
	void LoadSettings(void);
	typedef void(__closure * OnTFRDeadsChange)(void);
	OnTFRDeadsChange OnChange;
};
//---------------------------------------------------------------------------
extern PACKAGE TFRDeads *FRDeads;
//---------------------------------------------------------------------------
#endif
