// ---------------------------------------------------------------------------

#ifndef uFRViewZoneH
#define uFRViewZoneH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.ArrowCha.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "cspin.h"
#include "CTube.h"
#include "SerCursor.h"
#include <VclTee.TeeGDIPlus.hpp>
//#include <VclTee.TeeGDIPlus.hpp>

// ---------------------------------------------------------------------------
class TFRViewZone : public TFrame
{
__published: // IDE-managed Components

	TChart *Chart1;
	TBarSeries *BarOut;
	TLineSeries *Out1;
	TLineSeries *Out2;
	TEdit *Edit1;
	TBarSeries *BarIn;
	TLineSeries *In1;
	TLineSeries *In2;
	TLineSeries *Zero;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TCSpinButton *CSpinButton1;
	TCheckBox *CheckBox1;

	void __fastcall FrameResize(TObject *Sender);
	void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall Chart1ClickSeries(TCustomChart *Sender, TChartSeries *Series, int ValueIndex, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall Chart1ClickBackground(TCustomChart *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall CSpinButton1UpClick(TObject *Sender);
	void __fastcall CSpinButton1DownClick(TObject *Sender);

private: // User declarations
	void SetBorder(TLineSeries* _series, double _level, TColor _color);

	int sensor;
	SerCursor rCursor;

	double step;

	CMeas::TP Tp;

	CTube* Tube;

	inline void AddOut(double _level, TColor _color)
	{
		if (_level < 0)
			_level = -_level;
		BarOut->AddY(_level, "", _color);
	};

	inline void AddIn(double _level, TColor _color)
	{
		if (_level > 0)
			_level = -_level;
		BarIn->AddY(_level, "", _color);
	};

	inline void SetBorderOut1(double _level, TColor _color)
	{
		if (_level < 0)
			_level = -_level;
		SetBorder(Out1, _level, _color);
	}

	inline void SetBorderOut2(double _level, TColor _color)
	{
		if (_level < 0)
			_level = -_level;
		SetBorder(Out2, _level, _color);
	}

	inline void SetBorderIn1(double _level, TColor _color)
	{
		if (_level > 0)
			_level = -_level;
		SetBorder(In1, _level, _color);
	}

	inline void SetBorderIn2(double _level, TColor _color)
	{
		if (_level > 0)
			_level = -_level;
		SetBorder(In2, _level, _color);
	}
	void TrigerVisible(void);

	inline void SetZero(void)
	{
		SetBorder(Zero, 0, clBlack);
	}
	void Clear(void);
	void SetGain(double _gain);

	inline void SetZoneColor(TColor zoneColor)
	{
		Chart1->Color = zoneColor;
	}
	void OnSetCursor(int _val, double _level);
	AnsiString title;
	void pr(AnsiString _msg);

public: // User declarations

	__fastcall TFRViewZone(TComponent* Owner, CMeas::TP _Tp, CTube* _Tube, int _sensor, bool _gain_visible, bool _check_visible);
	__fastcall ~TFRViewZone(void);
	void Draw(int _zone);
	void SetInner(bool _v);

	typedef void(__closure * OnChangeGainDef)(int _sensor, double _gain);

	OnChangeGainDef OnChangeGain;

	typedef void(__closure * OnCalibrateDef)(TFRViewZone * _arc);

	OnCalibrateDef OnCalibrate;

	inline void SetStep(double _step)
	{
		step = _step;
	}

	inline bool NeedCalibrate(void)
	{
		return (CheckBox1->Checked);
	}

	inline int GetSensor(void)
	{
		return (sensor);
	}
};
#endif
