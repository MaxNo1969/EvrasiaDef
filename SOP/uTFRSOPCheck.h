//---------------------------------------------------------------------------

#ifndef uTFRSOPCheckH
#define uTFRSOPCheckH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <vector>
using namespace std;

//---------------------------------------------------------------------------
class TFRSOPCheck : public TFrame
{
__published:	// IDE-managed Components
	TPanel *pResultBit;
	TMemo *mCheckedDefects;
	TButton *bSave;
	TPanel *pResultNum;
	TGroupBox *GroupBox1;
	void __fastcall bSaveClick(TObject *Sender);
	void __fastcall FrameResize(TObject *Sender);
private:	// User declarations
	int numOfDefects;
	int matchedDefects;
	// Данные по трубе
//	vector<vector<vector<double> > >CrossFilteredOut_Data;
//	vector<double>CrossGain;
//	vector<vector<bool> >CrossDeads;
//	vector<vector<vector<double> > >LinearFilteredOut_Data;
//	vector<vector<vector<double> > >LinearFilteredIn_Data;
//	vector<double>LinearGain;
//	vector<vector<bool> >LinearDeads;
	AnsiString SOP;
	AnsiString user;
	AnsiString group;
	AnsiString TypeSize;

	void EtalonCheck();
	bool DefectCheck(AnsiString _Module, AnsiString _DefType, int _DefPoint,
		int _DefRadius, bool _isTopBrackBorder, double _TopBorderPercent,
		bool _isBottomBrackBorder, double _BottomBorderPercent);

	bool CheckDiap(AnsiString _Module, int _sensor, bool _isBrackBorder,
		double _borderPercent, int _startPoint, int _endPoint);
	bool CheckDefType(AnsiString _Module, AnsiString _DefType,
		vector<int>dirtyFind);
	bool AddMemoResult(bool _matched, AnsiString _module, int _defPoint);

	void SetData();
public:		// User declarations
	__fastcall TFRSOPCheck(TComponent* Owner);
	void Init(AnsiString _user,AnsiString _group);
	void Exec(AnsiString _SOP, AnsiString _TypeSize);
	typedef void(__closure * OnUpdateDef)(void);
	OnUpdateDef OnUpdate;
};
//---------------------------------------------------------------------------
extern PACKAGE TFRSOPCheck *FRSOPCheck;
//---------------------------------------------------------------------------
#endif
