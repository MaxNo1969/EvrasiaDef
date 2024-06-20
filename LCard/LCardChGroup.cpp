#pragma hdrstop
#include "LCardChGroup.h"
#include "uFunctions.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
LCardChGroup::LCardChGroup(void)
{
	channels = new TList();
}

//---------------------------------------------------------------------------
LCardChGroup::LCardChGroup(PA _pa)
{
	channels = new TList();
	LoadSettings(_pa);
}

LCardChGroup::~LCardChGroup(void)
{
	Clear();
	delete channels;
}

//---------------------------------------------------------------------------
LCardChGroup::LCardChGroup(LCardChGroup& _g)
{
	channels = new TList();
	Add(_g);
}
//---------------------------------------------------------------------------
LCardChGroup& LCardChGroup::operator = (LCardChGroup & _g)
{
	if(this==&_g)
		return(*this);
	Clear();
	Add(_g);
	return(_g);
}

//---------------------------------------------------------------------------
void LCardChGroup::LoadSettings(PA _pa)
{
	int count=_pa.GetCount();
	for (int i = 0; i < count; i++)
		channels->Add(new RChannel_parameters(_pa[i]));
}

//---------------------------------------------------------------------------
RChannel_parameters LCardChGroup:: operator[](AnsiString _name)
{
	for (int i = 0; i < channels->Count; i++)
	{
		RChannel_parameters* p = (RChannel_parameters*)channels->Items[i];
		if (p->name == _name)
			return (*p);
	}
	FATAL("LCardChGroup: канал не найден");
	RChannel_parameters ppp=RChannel_parameters(PA());
	return (RChannel_parameters(PA()));
}

//---------------------------------------------------------------------------
RChannel_parameters LCardChGroup:: operator[](int _index)
{
	RChannel_parameters* p = (RChannel_parameters*)channels->Items[_index];
	return (*p);
}

//---------------------------------------------------------------------------
RChannel_parameters LCardChGroup::Item(AnsiString _name)
{
	for (int i = 0; i < channels->Count; i++)
	{
		RChannel_parameters* p = (RChannel_parameters*)channels->Items[i];
		if (p->name == _name)
			return (*p);
	}
	FATAL("LCardChGroup: канал не найден");
	return (RChannel_parameters(PA()));
}

//---------------------------------------------------------------------------
RChannel_parameters LCardChGroup::Item(int _index)
{
	RChannel_parameters* p = (RChannel_parameters*)channels->Items[_index];
	return (*p);
}

//---------------------------------------------------------------------------
void LCardChGroup::Add(RChannel_parameters _p)
{
	channels->Add(new RChannel_parameters(_p));
}

//---------------------------------------------------------------------------
void LCardChGroup::Add(LCardChGroup& _g)
{
	for (int i = 0; i < _g.channels->Count; i++)
		channels->Add(new RChannel_parameters(_g.Item(i)));
}

//---------------------------------------------------------------------------
void LCardChGroup::Clear(void)
{
	for (int i = 0; i < channels->Count; i++)
	{
		RChannel_parameters* p = (RChannel_parameters*)channels->Items[i];
		delete p;
	}
	channels->Clear();
}
//---------------------------------------------------------------------------
