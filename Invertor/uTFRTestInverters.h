//---------------------------------------------------------------------------

#ifndef uTFRTestInvertersH
#define uTFRTestInvertersH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uTFRTestInverter.h"
//---------------------------------------------------------------------------
class TFRTestInverters : public TFrame
{
__published:	// IDE-managed Components
	TFRTestInverter *ThickInverter;
private:	// User declarations
	CInv* Inv;
public:		// User declarations
	__fastcall TFRTestInverters(TComponent* Owner);
	__fastcall ~TFRTestInverters(void);
	void Init(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRTestInverters *FRTestInverters;
//---------------------------------------------------------------------------
#endif
