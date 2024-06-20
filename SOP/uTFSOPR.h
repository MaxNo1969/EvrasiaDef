//---------------------------------------------------------------------------

#ifndef uTFSOPRH
#define uTFSOPRH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "uTFRSOPCheck.h"
//---------------------------------------------------------------------------
class TFSOPR : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TDataSource *DataEtalons;
	TDBNavigator *DBNavigator1;
	TLabel *Label1;
	TDBGrid *DBGrid2;
	TLabel *Label2;
	TADOTable *ADOTable1;
	TADOTable *ADOTable2;
	TDataSource *DataSource2;
	TDBNavigator *DBNavigator2;
	TDataSource *DataSource3;
	TADOTable *ADOTable3;
	TDBNavigator *DBNavigator3;
	TDBGrid *DBGrid3;
	TLabel *Label3;
	TPanel *Panel;
	TLabel *LTS;
	TLabel *lDateFrom;
	TLabel *lDateTo;
	TComboBox *cbTypeSize;
	TDateTimePicker *dtpTo;
	TDateTimePicker *dtpFrom;
	TButton *Button1;
	TButton *Button3;
	TFRSOPCheck *FRSOPCheck1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ADOTable1NewRecord(TDataSet *DataSet);
	void __fastcall ADOTable3BeforeRefresh(TDataSet *DataSet);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall cbTypeSizeChange(TObject *Sender);
	void __fastcall DBNavigator3BeforeAction(TObject *Sender, TNavigateBtn Button);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall DBGrid2ColExit(TObject *Sender);
	void __fastcall DataSource2UpdateData(TObject *Sender);
	void __fastcall ADOTable1AfterDelete(TDataSet *DataSet);
	void __fastcall ADOTable1AfterInsert(TDataSet *DataSet);
	void __fastcall ADOTable1AfterPost(TDataSet *DataSet);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall DataSource2DataChange(TObject *Sender, TField *Field);


private:	// User declarations
	AnsiString GetFilter(void);
	AnsiString user;
	AnsiString group;
	TColumn* FindColumn(TDBGrid* _grid,AnsiString _name);
	AnsiString CheckPickList(TStrings* _list,AnsiString _val);
	void CheckFields(bool _update);
	void __fastcall GetYesNot(TField* Sender, System::UnicodeString &Text, bool DisplayText);
	void __fastcall SetYesNot(TField* Sender, System::UnicodeString Text);
	void UpdateJournal(void);
public:		// User declarations
	__fastcall TFSOPR(TComponent* Owner, AnsiString _user,AnsiString _group);
	bool need_reload;
};
//---------------------------------------------------------------------------
extern PACKAGE TFSOPR *FSOPR;
//---------------------------------------------------------------------------
#endif
