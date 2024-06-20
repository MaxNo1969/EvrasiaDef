//---------------------------------------------------------------------------

#ifndef uFViewZoneDH
#define uFViewZoneDH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.ArrowCha.hpp>
#include <VCLTee.BubbleCh.hpp>
#include <VCLTee.Series.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "CTube.h"
#include <VclTee.TeeGDIPlus.hpp>
//#include <VclTee.TeeGDIPlus.hpp>
#include <vector>

//---------------------------------------------------------------------------
class TFViewZoneD : public TForm
{
__published: //IDE-managed Components

	TChart *Chart1;
	TStatusBar *StatusBar1;
	TBarSeries *BarOut;
	TBarSeries *BarIn;
	TLineSeries *Out1;
	TLineSeries *Out2;
	TLineSeries *In1;
	TLineSeries *In2;
	TLineSeries *Zero;
	TLineSeries *Devider1;
	TLineSeries *Devider2;
	TLineSeries *DeviderIn1;
	TLineSeries *DeviderIn2;
	TComboBox *cbEtalonTubeDefects;
	TPanel *Panel1;
	TArrowSeries *Arrow;
	TBubbleSeries *Mark;

	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbEtalonTubeDefectsKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Chart1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

private: //User declarations

	AnsiString title;
	double start;
	double zone_size;
	int curr_zone;
	int curr_sens;
	int DevidMeas1;
	int DevidMeas2;
	bool IsLinear;
	int curr_defect;
	bool KeyUpFlag;
	double levelOut1;
	double levelOut2;
	double levelIn1;
	double levelIn2;
	bool mouse_on;

	void SetBorder(TLineSeries* _series, double _level, TColor _color);
	//Рисует границы дефектов
	void SetBrackBorder(int _startMeas, int _finalMeas, double _Border, TColor _color, AnsiString _mark);
	CMeas::TP Tp;
	void Draw(void);
	CTube* Tube;
	void pr(AnsiString _msg);

public: //User declarations
	void SetMetric(double _start, double _zone_size);
	__fastcall TFViewZoneD(TComponent* Owner, CMeas::TP _Tp, AnsiString _title);
	void SetCaption(AnsiString _cap);
	void Clear(void);
	void SetInner(bool _v);
	void SetCurrPoint(int _curr_zone, int _curr_sens, bool _IsLinear);
	//показывает границы поиска дефектов СОП
	void ViewEtalonCheck(void);
	//расчитывает измерение на графике в зависимости от расстояния
	int CalcMeasFromRange(int _x);

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

	inline void AddDevider1(int _meas, TColor _color)
	{
		DevidMeas1 = _meas;
		Devider1->AddXY(_meas, 0, "", _color);
		Devider1->AddXY(_meas, 100, "", _color);
	};

	inline void AddDevider2(int _meas, TColor _color)
	{
		DevidMeas2 = _meas;
		Devider2->AddXY(_meas, 0, "", _color);
		Devider2->AddXY(_meas, 100, "", _color);
	};

	inline void AddDeviderIn1(int _meas, TColor _color)
	{
		DeviderIn1->AddXY(_meas, -100, "", _color);
		DeviderIn1->AddXY(_meas, 0, "", _color);
	};

	inline void AddDeviderIn2(int _meas, TColor _color)
	{
		DeviderIn2->AddXY(_meas, -100, "", _color);
		DeviderIn2->AddXY(_meas, 0, "", _color);
	};

	inline void SetBorderOut1(double _level, TColor _color)
	{
		if (_level < 0)
			_level = -_level;
		levelOut1 = _level;
		SetBorder(Out1, _level, _color);
	}

	inline void SetBorderOut2(double _level, TColor _color)
	{
		if (_level < 0)
			_level = -_level;
		levelOut2 = _level;
		SetBorder(Out2, _level, _color);
	}

	inline void SetBorderIn1(double _level, TColor _color)
	{
		if (_level > 0)
			_level = -_level;
		levelIn1 = _level;
		SetBorder(In1, _level, _color);
	}

	inline void SetBorderIn2(double _level, TColor _color)
	{
		if (_level > 0)
			_level = -_level;
		levelIn2 = _level;
		SetBorder(In2, _level, _color);
	}

	inline void SetZero(void)
	{
		SetBorder(Zero, 0, clBlack);
	}
	void Draw(CTube* _Tube, int _zone, int _sensor);
};
#endif
