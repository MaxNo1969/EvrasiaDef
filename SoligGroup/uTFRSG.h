//---------------------------------------------------------------------------

#ifndef uTFRSGH
#define uTFRSGH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "SGR.h"
//---------------------------------------------------------------------------
class TFRSG : public TFrame
{
__published:	// IDE-managed Components
	TPanel *pSolidGroup;
	TGroupBox *GroupBox1;
	TCheckBox *CheckBox1;
	TEdit *Edit1;
	TCheckBox *CheckBox2;
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
private:	// User declarations
	void Save(void);
	bool block;
public:		// User declarations
	__fastcall TFRSG(TComponent* Owner);
	void Init(void);
	void LoadSettings(void);
	void Set(AnsiString _SolidGroup,TColor _SolidGroupColor);
	void Clear();
	void CopyFrom(TFRSG* _th);
	inline bool IsFix(void)
	{
		return(CheckBox1->Checked);
	}
	inline bool IsSG(void)
	{
		return (CheckBox2->Checked);
	}
	AnsiString SGGroup(void);
	typedef void (__closure * OnTFRTubeHistoryChange)(bool _IsFix,AnsiString _SGroupFix);
	OnTFRTubeHistoryChange OnChange;
	AnsiString GetFix(void);
	void Set(SGR::SG _sg);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRSG *FRSG;
//---------------------------------------------------------------------------
#endif
