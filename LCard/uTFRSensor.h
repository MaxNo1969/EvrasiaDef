//---------------------------------------------------------------------------

#ifndef uTFRSensorH
#define uTFRSensorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cspin.h"
#include "RChannel_parameters.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFRSensor : public TFrame
{
__published:	// IDE-managed Components
	TLabel *LName;
	TComboBox *CBRange;
	TCSpinEdit *SEChannel;
	TComboBox *CBMode;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TPopupMenu *PopupMenu2;
	TMenuItem *N2;
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
private:	// User declarations
	TIniFile* ini;
	int GetRange(void);
	int GetChannel(void);
	int GetMode(void);
	RChannel_parameters ch_par;
	int pop_item;
public:		// User declarations
	__fastcall TFRSensor(TComponent* Owner);
	__fastcall TFRSensor(TComponent* Owner,RChannel_parameters _ch_par,AnsiString _title);
	void Init(RChannel_parameters _ch_par,AnsiString _title);
	void SetEnabledR(bool _v);
	void SaveSettings(void);
	void SetFocused(TFRSensor* _p);
	typedef void(__closure * OnPopDef)(TFRSensor* _p);
	OnPopDef OnPop;
};
//---------------------------------------------------------------------------
extern PACKAGE TFRSensor *FRSensor;
//---------------------------------------------------------------------------
#endif
