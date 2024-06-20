#ifndef SingletonH
#define SingletonH
#include "CTube.h"

class CSingleton
{
private:
	bool inner;

	void LoadSettings0(void);

	TComponent* Owner;

	void SaveSet(FILE* _df, AnsiString _user);
	bool LoadSet(FILE* _df);

	AnsiString TubePath;
	int TubeRest;

	void pr(AnsiString _msg);

public:
	CSingleton(TComponent* _Owner);
	~CSingleton();

	AnsiString user;

	inline bool IsInner(void)
	{
		return (inner);
	};
	void LoadSettings(void);

	bool FromFile;

	void SaveTubeToDB(AnsiString _user, AnsiString _client, AnsiString _sgname);
	void SaveTubeToDB(AnsiString _user, AnsiString _client, AnsiString _sgname,double _length);
	void Save(AnsiString _user);
	void Save(AnsiString _FileName, AnsiString _user);
	bool Load(AnsiString _FileName);
	void Clear(void);

	CTube* Tube;
};

extern CSingleton* Singleton;
#endif
