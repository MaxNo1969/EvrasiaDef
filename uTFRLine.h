// ---------------------------------------------------------------------------

#ifndef uTFRLineH
#define uTFRLineH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include "uTFRBorders.h"
#include <ExtCtrls.hpp>
#include "uTFRDeads.h"
#include "uTFRSplit.h"
#include "uTFRDefects.h"
#include "CTube.h"
#include "uFViewZoneS.h"
#include "uFViewZoneD.h"
#include <VclTee.TeeGDIPlus.hpp>

// ---------------------------------------------------------------------------
class TFRLine : public TFrame
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
	void __fastcall SeriesDblClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall SeriesClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y);

private: // User declarations
	void LoadSettings0(void);

	int mark_zone;
	int mark_sensor;
	bool mark_is;
	TColor mark_color;

	void OnChangeChild(void);

	TFViewZoneD* SensorFormD;
	TFViewZoneS* SensorFormS;
	CTube* Tube;

	void MarkerSet(int _zone, int _sensor);
	void MarkerOff(void);

	void SetDefects(int _val);

public: // User declarations
	__fastcall TFRLine(TComponent* Owner);
	__fastcall ~TFRLine(void);
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
	typedef void(__closure * OnClickDef)(int _zone, int _sensor, bool _IsCtrl);

	OnClickDef OnClick;

	typedef void(__closure * OnDblClickDef)(int _zone, int _sensor, bool _IsCtrl);

	typedef void(__closure * OnChangeDef)(void);

	OnChangeDef OnChange;
};

// ---------------------------------------------------------------------------
extern PACKAGE TFRLine *FRLine;
// ---------------------------------------------------------------------------
#endif
