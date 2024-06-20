// ---------------------------------------------------------------------------

#ifndef uTFRSumH
#define uTFRSumH
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
#include <VclTee.TeeGDIPlus.hpp>
//#include <VclTee.TeeGDIPlus.hpp>
// ---------------------------------------------------------------------------
class TFRSum : public TFrame
{
__published: // IDE-managed Components
	TGroupBox *gbSummary;
	TLabel *Label7;
	TLabel *lCut1;
	TLabel *Label9;
	TLabel *lCut2;
	TLabel *Label8;
	TLabel *lNN;
	TChart *Chart1;
	TBarSeries *Series4;
	TEdit *eMin_Good_Length;
	TPanel *lResult;
	TPanel *pNN;
	TPanel *Panel1;
	void __fastcall FrameResize(TObject *Sender);
	void __fastcall eMin_Good_LengthKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall eMin_Good_LengthExit(TObject *Sender);

private: // User declarations
	AnsiString section;
	void Save(void);
public: // User declarations
	__fastcall TFRSum(TComponent* Owner);
	void Init(void);
	void LoadSettings(void);
	void Clear(void);
	void SetDecision(AnsiString _name,TColor _color,int _cut1,int _cut2);
	typedef void(__closure * OnTFRSumChange)(void);
	OnTFRSumChange OnChange;
};
// ---------------------------------------------------------------------------
extern PACKAGE TFRSum *FRSum;
// ---------------------------------------------------------------------------
#endif
