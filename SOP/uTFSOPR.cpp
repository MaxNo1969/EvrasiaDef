//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFSOPR.h"
#include "uFunctions.h"
#include "uCSelect.h"
#include "uCExecSQL.h"
#include "Protocol.h"
#include "Singleton.h"
#include "Protocol.h"
#include "PA.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "uTFRSOPCheck"
#pragma resource "*.dfm"
TFSOPR *FSOPR;

//---------------------------------------------------------------------------
__fastcall TFSOPR::TFSOPR(TComponent* Owner, AnsiString _user,AnsiString _group) : TForm(Owner)
{
	user = _user;
	group=_group;
	need_reload = false;
}

//---------------------------------------------------------------------------
void __fastcall TFSOPR::FormCreate(TObject *Sender)
{
	PA("Defect.Wins").LoadFormPos(this);
	ADOTable1->Connection = DBS->Connection();
	ADOTable1->Active = true;
	ADOTable2->Connection = DBS->Connection();
	ADOTable2->Active = true;
	ADOTable3->Connection = DBS->Connection();
	cbTypeSize->Items->Add("Все");
	for (CSelect S = CSelect("SELECT DISTINCT TypeSize FROM dbo.EtalonCheckResult order by TypeSize"); !S.Eof();
	S.Next())
		cbTypeSize->Items->Add(S.AsAnsiString("TypeSize"));
	cbTypeSize->ItemIndex = 0;
	dtpFrom->DateTime = Date() - 1;
	dtpTo->DateTime = Date();
	ADOTable3->Filter = GetFilter();
	ADOTable3->Active = true;
	if (group == "Master")
	{
		DBNavigator1->VisibleButtons =
			DBNavigator1->VisibleButtons << nbInsert << nbDelete << nbEdit << nbPost << nbCancel;
		DBNavigator2->VisibleButtons =
			DBNavigator2->VisibleButtons << nbInsert << nbDelete << nbEdit << nbPost << nbCancel;
		DBNavigator3->VisibleButtons = DBNavigator3->VisibleButtons << nbDelete;
	}
	else
	{
		DBGrid1->ReadOnly = true;
		DBGrid2->ReadOnly = true;
	}
	Caption = AnsiString("СОПы Оператор ") + user;
	FRSOPCheck1->Init(user,group);
	FRSOPCheck1->OnUpdate = UpdateJournal;
	TField* f;
	f = ADOTable2->Fields->FindField("isTopBrackBorder");
	f->OnGetText = GetYesNot;
	f->OnSetText = SetYesNot;
	f = ADOTable2->Fields->FindField("isBottomBrackBorder");
	f->OnGetText = GetYesNot;
	f->OnSetText = SetYesNot;

	TColumn* с = FindColumn(DBGrid1, "TypeSize");
	с->PickList->Clear();
	PA pa("TSSet");
	int count = pa.GetCount();
	for (int i = 0; i < count; i++)
		с->PickList->Add(pa[i].Item("Name").String());
}

//---------------------------------------------------------------------------
void __fastcall TFSOPR::GetYesNot(TField* Sender, System::UnicodeString &Text, bool DisplayText)
{
	if (Sender->AsBoolean)
		Text = "Да";
	else
		Text = "Нет";
}

//---------------------------------------------------------------------------
void __fastcall TFSOPR::SetYesNot(TField* Sender, System::UnicodeString Text)
{
	if (Text == "Да")
		Sender->Value = true;
	else
		Sender->Value = false;
}

//---------------------------------------------------------------------------
void __fastcall TFSOPR::FormDestroy(TObject *Sender)
{
	PA("Defect.Wins").SaveFormPos(this);
}

//---------------------------------------------------------------------------
void __fastcall TFSOPR::ADOTable1NewRecord(TDataSet *DataSet)
{
	ADOTable1->Fields->FindField("Date")->Value = TDateTime::CurrentDateTime();
}

//---------------------------------------------------------------------------
AnsiString TFSOPR::GetFilter(void)
{
	AnsiString filter = "";
	filter += " Date > '" + DateToStr(dtpFrom->DateTime) + "'";
	filter += " and Date <= '" + DateToStr(dtpTo->DateTime + 1) + "'";
	if (cbTypeSize->Text != "Все")
		filter += " and TypeSize='" + cbTypeSize->Text + "'";
	return (filter);
}

void __fastcall TFSOPR::ADOTable3BeforeRefresh(TDataSet *DataSet)
{
	ADOTable3->Filter = GetFilter();
}
//---------------------------------------------------------------------------

void __fastcall TFSOPR::Button1Click(TObject *Sender)
{
	for (ADOTable3->First(); !ADOTable3->Eof; ADOTable3->Next())
		DBGrid3->SelectedRows->CurrentRowSelected = true;
}
//---------------------------------------------------------------------------

void __fastcall TFSOPR::cbTypeSizeChange(TObject *Sender)
{
	ADOTable3->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFSOPR::DBNavigator3BeforeAction(TObject *Sender, TNavigateBtn Button)

{
	if (Button != TNavigateBtn::nbDelete)
		return;
	for (ADOTable3->First(); !ADOTable3->Eof; ADOTable3->Next())
	{

		if (!DBGrid3->SelectedRows->CurrentRowSelected)
			continue;
		AnsiString SQL;
		SQL = "delete from dbo.EtalonCheckResult where ID=";
		SQL += ADOTable3->FieldByName("ID")->AsInteger;
		CExecSQL E(SQL);
	}
	ADOTable3->Active = false;
	ADOTable3->Active = true;
	Abort();
}
//---------------------------------------------------------------------------

void __fastcall TFSOPR::Button3Click(TObject *Sender)
{
	if (DBGrid1->SelectedRows->Count <= 0)
	{
		Application->MessageBoxW(L"Выберете эталон для проверки!", L"Предупреждение!", MB_ICONWARNING);
		return;
	}
	if (ADOTable1->Fields->FindField("SOP")->Value.IsNull())
		return;
	AnsiString SOP = ADOTable1->Fields->FindField("SOP")->Value;
	AnsiString ts = ADOTable1->FindField("TypeSize")->Value;
	if (PA("TSSet.Current.Name").String() != ts)
	{
		Application->MessageBoxW(L"Текущий типоразмер не совпадает с эталоном!", L"Предупреждение!", MB_ICONWARNING);
		return;
	}
	if (Singleton->Tube->Cross.Size() == 0)
	{
		TPr::pr("Нет трубы для сверки");
		Application->MessageBoxW(L"Нет трубы для сверки!", L"Предупреждение!", MB_ICONWARNING);
		return;
	}
	FRSOPCheck1->Exec(SOP, ts);
}

//---------------------------------------------------------------------------
void TFSOPR::UpdateJournal(void)
{
	ADOTable3->Active = false;
	ADOTable3->Active = true;
}

//---------------------------------------------------------------------------
TColumn* TFSOPR::FindColumn(TDBGrid* _grid, AnsiString _name)
{
	for (int i = 0; i < _grid->Columns->Count; i++)
	{
		TColumn* p = _grid->Columns->Items[i];
		if (p->FieldName == _name)
			return (p);
	}
	return (NULL);
}

//---------------------------------------------------------------------------
void TFSOPR::CheckFields(bool _update)
{
	//TPr::pr("CheckFields");
	TColumn* cDefType = FindColumn(DBGrid2, "DefType");
	TField* fDefType = DBGrid2->DataSource->DataSet->FieldByName("DefType");
	TField* fModule = DBGrid2->DataSource->DataSet->FieldByName("Module");
	AnsiString vDefType;
	if (fDefType->Value.IsNull())
		vDefType = NULL;
	else
		vDefType = fDefType->Value;

	AnsiString v;
	if (fModule->Value.IsNull())
		v = "Empty";
	else
		v = fModule->Value;
	if (v == "Толщиномер")
	{
		cDefType->PickList->Clear();
		cDefType->PickList->Add("Толщина");
		if (_update)
			fDefType->Value = CheckPickList(cDefType->PickList, vDefType);
	}
	else if (v == "Поперечный")
	{
		cDefType->PickList->Clear();
		cDefType->PickList->Add("До 3 соседних");
		cDefType->PickList->Add("Все датчики");
		if (_update)
			fDefType->Value = CheckPickList(cDefType->PickList, vDefType);
	}
	else if (v == "Продольный")
	{
		cDefType->PickList->Clear();
		cDefType->PickList->Add("1 и более");
		cDefType->PickList->Add("Все датчики");
		if (_update)
			fDefType->Value = CheckPickList(cDefType->PickList, vDefType);
	}
	else
	{
		cDefType->PickList->Clear();
		cDefType->PickList->Add("Толщина");
		if (_update)
		{
			fModule->Value = "Толщиномер";
			fDefType->Value = CheckPickList(cDefType->PickList, vDefType);
		}
	}
}

//---------------------------------------------------------------------------
AnsiString TFSOPR::CheckPickList(TStrings* _list, AnsiString _val)
{
	if (_val == NULL)
		return (_list->Strings[0]);
	if (_list->IndexOf(_val) >= 0)
		return (_val);
	return (_list->Strings[0]);
}

void __fastcall TFSOPR::ADOTable1AfterDelete(TDataSet *DataSet)
{
	need_reload = true;
}
//---------------------------------------------------------------------------

void __fastcall TFSOPR::ADOTable1AfterInsert(TDataSet *DataSet)
{
	need_reload = true;
}
//---------------------------------------------------------------------------

void __fastcall TFSOPR::ADOTable1AfterPost(TDataSet *DataSet)
{
	need_reload = true;
}
//---------------------------------------------------------------------------

void __fastcall TFSOPR::FormResize(TObject *Sender)
{
	int space = 2;
	DBNavigator3->Top = ClientHeight - DBNavigator3->Height - space;
	Button1->Top = DBNavigator3->Top;
	DBGrid3->Height = DBNavigator3->Top - DBGrid3->Top;
	DBGrid3->Width = ClientWidth - DBGrid3->Left - space;
}
//---------------------------------------------------------------------------

void __fastcall TFSOPR::DataSource2DataChange(TObject *Sender, TField *Field)
{
	//TPr::pr("DataChange");
	CheckFields(false);
}

//---------------------------------------------------------------------------
void __fastcall TFSOPR::DBGrid2ColExit(TObject *Sender)
{
	//TPr::pr("ColExit");
	CheckFields(false);
}

//---------------------------------------------------------------------------
void __fastcall TFSOPR::DataSource2UpdateData(TObject *Sender)
{
	//TPr::pr("UpdateData");
	CheckFields(true);
}
//---------------------------------------------------------------------------
