#pragma hdrstop
#include "TTLSignal.h"
#pragma package(smart_init)

TTLSignal::TTLSignal(void)
{
	mask = 0;
	prev=false;
	Name=NULL;
}
TTLSignal::TTLSignal(int _pos, AnsiString _name)
{
	SetPos(_pos);
	prev=false;
	Name=_name;
}

void TTLSignal::SetPos(int _pos)
{
	if (_pos < 0)
		_pos = 0;
	if (_pos > 17)
		_pos = 17;
	unsigned int x = 1;
	mask = x << _pos;
}

int TTLSignal::Exec(unsigned int _w)
{
	bool v = _w && mask;
	if(prev==v)
		return(0);
	prev=v;
	if(v)
		return(1);
	else
		return(-1);
}
