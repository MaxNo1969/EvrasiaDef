// ---------------------------------------------------------------------------

#ifndef uTFRSumMH
#define uTFRSumMH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <ExtCtrls.hpp>
#include "CTube.h"
#include <VclTee.TeeGDIPlus.hpp>
//#include <VclTee.TeeGDIPlus.hpp>

// ---------------------------------------------------------------------------
class TFRSumM : public TFrame
{
__published: // IDE-managed Components

	TPanel *Panel1;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *lCut1;
	TLabel *lCut2;
	TLabel *lNN;
	TEdit *eMin_Good_Length;
	TPanel *lResult;
	TPanel *pNN;
	TChart *Chart1;
	TBarSeries *Series1;
	TLabel *Label1;

	void __fastcall FrameResize(TObject *Sender);
	void __fastcall eMin_Good_LengthKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift);
	void __fastcall eMin_Good_LengthExit(TObject *Sender);
	void __fastcall lResultClick(TObject *Sender);

private: // User declarations

	AnsiString section;
	bool InMetr;
	double mult;
	int max_zones;
	int ZoneLength;

	void Save(void);
	bool isEnable;
	void pr(AnsiString _msg);
public: // User declarations

	__fastcall TFRSumM(TComponent* Owner);
	void Init(void);
	void LoadSettings(void);
	void Clear(void);
	typedef void(__closure * OnTFRSumChange)(void);

	OnTFRSumChange OnChange;
	OnTFRSumChange OnDecision;

	inline bool IsMetr()
	{
		return (InMetr);
	};
	void SetDecision(AnsiString _name, TColor _color, double _cut1,
		double _cut2);
	int MinHeight(void);
	void SetEnabledR1(bool _v);
	void SetEnabledResult(bool _v);
	void SetTubeLenght(double _length);
	void Draw(CTube* _Tube);
};

// ---------------------------------------------------------------------------
extern PACKAGE TFRSumM *FRSumM;
// ---------------------------------------------------------------------------
#endif
