#pragma hdrstop
#include "RChannel_parameters.h"
#include "uFunctions.h"
#include "protocol.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
RChannel_parameters::RChannel_parameters(void)
{
	name = "?";
	phisicalChannel = 0;
	collectedMode = 0;
	range = 0;
}

// ---------------------------------------------------------------------------
RChannel_parameters::RChannel_parameters(PA _pa)
{
	name = "?";
	 phisicalChannel = _pa.Item("ChPhisical").Int();
	collectedMode = _pa.Item("Mode").Int();
	range = _pa.Item("Range").Int();
}

// ---------------------------------------------------------------------------
RChannel_parameters::RChannel_parameters(PA _pa, AnsiString _name)
{
	name = _name;
   phisicalChannel = _pa.Item("ChPhisical").Int();
	collectedMode = _pa.Item("Mode").Int();
	range = _pa.Item("Range").Int();
}

// ---------------------------------------------------------------------------
AnsiString RChannel_parameters::ToString(void)
{
	AnsiString ret = name;
	ret += ":  phisical_ch=";
	ret += phisicalChannel;
	ret += ",mode=";
	ret += collectedMode;
	ret += ",range=";
	ret += range;
	return (ret);
}

// ---------------------------------------------------------------------------
RChannel_parameters::RChannel_parameters(const RChannel_parameters& _p)
{
	name = _p.name;
	phisicalChannel = _p.phisicalChannel;
	collectedMode = _p.collectedMode;
	range = _p.range;
}
// ---------------------------------------------------------------------------
