#pragma hdrstop
#include <time.h>
#include <sys/stat.h>
#include <IOUtils.hpp>
#include "Singleton.h"
#include "Protocol.h"
#include "uFunctions.h"
#include "uCExecSQL.h"
#include "uCExecute.h"
#include "uCSelect.h"
#include "Filters.h"
#include "PA.h"
#include "FileEntry.h"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
CSingleton* Singleton = NULL;

// ---------------------------------------------------------------------------
CSingleton::CSingleton(TComponent* _Owner)
{
	Owner = _Owner;
	FromFile = false;
	LoadSettings0();
	Tube = new CTube();
}

// ---------------------------------------------------------------------------
CSingleton::~CSingleton()
{
	delete Tube;
}

// ---------------------------------------------------------------------------
void CSingleton::Clear(void)
{
	delete Tube;
	Tube=new CTube();
	FromFile = false;
}

// ---------------------------------------------------------------------------
void CSingleton::LoadSettings0(void)
{
	TubePath = PA("Defect.Some.TubePath").String();
	TubeRest = PA("Defect.Some.MaxCountSaveTubes").Int();
}

// ---------------------------------------------------------------------------
void CSingleton::LoadSettings(void)
{
	TubePath = PA("Defect.Some.TubePath").String();
	TubeRest = PA("Defect.Some.MaxCountSaveTubes").Int();
}

// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
void CSingleton::SaveTubeToDB(AnsiString _user, AnsiString _client,
	AnsiString _sgname, double _length)
{
	Tube->SaveToDB(_user,_client,_sgname,_length);
}
void CSingleton::SaveTubeToDB(AnsiString _user, AnsiString _client,
	AnsiString _sgname)
{
	Tube->SaveToDB(_user,_client,_sgname);
}

// ---------------------------------------------------------------------------
void CSingleton::Save(AnsiString _FileName, AnsiString _user)
{
	Tube->Save(_FileName, _user);
}

// ---------------------------------------------------------------------------
bool CSingleton::Load(AnsiString _FileName)
{
	FILE* df;
	try
	{
		df = fopen(_FileName.c_str(), "rb");
		if (df == NULL)
		{
			Application->MessageBoxW(L"Не удалось загрузить файл", L"Ошибка",
				MB_ICONERROR | MB_OK);
			return (false);
		}
		delete Tube;
		Tube = new CTube(df);
		fclose(df);
		if (Tube->IsError())
		{
			delete Tube;
			Tube = new CTube();
			return (false);
		}
	}
	catch (...)
	{
		delete Tube;
		Tube = new CTube(df);
		Application->MessageBoxW(L"Не удалось загрузить файл", L"Ошибка",
			MB_ICONERROR | MB_OK);
		fclose(df);
		return (false);
	}
	FromFile = true;
	return (true);
}


// ---------------------------------------------------------------------------
void CSingleton::Save(AnsiString _user)
{
	Tube->Save(_user);
}

// ---------------------------------------------------------------------------
void CSingleton::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("Singleton: ") + _msg);
}
