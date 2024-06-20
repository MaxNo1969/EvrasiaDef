//---------------------------------------------------------------------------

#ifndef uTFRDefectsH
#define uTFRDefectsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFRDefects : public TFrame
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
private:	// User declarations
public:		// User declarations
	__fastcall TFRDefects(TComponent* Owner);
	void Set(int _val);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRDefects *FRDefects;
//---------------------------------------------------------------------------
#endif
