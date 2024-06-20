//---------------------------------------------------------------------------

#ifndef uTFRThickH
#define uTFRThickH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "uTFRBorders.h"
#include <ExtCtrls.hpp>
#include "uTFRSplit.h"
#include "uTFRDefects.h"
#include "CTube.h"
#include <VclTee.TeeGDIPlus.hpp>
//#include <VclTee.TeeGDIPlus.hpp>
//---------------------------------------------------------------------------
class TFRThick : public TFrame
{
__published:	// IDE-managed Components
	TChart *Chart1;
	TBarSeries *Series3;
	TFRBorders *FRBordersThick;
	TLabel *Label2;
	TCheckBox *cbThick;
	TPanel *Panel3;
	TLabel *Label3;
	TPanel *Panel2;
	TFRDefects *FRDefects1;
	TPanel *Panel1;
	TLabel *Label1;
	void __fastcall FrameResize(TObject *Sender);
	void __fastcall cbThickClick(TObject *Sender);
private:	// User declarations
	void OnChangeChild(void);
	void LoadSettings0(void);
public:		// User declarations
	__fastcall TFRThick(TComponent* Owner);
	typedef void(__closure * OnChangeDef)(void);
	OnChangeDef OnChange;
	void Clear(void);
	void Init(void);
	void LoadSettings(void);
	void SetEnabledR(bool _v);
	void SetDefects(int _val);
	void SetMinThick(double _val,int _nn);
	inline bool IsThick(void)
	{
		return(cbThick->Checked);
	}
	int MinHeight(void);
	void Draw(CTube* _Tube);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRThick *FRThick;
//---------------------------------------------------------------------------
#endif
