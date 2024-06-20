#pragma hdrstop
#include <time.h>
#include "CTube.h"
#include "uFunctions.h"
#include "PA.h"
#include "Filters.h"
#include "Protocol.h"
#include "uCExecSQL.h"
#include "uCExecute.h"
#include "uCSelect.h"
#include "Classer.h"
#include "FileEntry.h"
#pragma package(smart_init)

CTube::CTube(void)
{
	/* TODO : Все ли необходимые настройки погрузились? */
	LoadSettings();
	State=EState::Empty;
}

CTube::CTube(FILE* _df)
{
	LoadSettings();
	if (!LoadSet(_df))
	{
		State=EState::Error;
		return;
	}
	if (!Cross.Load(_df))
	{
		State=EState::Error;
		return;
	}
	if (!Line.Load(_df))
	{
		State=EState::Error;
		return;
	}
	if (!Thick.Load(_df))
	{
		State=EState::Error;
		return;
	}
	if (!Calc())
	{
		State=EState::Error;
		return;
	}
	State=EState::Ok;
}

bool CTube::Calc(void)
{
	Cross.Calc();
	Line.Calc();
	Thick.Calc();
	CalcSum();
	return (true);
}

void CTube::CalcSum(void)
{
	int min_zones = 0;

	if (Cross.Size() > 0)
	{
		if (min_zones == 0)
			min_zones = Cross.Size();
		else if (min_zones > Cross.Size())
			min_zones = Cross.Size();
	}
	if (Line.Size() > 0)
	{
		if (min_zones == 0)
			min_zones = Line.Size();
		else if (min_zones > Line.Size())
			min_zones = Line.Size();
	}
	if (Thick.Size() > 0)
	{
		if (min_zones == 0)
			min_zones = Thick.Size();
		else if (min_zones > Thick.Size())
			min_zones = Thick.Size();
	}
	RSum.MZone.Clear();
	RSum.MZone.Capacity(min_zones);

	for (int z = 0; z < min_zones; z++)
	{
		CZoneSum* Z=RSum.MZone.Add();
		if (Cross.Size() > 0 && Cross.MZone[z]->DClass == 0 ||

			Line.Size() > 0 && Line.MZone[z]->DClass == 0 ||

			Thick.Size() > 0 && Thick.MZone[z]->DClass == 0)

			Z->DClass = 0;

		else if (Cross.Size() > 0 && Cross.MZone[z]->DClass == 1 ||

			Line.Size() > 0 && Line.MZone[z]->DClass == 1 ||

			Thick.Size() > 0 && Thick.MZone[z]->DClass == 1)

			Z->DClass = 1;
		else
			Z->DClass = 2;
	}
	RSum.MakeDecision();
	if (Thick.Size() > 0)
		Thick.CalcMinThick(RSum.cut1, RSum.cut2);
}

void CTube::LoadSettings(void)
{
	Batch=PA("Batch").String();
	if(Batch==NULL)
		Batch="?";
	else if(Batch.Length()==0)
		Batch="?";
	Cross.LoadSettings();
	Line.LoadSettings();
	Thick.LoadSettings();
	RSum.LoadSettings();
}

bool CTube::LoadSet(FILE* _df)
{
	// Пропускаем все все
	int size;
	char* s;
	char buf[32];
	int ibuf;
	double dbuf;

	// пользователя просто пропускаем
	Fread(&size, sizeof(size), 1, _df);
	s = new char[size];
	Fread(s, size, 1, _df);
	delete s;

	Fread(&size, sizeof(size), 1, _df);
	s = new char[size + 1];
	Fread(s, size, 1, _df);
	s[size] = '\0';
	AnsiString lTypeSize = s;
	delete s;
	if (lTypeSize != PA("TSSet.Current.Name").String())
	{
		AnsiString a = "Типоразмер в файле: ";
		a += lTypeSize;
		a += " не совпадает с типоразмером в программе";
		WideString w = a;
		Application->MessageBoxW(w.c_bstr(), L"Ошибка", MB_ICONERROR | MB_OK);
		return (false);
	}

	short lsensors;
	Fread(&lsensors, sizeof(lsensors), 1, _df);
	if (lsensors != Cross.Size2())
	{
		AnsiString a = "Количество датчиков поперечного в файле: ";
		a += lsensors;
		a += " не совпадает настройками в программе: ";
		a += Cross.Size2();
		WideString w = a;
		Application->MessageBoxW(w.c_bstr(), L"Ошибка", MB_ICONERROR | MB_OK);
		return (false);
	}

	// gains просто пропускаем
	for (int s = 0; s < Cross.Size2(); s++)
		Fread(&dbuf, sizeof(double), 1, _df);

	// пороги пропускаем
	Fread(&size, sizeof(size), 1, _df);
	for (int i = 0; i < size; i++)
		Fread(buf, sizeof(Cross.borders[0]), 1, _df);

	// пропускаем
	Fread(buf, sizeof(Cross.dead_zone_start), 1, _df);
	Fread(buf, sizeof(Cross.dead_zone_finish), 1, _df);

	Fread(&lsensors, sizeof(lsensors), 1, _df);
	if (lsensors != Line.Size2())
	{
		AnsiString a = "Количество датчиков продольного в файле: ";
		a += lsensors;
		a += " не совпадает настройками в программе: ";
		a += Line.Size2();
		WideString w = a;
		Application->MessageBoxW(w.c_bstr(), L"Ошибка", MB_ICONERROR | MB_OK);
		return (false);
	}
	for (int s = 0; s < Line.Size2(); s++)
		Fread(buf, sizeof(double), 1, _df);
	Fread(&size, sizeof(size), 1, _df);
	for (int i = 0; i < size; i++)
		Fread(buf, sizeof(Line.borders[0]), 1, _df);
	Fread(&size, sizeof(size), 1, _df);
	for (int i = 0; i < size; i++)
		Fread(buf, sizeof(Line.bordersIn[0]), 1, _df);
	Fread(buf, sizeof(Line.dead_zone_start), 1, _df);
	Fread(buf, sizeof(Line.dead_zone_finish), 1, _df);

	Fread(&size, sizeof(size), 1, _df);
	for (int i = 0; i < size; i++)
		Fread(buf, sizeof(Thick.borders[0]), 1, _df);
	Fread(buf, sizeof(short), 1, _df);
	Filters::Settings S = Filters::Settings("?");
	S.Load(_df);
	S.Load(_df);
	S.Load(_df);
	Fread(&buf, sizeof(int), 1, _df);
	Fread(&buf, sizeof(bool), 1, _df);
	return (true);
}

void CTube::SaveSet(FILE* _df, AnsiString _user)
{
	AnsiString TypeSize = PA("TSSet.Current.Name").String();
	int size;
	short sbuf;

	size = _user.Length();
	fwrite(&size, sizeof(size), 1, _df);
	fwrite(_user.c_str(), size, 1, _df);

	size = TypeSize.Length();
	fwrite(&size, sizeof(size), 1, _df);
	fwrite(TypeSize.c_str(), size, 1, _df);

	sbuf = Cross.Size2();
	fwrite(&sbuf, sizeof(sbuf), 1, _df);
	for (int s = 0; s < Cross.Size2(); s++)
		fwrite(&(Cross.MSensor2[s]->Gain), sizeof(double), 1, _df);
	size = 2;
	fwrite(&size, sizeof(size), 1, _df);
	for (int i = 0; i < size; i++)
		fwrite(&(Cross.borders[i]), sizeof(double), 1, _df);

	fwrite(&Cross.dead_zone_start, sizeof(Cross.dead_zone_start), 1, _df);
	fwrite(&Cross.dead_zone_finish, sizeof(Cross.dead_zone_finish), 1, _df);

	sbuf = Line.Size2();
	fwrite(&sbuf, sizeof(sbuf), 1, _df);
	for (int s = 0; s < Line.Size2(); s++)
		fwrite(&(Line.MSensor2[s]->Gain), sizeof(double), 1, _df);
	size = 2;
	fwrite(&size, sizeof(size), 1, _df);
	for (int i = 0; i < size; i++)
		fwrite(&(Line.borders[i]), sizeof(double), 1, _df);
	size = 2;
	fwrite(&size, sizeof(size), 1, _df);
	for (int i = 0; i < size; i++)
		fwrite(&(Line.bordersIn[i]), sizeof(double), 1, _df);
	fwrite(&Line.dead_zone_start, sizeof(Line.dead_zone_start), 1, _df);
	fwrite(&Line.dead_zone_finish, sizeof(Line.dead_zone_finish), 1, _df);

	size = 2;
	fwrite(&size, sizeof(size), 1, _df);
	for (int i = 0; i < size; i++)
		fwrite(&(Thick.borders[i]), sizeof(double), 1, _df);

	sbuf=RSum.min_good_length;
	fwrite(&sbuf, sizeof(sbuf), 1, _df);
	CrossFilter->Save(_df);
	LinearFilterIn->Save(_df);
	LinearFilterOut->Save(_df);
	fwrite(&Cross.WidthMedianFilter, sizeof(Cross.WidthMedianFilter), 1, _df);
	fwrite(&Cross.isMedianFilter, sizeof(Cross.isMedianFilter), 1, _df);
}

void CTube::Save(FILE* _df, AnsiString _user)
{
	SaveSet(_df, _user);
	Cross.Save(_df);
	Line.Save(_df);
	Thick.Save(_df);
}
void CTube::Save(AnsiString _FileName, AnsiString _user)
{
	try
	{
		DWORD tick = GetTickCount();
		FILE* df = fopen(_FileName.c_str(), "wb");
		if (df == NULL)
		{
			State=EState::Error;
			Application->MessageBoxW(L"Не удалось сохранить файл", L"Ошибка",
				MB_ICONERROR | MB_OK);
			return;
		}
		Save(df,_user);
		fclose(df);
		pr(AnsiString().sprintf("Время сохранения DF: %d мс",
			(int)(GetTickCount() - tick)));
	}
	catch (...)
	{
		State=EState::Error;
		Application->MessageBoxW(L"Не удалось сохранить файл", L"Ошибка",
			MB_ICONERROR | MB_OK);
	}
}
void CTube::Save(AnsiString _user)
{
	AnsiString TubePath = PA("Defect.Some.TubePath").String();
	if (TubePath.Length() == 0)
		return;
	DeleteOldFiles(TubePath);
	// Формируем название для новой трубы
	AnsiString FileName = TubePath + "\\Tube_";
	time_t t;
	time(&t);
	tm ltm = *localtime(&t);
	AnsiString fn;
	FileName.cat_printf("%.2d%.2d%.2d_%.2d%.2d%.2d.bindkb", ltm.tm_year - 100,
		ltm.tm_mon + 1, ltm.tm_mday, ltm.tm_hour, ltm.tm_min, ltm.tm_sec);
	pr(FileName);
	Save(FileName, _user);
}
void CTube::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("CTube: ")+_msg);
}
void CTube::SaveToDB(AnsiString _user, AnsiString _client, AnsiString _sgname)
{
	double llength=RSum.ZoneLength*RSum.MZone.Count();
	llength/=1000;
	SaveToDB(_user, _client, _sgname,llength);
}
void CTube::SaveToDB(AnsiString _user, AnsiString _client, AnsiString _sgname,double _length)
{
	AnsiString SQL;
	AnsiString ret;

	CExecSQL* E;
	// Проверяем число записей
	CSelect S1("SELECT COUNT(TubeNum) as nn from dbo.TubesStat");
	if (S1.AsInt("nn") > 60000)
	{
		// Находим самую старую запись
		CSelect S2("Select top 1 * from dbo.TubesStat order by IDTube ASC");
		// Удаляем старые записи с этим номером

		SQL = "Delete from dbo.ZonesStat where TubeNum=";
		SQL += S2.AsInt("TubeNum");
		E = new CExecSQL(SQL);
		delete E;

		SQL = "Delete from dbo.TubesStat where TubeNum=";
		SQL += S2.AsInt("TubeNum");
		E = new CExecSQL(SQL);
		delete E;
	}

	// Ищем последний номер трубы
	CSelect S3("Select top 1 * from dbo.TubesStat order by IDTube Desc");
	// Выбираем новый номер трубы
	int TubeNum = 0;
	TubeNum = S3.AsInt("TubeNum");
	if (TubeNum == 0 || TubeNum == 200000)
		TubeNum = 1;
	else
		TubeNum++;

	// Удаляем старые записи с этим номером
	SQL = "Delete from dbo.ZonesStat where TubeNum=";
	SQL += TubeNum;
	E = new CExecSQL(SQL);
	delete E;

	SQL = "Delete from dbo.TubesStat where TubeNum=";
	SQL += TubeNum;
	E = new CExecSQL(SQL);
	ret = E->IsOk();
	delete E;

	// Вводим новую запись трубы
	SQL = "insert into dbo.TubesStat (TubeNum,DateTime,TypeSize,Result,SolidGroup,";
	SQL += "ThickBrackBorder,NumOfZones,Cut1,Cut2,Defectoscoper,Client,TubeLength,Batch) values(";
	SQL += TubeNum;
	SQL += ",'";
	SQL += DateTimeToStr(Date() + Time());
	SQL += "','";
	SQL += PA("TSSet.Current.Name").String();
	SQL += "','";
	SQL += Classer::ClassString(RSum.DClass);
	SQL += "','";
	SQL += _sgname == NULL ? AnsiString("?") : _sgname;
	SQL += "',";
	AnsiString ss;
	ss.printf("%0.1f,", Thick.MinThick);
	SQL += ss;
	SQL += RSum.Size();
	SQL += ",";
	SQL += RSum.cut1;
	SQL += ",";
	SQL += RSum.cut2;
	SQL += ",'";
	SQL += _user;
	SQL += "','";
	SQL += _client;
	SQL += "',";
	ss.printf("%0.3f,", _length);
	SQL += ss;
	SQL+="'";
	SQL+=Batch;
	SQL+="')";
	TPr::pr(SQL);
	E = new CExecSQL(SQL);
	ret = E->IsOk();
	delete E;
	if (ret != "Ok")
		FATAL(AnsiString("SaveTubeToDB: ") + ret);
	else
	{
		// Ищем номер новой трубы
		CSelect S4("Select top 1 * from dbo.TubesStat order by IDTube Desc");
		int IDTube = 0;
		IDTube = S4.AsInt("IDTube");
		int maxZones=PA("MaxZones").Int();
		if (IDTube > 0)
		{
			// Вводим новые записи по зонам
			// Поперечник
			SQL = "insert into dbo.ZonesStat (TubeID,TubeNum,Module,";
			SQL += GetZoneList(maxZones);
			SQL += ") values(";
			SQL += IDTube;
			SQL += ",";
			SQL += TubeNum;
			SQL += ",'Поперечный'";
			int NumOfZones = Cross.Size();
			int i;
			for (i = 0; i < NumOfZones; i++)
			{
				SQL += ",";
				SQL += Cross.MZone[i]->DClass;
			}
			for (; i < maxZones; i++)
			{
				SQL += ",";
				SQL += 5; // Нет данных (за концом трубы)
			}
			SQL += ")";
			TPr::pr(SQL);
			E = new CExecSQL(SQL);
			ret = E->IsOk();
			delete E;
			if (ret != "Ok")
				FATAL(AnsiString("SaveTubeToDB: ") + ret);

			// Продольник
			NumOfZones = Line.Size();
			if (NumOfZones > 0)
			{
				SQL = "insert into dbo.ZonesStat (TubeID,TubeNum,Module,";
				SQL += GetZoneList(maxZones);
				SQL += ") values(";
				SQL += IDTube;
				SQL += ",";
				SQL += TubeNum;
				SQL += ",'Продольный'";
				for (i = 0; i < NumOfZones; i++)
				{
					SQL += ",";
					SQL += Line.MZone[i]->DClass;
				}
				for (; i < maxZones; i++)
				{
					SQL += ",";
					SQL += 5; // Нет данных (за концом трубы)
				}
				SQL += ")";
				TPr::pr(SQL);
				E = new CExecSQL(SQL);
				ret = E->IsOk();
				delete E;
				if (ret != "Ok")
					FATAL(AnsiString("SaveTubeToDB: ") + ret);
			}
			// Толщиномер
			NumOfZones = Thick.Size();
			if (NumOfZones > 0)
			{
				SQL = "insert into dbo.ZonesStat (TubeID,TubeNum,Module,";
				SQL += GetZoneList(maxZones);
				SQL += ") values(";
				SQL += IDTube;
				SQL += ",";
				SQL += TubeNum;
				SQL += ",'Толщиномер'";
				for (i = 0; i < NumOfZones; i++)
				{
					SQL += ",";
					SQL += Thick.MZone[i]->DClass;
				}
				for (; i < maxZones; i++)
				{
					SQL += ",";
					SQL += 5; // Нет данных (за концом трубы)
				}
				SQL += ")";
				TPr::pr(SQL);
				E = new CExecSQL(SQL);
				ret = E->IsOk();
				delete E;
				if (ret != "Ok")
					FATAL(AnsiString("SaveTubeToDB: ") + ret);
			}
		}
	}
}
AnsiString CTube::GetZoneList(int _maxZones)
{
	AnsiString ret = "";
	for (int i = 1; i <= _maxZones; i++)
	{
		ret += AnsiString("Zone") + i;
		if (i != _maxZones)
			ret += ",";
	}
	return (ret);
}
void CTube::DeleteOldFiles(AnsiString _TubePath)
{
	int TubeRest = PA("Defect.Some.MaxCountSaveTubes").Int();
	if (TubeRest < 0)
		TubeRest = 0;
	HANDLE dir;
	WIN32_FIND_DATA file_data;
	WideString w = _TubePath + "/*";
	if ((dir = FindFirstFile(w.c_bstr(), &file_data)) == INVALID_HANDLE_VALUE)
		return;
	TList *L = new TList();
	L->Capacity = TubeRest >= 100 ? TubeRest : 100;
	do
	{
		if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY != 0)
			continue;
		AnsiString ext = ExtractFileExt(AnsiString(file_data.cFileName));
		if (ext != ".dkb" && ext != ".bindkb")
			continue;
		if (L->Count >= L->Capacity)
			L->Capacity = (int)(((double)L->Capacity) * 1.25);
		L->Add(new FileEntry(&file_data));
	}
	while (FindNextFile(dir, &file_data));
	FindClose(dir);
	// for (int i = 0; i < L->Count; i++)
	// TPr::pr(((FileEntry*)L->Items[i])->name);
	// L->Sort(FileEntry::Comparer);
	// for (int i = 0; i < L->Count; i++)
	// TPr::pr(((FileEntry*)L->Items[i])->ToString());
	if (L->Count > TubeRest)
	{
		L->Sort(FileEntry::Comparer);
		for (int i = 0; i < L->Count - TubeRest; i++)
		{
			AnsiString fname = _TubePath;
			fname += "\\";
			fname += ((FileEntry*)L->Items[i])->name;
			// TPr::pr(AnsiString("To Delete ") + fname);
			remove(fname.c_str());
		}
	}
	for (int i = 0; i < L->Count; i++)
		delete(FileEntry*)(L->Items[i]);
	delete L;
}

