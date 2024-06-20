//---------------------------------------------------------------------------

#ifndef uTFWinWorkH
#define uTFWinWorkH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFWinWork : public TForm
{
__published:	// IDE-managed Components
	TLabel *lWinWorkMessage;
	TButton *bWinWorkOk;
	void __fastcall bWinWorkOkClick(TObject *Sender);
private:	// User declarations
	bool On;
public:		// User declarations
	__fastcall TFWinWork(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFWinWork *FWinWork;
//---------------------------------------------------------------------------
#endif
