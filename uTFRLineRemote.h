// ---------------------------------------------------------------------------

#ifndef uTFRLineRemoteH
#define uTFRLineRemoteH
// ---------------------------------------------------------------------------
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
#include "uTFRDeads.h"
#include "uTFRSplit.h"
#include "uTFRDefects.h"
#include "CTube.h"
#include <VclTee.TeeGDIPlus.hpp>
//#include <VclTee.TeeGDIPlus.hpp>

// ---------------------------------------------------------------------------
class TFRLineRemote : public TFrame
{
__published: // IDE-managed Components

	TCheckBox *cbLinear;
	TFRBorders *FRBordersLine;
	TPanel *Panel1;
	TChart *Chart1;
	TBarSeries *Series1;
	TBarSeries *Series2;
	TBarSeries *Series3;
	TFRDeads *FRDeads1;
	TBarSeries *Series4;
	TLabel *Label2;
	TFRDefects *FRDefects1;

	void __fastcall cbLinearClick(TObject *Sender);

private: // User declarations
	void LoadSettings0(void);

	void OnChangeChild(void);

	CTube* Tube;

	void SetDefects(int _val);

public: // User declarations
	__fastcall TFRLineRemote(TComponent* Owner);
	__fastcall ~TFRLineRemote(void);
	void Clear(void);
	void Init(void);
	void LoadSettings(void);
	void SetEnabledR(bool _v);
	int MinHeight(void);
	void Draw(CTube* _Tube);

	inline bool IsLinear(void)
	{
		return (cbLinear->Checked);
	}

	typedef void(__closure * OnChangeDef)(void);

	OnChangeDef OnChange;
};

// ---------------------------------------------------------------------------
extern PACKAGE TFRLineRemote *FRLineRemote;
// ---------------------------------------------------------------------------
#endif
