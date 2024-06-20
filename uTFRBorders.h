// ---------------------------------------------------------------------------

#ifndef uTFRBordersH
#define uTFRBordersH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

// ---------------------------------------------------------------------------
class TFRBorders : public TFrame
{
__published: // IDE-managed Components

	TEdit *EBorder20;
	TLabel *Label6;
	TEdit *EBorder10;
	TLabel *Label14;
	TEdit *EBorder11;
	TEdit *EBorder21;
	TLabel *Label1;
	TLabel *LBorder1;
	TLabel *LBorder2;

	void __fastcall EBorder10Exit(TObject *Sender);
	void __fastcall EBorder10KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private: // User declarations
	void SetInner(bool _v);
	void Save(void);

	AnsiString tp;
	bool inner;
	AnsiString section;

public: // User declarations

	__fastcall TFRBorders(TComponent* Owner);
	void Init(AnsiString _tp);
	void LoadSettings(void);
	typedef void(__closure * OnTFRBordersChange)(void);
	OnTFRBordersChange OnChange;
};

// ---------------------------------------------------------------------------
extern PACKAGE TFRBorders *FRBorders;
// ---------------------------------------------------------------------------
#endif
