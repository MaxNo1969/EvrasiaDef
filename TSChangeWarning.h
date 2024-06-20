//---------------------------------------------------------------------------

#ifndef TSChangeWarningH
#define TSChangeWarningH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TTSChangeWarningForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TButton *bOK;
	TButton *bCancel;
	TLabel *Label3;
	void __fastcall bOKClick(TObject *Sender);
	void __fastcall bCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TTSChangeWarningForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTSChangeWarningForm *TSChangeWarningForm;
//---------------------------------------------------------------------------
#endif
