#ifndef CTubeH
#define CTubeH
#include "CCross.h"
#include "CLine.h"
#include "CThick.h"
#include "CSum.h"
#include <System.hpp>

class CTube
{
private:
	bool Load(FILE* _df);

	bool LoadSet(FILE* _df);
	void SaveSet(FILE* _df, AnsiString _user);
	void pr(AnsiString _msg);
	AnsiString GetZoneList(int _maxZones);
	void DeleteOldFiles(AnsiString _TubePath);
	enum class EState { Empty, Ok, Error };
	EState State;
	AnsiString Batch;
public:
	CTube(void);
	CTube(FILE* _df);
	void Save(AnsiString _user);
	void Save(AnsiString _FileName, AnsiString _user);
	void Save(FILE* _df, AnsiString _user);
	bool Calc(void);

	CCross Cross;
	CLine Line;
	CThick Thick;
	CSum RSum;

	void CalcSum(void);

	inline bool IsError(void)
	{
		return (State==EState::Error);
	}

	void LoadSettings(void);
	void SaveToDB(AnsiString _user, AnsiString _client, AnsiString _sgname,
		double _length);
	void SaveToDB(AnsiString _user, AnsiString _client, AnsiString _sgname);
};
#endif
