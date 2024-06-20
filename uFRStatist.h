//---------------------------------------------------------------------------

#ifndef uFRStatistH
#define uFRStatistH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFRStatist : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TStaticText *STTubes;
	TStaticText *STGood;
	TStaticText *STBrak;
	TButton *Button1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
	void Load(void);
public:		// User declarations
	__fastcall TFRStatist(TComponent* Owner);
	void Add(bool _brak);
	void Init(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRStatist *FRStatist;
//---------------------------------------------------------------------------
#endif
