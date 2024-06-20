#pragma hdrstop
#include "CMin.h"
#pragma package(smart_init)
CMin::CMin(void)
{
	was=false;
	val=0;
}
void CMin::Add(int _val)
{
	if(!was)
		val=_val;
	else
	{
		if(val>_val)
			val=_val;
	}
	was=true;
}