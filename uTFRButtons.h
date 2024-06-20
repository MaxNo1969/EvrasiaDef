//---------------------------------------------------------------------------

#ifndef uTFRButtonsH
#define uTFRButtonsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFRButtons : public TFrame
{
__published:	// IDE-managed Components
	TSpeedButton *SBTest;
	TSpeedButton *SBView;
	TSpeedButton *SBWork;
	TSpeedButton *SBManage;
	TSpeedButton *SBCancel;
	TSpeedButton *SBReturn;
	TSpeedButton *SBPass;
	TSpeedButton *SBSOP;
	void __fastcall SBWorkClick(TObject *Sender);
	void __fastcall SBViewClick(TObject *Sender);
	void __fastcall SBReturnClick(TObject *Sender);
	void __fastcall SBPassClick(TObject *Sender);
	void __fastcall SBTestClick(TObject *Sender);
	void __fastcall SBManageClick(TObject *Sender);
	void __fastcall SBCancelClick(TObject *Sender);
	void __fastcall SBSOPClick(TObject *Sender);
private:	// User declarations
	void Disable(void);
public:		// User declarations
	typedef void(__closure * DefROnClick)(AnsiString _button);
	DefROnClick ROnClick;
	__fastcall TFRButtons(TComponent* Owner);
	void Enable(void);
	void Interrupt();
};
//---------------------------------------------------------------------------
extern PACKAGE TFRButtons *FRButtons;
//---------------------------------------------------------------------------
#endif
