// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ViewEtalons.h"
#include "uFunctions.h"
#include "uCDBS.h"
#include "GraphicsCenters.h"
#include "protocol.h"
#include "uCExecSQL.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormViewEtalons *FormViewEtalons;

// ---------------------------------------------------------------------------
__fastcall TFormViewEtalons::TFormViewEtalons(TComponent* Owner) : TForm(Owner)
{
	KeyPreview = true;
}

// ---------------------------------------------------------------------------
void __fastcall TFormViewEtalons::ViewClick(TObject *Sender)
{
	need_loadsettings = false;
	QEtalons->Close();
	QEtalons->Active = false;
	QEtalons->SQL->Clear();
	AnsiString SQL;
	SQL = "SELECT SGEtalon.*,";
	SQL += "Si.value as Si,Si.id_etalon as Si_id,Si.elem as Si_elem,";
	SQL += "Mn.value as Mn,Mn.id_etalon as Mn_id,Mn.elem as Mn_elem,";
	SQL += "Cr.value as Cr,Cr.id_etalon as Cr_id,Cr.elem as Cr_elem,";
	SQL += "Ni.value as Ni,Ni.id_etalon as Ni_id,Ni.elem as Ni_elem,";
	SQL += "Mo.value as Mo,Mo.id_etalon as Mo_id,Mo.elem as Mo_elem";
	SQL += " FROM   SGEtalon";
	SQL += " INNER JOIN SGEtalonChem as Si ON SGEtalon.id = Si.id_etalon and Si.elem='Si'";
	SQL += " INNER JOIN SGEtalonChem as Mn ON SGEtalon.id = Mn.id_etalon and Mn.elem='Mn'";
	SQL += " INNER JOIN SGEtalonChem as Cr ON SGEtalon.id = Cr.id_etalon and Cr.elem='Cr'";
	SQL += " INNER JOIN SGEtalonChem as Ni ON SGEtalon.id = Ni.id_etalon and Ni.elem='Ni'";
	SQL += " INNER JOIN SGEtalonChem as Mo ON SGEtalon.id = Mo.id_etalon and Mo.elem='Mo' ";
	AnsiString WhereStr = "";
	if ((ComboBoxSG->Text == "Все") && (ComboBoxTS->Text == "Все"))
		WhereStr = "";
	else if ((ComboBoxSG->Text != "Все") && (ComboBoxTS->Text == "Все"))
		WhereStr = "where SGEtalon.Name='" + ComboBoxSG->Text + "'";
	else if ((ComboBoxSG->Text == "Все") && (ComboBoxTS->Text != "Все"))
		WhereStr = "where SGEtalon.TypeSize='" + ComboBoxTS->Text + "'";
	else if ((ComboBoxSG->Text != "Все") && (ComboBoxTS->Text != "Все"))
		WhereStr = "where ((SGEtalon.Name='" + ComboBoxSG->Text +
			"') and (SGEtalon.TypeSize='" + ComboBoxTS->Text + "'))";
	SQL += WhereStr;
	SQL += " order by SGEtalon.id";
	QEtalons->SQL->Add(SQL);

	QEtalons->ExecSQL();
	QEtalons->Active = true;

	// DBGridEtalons->DataSource = DataEtalons;
	// DBNavigatorEtalons->DataSource = DataEtalons;
}

// ---------------------------------------------------------------------------

void __fastcall TFormViewEtalons::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == 27)
		FormViewEtalons->Close();
}

// ---------------------------------------------------------------------------
void __fastcall TFormViewEtalons::FormActivate(TObject *Sender)
{
	LoadFormPos(this, ini);
	QEtalons->Connection = DBS->Connection();
	ComboBoxSG->Clear();
	ComboBoxTS->Clear();

	SolidGroups::Group g;
	TStringList * gr = g.getGroupNames();
	ComboBoxSG->Items->Add("Все");
	ComboBoxSG->Items->AddStrings(gr);
	ComboBoxSG->ItemIndex = 0;

	SolidGroups::TubeType tt;
	TStringList * ti = tt.getTubeTypeNames();
	ComboBoxTS->Items->Add("Все");
	ComboBoxTS->Items->AddStrings(ti);
	ComboBoxTS->ItemIndex = 0;
}
// ---------------------------------------------------------------------------

void __fastcall TFormViewEtalons::menuExportClick(TObject *Sender)
{
	map<String, int>_map;
	_map["D"] = -1;
	_map["K"] = 0;
	_map["E"] = 1;

	if (DBGridEtalons->SelectedRows->Count > 0)
	{
		if (SaveDialog->Execute())
		{
			FILE* file;
			file = fopen(AnsiString(SaveDialog->FileName).c_str(), "w");
			if (file == NULL)
			{
				Application->MessageBoxW(L"Не удалось открыть файл для записи данных",
					L"Ошибка", MB_ICONERROR | MB_OK);
				return;
			}
			else
			{
				int number = 1;
				QEtalons->First();
				while (!QEtalons->Eof)
				{
					if (DBGridEtalons->SelectedRows->CurrentRowSelected)
					{
						if (number > 1)
							fprintf(file, "\n");
						fprintf(file, "%d ", number);

						for (int j = 0; j < 8; j++)
							fprintf(file, "%d ",
							QEtalons->FieldByName("p" + String(j + 1))->AsInteger);

						fprintf(file, "%d",
							_map[QEtalons->FieldByName("Name")->AsString]);
						number++;

					}
					QEtalons->Next();
				}
			}
			fclose(file);
		}
	}
}

// ----------------------------------------------------------------------------
void __fastcall TFormViewEtalons::N1Click(TObject *Sender)
{
	vector<int>IndexSelectedField;
	if (DBGridEtalons->SelectedRows->Count > 0)
	{
		QEtalons->First();
		int index = 0;
		while (!QEtalons->Eof)
		{
			if (DBGridEtalons->SelectedRows->CurrentRowSelected)
				IndexSelectedField.push_back(index);
			index++;
			QEtalons->Next();
		}
		GraphicCentersForm->IndexField.clear();
		GraphicCentersForm->IndexField = IndexSelectedField;
		GraphicCentersForm->Show();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFormViewEtalons::SelectAllClick(TObject *Sender)
{
	QEtalons->First();
	while (!QEtalons->Eof)
	{
		DBGridEtalons->SelectedRows->CurrentRowSelected = true;
		QEtalons->Next();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TFormViewEtalons::menu60Click(TObject *Sender)
{
	if (OpenDialog->Execute())
	{
		map<int, String>_map;
		_map[-1] = "D";
		_map[0] = "K";
		_map[1] = "E";
		FILE* file;
		file = fopen(AnsiString(OpenDialog->FileName).c_str(), "r");
		if (file == NULL)
		{
			Application->MessageBoxW(L"Не удалось открыть файл для чтения ",
				L"Ошибка", MB_ICONERROR | MB_OK);
			return;
		}
		else
		{
			DM->tTemp->Active = true;
			while (!feof(file))
			{
				int index;
				fscanf(file, "%d", &index); // номер строки - мусор
				vector<int>parameters; // 8 параметров
				for (int i = 0; i < 8; i++)
				{
					fscanf(file, "%d", &index);
					parameters.push_back(index);
				}

				if (parameters.size() != 8)
				{
					Application->MessageBoxW(L"Ошибка",
						L"Не удалось считать параметры ГП", MB_OK);
					break;
				}
				else
				{
					DM->tTemp->Append();
					for (int i = 1; i <= 8; i++)
						DM->tTemp->FieldByName("p" + IntToStr(i))->AsString =
							parameters[i - 1];
				}
				fscanf(file, "%d", &index);
				DM->tTemp->FieldByName("Name")->AsString = _map[index];
				DM->tTemp->FieldByName("TypeSize")->AsString =
					IntToStr(((TMenuItem*)Sender)->Tag);
				DM->tTemp->FieldByName("Date")->AsString = Date();
				DM->tTemp->Post();
			}
		}
		fclose(file);
	}
}

// ---------------------------------------------------------------------------
void TFormViewEtalons::SetIni(TIniFile* _ini)
{
	ini = _ini;
}

void __fastcall TFormViewEtalons::FormClose(TObject *Sender, TCloseAction &Action)
{
	SaveFormPos(this, ini);
}
// ---------------------------------------------------------------------------

void __fastcall TFormViewEtalons::FormResize(TObject *Sender)
{
	DBNavigatorEtalons->Top = ClientHeight - DBNavigatorEtalons->Height - 3;
	DBGridEtalons->Height = DBNavigatorEtalons->Top - 2 - DBGridEtalons->Top;
}

// ---------------------------------------------------------------------------
void __fastcall TFormViewEtalons::N2Click(TObject *Sender)
{
	if (Application->MessageBoxW(L"Удалить записи?",
		L"Номер трубы", MB_YESNO) == IDNO)
		return ;

	QEtalons->First();
	while (!QEtalons->Eof)
	{
		if (DBGridEtalons->SelectedRows->CurrentRowSelected)
		{
			int id = QEtalons->FieldByName("ID")->AsInteger;
			AnsiString SQL;
			SQL = "delete from dbo.SGEtalon where id=";
			SQL += id;
			TPr::pr(SQL);
			CExecSQL E(SQL);
			SQL = "delete from dbo.SGEtalonChem where id_etalon=";
			SQL += id;
			TPr::pr(SQL);
			CExecSQL EE(SQL);
		}
		QEtalons->Next();
	}
	ViewClick(this);
	need_loadsettings = true;
}
// ---------------------------------------------------------------------------
