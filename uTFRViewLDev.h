// ---------------------------------------------------------------------------

#ifndef uTFRViewLDevH
#define uTFRViewLDevH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <ExtCtrls.hpp>
#include "CTube.h"
#include <VclTee.TeeGDIPlus.hpp>
//#include <VclTee.TeeGDIPlus.hpp>

// ---------------------------------------------------------------------------
class TFRViewLDev : public TFrame
{
__published: // IDE-managed Components

	TChart *Chart1;

	void __fastcall Chart1ClickSeries(TCustomChart *Sender, TChartSeries *Series, int ValueIndex, TMouseButton Button,
		TShiftState Shift, int X, int Y);

public:
	typedef void(__closure * OnClickSeriesDef)(int _zone);

private: // User declarations

	CTube* Tube;
	CCrossLine* CL;
	int max_zones;
	AnsiString Head;
	OnClickSeriesDef onClickSeries;

	void FOnClickSeries(OnClickSeriesDef _v);
	void FOnKeyDown(TKeyEvent _v);

public: // User declarations
	__fastcall TFRViewLDev(TComponent* Owner);
	void Init(CTube* _Tube, CMeas::TP _Tp, int _max_zones);
	void Draw(void);
	void ReDraw();
	__property OnClickSeriesDef OnClickSeries =
	{write = FOnClickSeries};
	__property TKeyEvent OnKeyDown =
	{write = FOnKeyDown};
	void ColorZone(int _zone);
	void ColorZone(int _zone, TColor _color);
};

// ---------------------------------------------------------------------------
extern PACKAGE TFRViewLDev *FRViewLDev;
// ---------------------------------------------------------------------------
#endif
