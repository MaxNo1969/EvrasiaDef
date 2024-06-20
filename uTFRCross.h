//---------------------------------------------------------------------------

#ifndef uTFRCrossH
#define uTFRCrossH
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
#include "uTFRDeads.h"
#include "uTFRSplit.h"
#include "uTFRDefects.h"
#include "CTube.h"
#include "uFViewZoneS.h"
#include "uFViewZoneD.h"
#include <VclTee.TeeGDIPlus.hpp>
//#include <VclTee.TeeGDIPlus.hpp>


//---------------------------------------------------------------------------
class TFRCross : public TFrame
{
__published: //IDE-managed Components
	TFRBorders *FRBordersCross;
	TChart *Chart1;
	TPanel *Panel1;
	TFRDeads *FRDeads1;
	TCheckBox *cbCross;
	TLabel *Label2;
	TFRDefects *FRDefects1;

	void __fastcall SeriesDblClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button, TShiftState Shift,
		int X, int Y);
	void __fastcall SeriesClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button, TShiftState Shift,
		int X, int Y);
	void __fastcall cbCrossClick(TObject *Sender);

private: //User declarations
	void OnChangeChild(void);
	int mark_zone;
	int mark_sensor;
	bool mark_is;
	TColor mark_color;
	void LoadSettings0(void);
	TFViewZoneD* SensorFormD;
	TFViewZoneS* SensorFormS;
	CTube* Tube;
public: //User declarations
		typedef void(__closure * OnChangeDef)(void);
	__fastcall TFRCross(TComponent* Owner);
	__fastcall ~TFRCross(void);
	void Clear(void);
	void Init(void);
	void LoadSettings(void);

	OnChangeDef OnChange;

	void SetEnabledR(bool _v);
	void MarkerSet(int _zone, int _sensor);
	void MarkerOff(void);
	typedef void(__closure * OnClickDef)(int _zone, int _sensor, bool _IsCtrl);

	OnClickDef OnClick;

	typedef void(__closure * OnDblClickDef)(int _zone, int _sensor, bool _IsCtrl);

	OnDblClickDef OnDblClick;

	void SetDefects(int _val);

	inline bool IsCross(void)
	{
		return (cbCross->Checked);
	}
	int MinHeight(void);
	void Draw(CTube* _Tube);
};

//---------------------------------------------------------------------------
extern PACKAGE TFRCross *FRCross;
//---------------------------------------------------------------------------
#endif
