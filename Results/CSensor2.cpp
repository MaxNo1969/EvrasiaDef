#pragma hdrstop
#include "CSensor2.h"
#include<System.hpp>
#include <SysUtils.hpp>
#pragma package(smart_init)
CSensor2::CSensor2(void)
{
	Gain=0;
	GainBuf=0;
	Offset=0;
}
CSensor2::~CSensor2(void)
{
}


