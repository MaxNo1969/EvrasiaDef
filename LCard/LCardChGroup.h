#ifndef LCardChGroupH
#define LCardChGroupH
#include "RChannel_parameters.h"

//---------------------------------------------------------------------------
class LCardChGroup
{
private:
	TList* channels;

public:
	LCardChGroup(void);
	LCardChGroup(PA _pa);
	~LCardChGroup(void);
	LCardChGroup(LCardChGroup& _g);
	LCardChGroup& operator=(LCardChGroup& _g);
	void LoadSettings(PA _pa);
	RChannel_parameters operator[](AnsiString _name);
	RChannel_parameters operator[](int _index);
	RChannel_parameters Item(AnsiString _name);
	RChannel_parameters Item(int _index);
	void Add(RChannel_parameters _p);
	void Add(LCardChGroup& _g);

	inline int Count(void)
	{
		return (channels->Count);
	}

	void Clear(void);
};
//---------------------------------------------------------------------------
#endif
