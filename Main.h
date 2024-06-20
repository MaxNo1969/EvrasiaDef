//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------

#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <ExtCtrls.hpp>
#include <VCLTee.Series.hpp>
#include <Dialogs.hpp>
#include <AppEvnts.hpp>
#include <XPMan.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <ActnCtrls.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <ActnMenus.hpp>
#include <PlatformDefaultStyleActnCtrls.hpp>
#include <ToolWin.hpp>
#include "uFRStatist.h"
#include "uTFRButtons.h"
#include "uTFRCross.h"
#include "uTFRLineRemote.h"
#include "uTFRSG.h"
#include "uTFRSOP.h"
#include "uTFRSplit.h"
#include "uTFRSumM.h"
#include "uTFRThick.h"
#include <System.Actions.hpp>
#include <vector>

#include "uTFRCross.h"
#include "uTFRLineRemote.h"
#include "uTFRThick.h"
#include "uTFRSOP.h"
#include "uTFRSG.h"
#include "uTFRSumM.h"

#include "uFRStatist.h"
#include "uTFRButtons.h"
#include "uTFRSplit.h"
#include "ThBase.h"
#include "Bank.h"
#include "ACS.h"
#include "WinWork.h"


#include "SignalServer.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published: //IDE-managed Components

	TStatusBar *StatusBarTop;
	TCheckBox *cbInterruptView;
	TSaveDialog *SaveToFileDialog;
	TOpenDialog *OpenDialogFromFile;
	TApplicationEvents *ApplicationEvents;
	TPopupMenu *OtherTest;
	TMenuItem *TestRotation;
	TXPManifest *XPManifest1;
	TFRLineRemote *FRLine1;
	TFRThick *FRThick1;
	TActionManager *ActionManager1;
	TAction *Action1;
	TAction *Action2;
	TAction *Action3;
	TAction *Action4;
	TAction *Action5;
	TAction *Action7;
	TAction *Action8;
	TAction *Action9;
	TAction *Action10;
	TAction *Action11;
	TAction *Action12;
	TAction *Action13;
	TAction *Action14;
	TAction *Action15;
	TAction *Action16;
	TAction *Action17;
	TAction *Action18;
	TAction *Action19;
	TAction *Action20;
	TAction *Action21;
	TActionMainMenuBar *ActionMainMenuBar1;
	TAction *Action6;
	TFRStatist *FRStatist1;
	TAction *Action22;
	TAction *Action23;
	TAction *Action24;
	TAction *Action25;
	TButton *Button1;
	TAction *Action26;
	TFRButtons *FRButtons1;
	TFRSumM *FRSumM1;
	TFRCross *FRCross1;
	TFRSplit *FRSplit1;
	TFRSplit *FRSplit2;
	TFRSplit *FRSplit3;
	TPanel *Panel4;
	TAction *Action27;
	TFRSOP *FRSOP1;
	TLabel *Label1;
	TFRSG *FRSG1;
	TAction *ActionPars;
	//выравнивает объекты на форме, работает в начале работы и при Resize
	//стандартные функции
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall menuSignalsStateClick(TObject *Sender);
	void __fastcall menuSaveTubeClick(TObject *Sender);
	void __fastcall menuLoadTubeClick(TObject *Sender);
	void __fastcall menuTestAdvantechClick(TObject *Sender);
	void __fastcall menuProtocolClick(TObject *Sender);
	void __fastcall ApplicationEventsMessage(tagMSG &Msg, bool &Handled);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall Action25Execute(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall Action27Execute(TObject *Sender);
	void __fastcall ActionParsExecute(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);

private: //User declarations

	//настройки типоразмеров
	void LoadSettings(void);
	//читает настройки из ini файла, заполняет едиты, устанавли пороги, мертвые зоны

	//блокировка
	void SetAbleButtons(bool state);

	void ChangeDecision(void);

	UINT thread_msg;
	bool isView;
	Bank* bank;

	void ReDraw(void);
	void pr(AnsiString _msg);

	//AnsiString tube_number;
	void UpdateStatus(AnsiString _text1, AnsiString _text2);
	void ClearCharts(void);

	void BlockMainMenu(bool _state);

	void OnClickButton(AnsiString _button);

	ThBase* thCurrent;

	void Post(void);
	void DoThreadMessage(void);

	int prevHeight;
	AnsiString title_prefix;
	AnsiString user;
	AnsiString client;
	void StartWorkSOP(AnsiString _button);
	bool WasSOP;
	IsWork GetIsWork(void);
	void OnLoadSettings(void);
	IsWork IW;
	void AddResultZone(void);
	SignalServer* signalServer;
//	double TubeLengthFX;
	ACS* acs;
	WinWork winWork;
	bool IsAuto;
public: //User declarations

	__fastcall TMainForm(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
#endif
