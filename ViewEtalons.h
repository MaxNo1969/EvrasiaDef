//---------------------------------------------------------------------------

#ifndef ViewEtalonsH
#define ViewEtalonsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <DBCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <IniFiles.hpp>
#include <DB.hpp>
#include <ADODB.hpp>
#include <map>
#include <cstdio.h>
//---------------------------------------------------------------------------
class TFormViewEtalons : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGridEtalons;
	TPanel *Panel;
	TLabel *LSG;
	TComboBox *ComboBoxSG;
	TLabel *LTS;
	TComboBox *ComboBoxTS;
	TButton *View;
	TDBNavigator *DBNavigatorEtalons;
	TPopupMenu *pmExport;
	TSaveDialog *SaveDialog;
	TMenuItem *N1;
	TOpenDialog *OpenDialog;
	TMenuItem *SelectAll;
	TDataSource *DataEtalons;
	TADOQuery *QEtalons;
	TMenuItem *N2;
	void __fastcall ViewClick(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall menuExportClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall SelectAllClick(TObject *Sender);
	void __fastcall menu60Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);


private:	// User declarations
	TIniFile *ini;
public:		// User declarations
	__fastcall TFormViewEtalons(TComponent* Owner);
	void SetIni(TIniFile* _ini);
	bool need_loadsettings;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormViewEtalons *FormViewEtalons;
//---------------------------------------------------------------------------
#endif
