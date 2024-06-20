#pragma hdrstop
#include "TransportEvent.h"
#include "Protocol.h"
#pragma package(smart_init)

TransportEvent::TransportEvent(void)
{
	tick = 0;
	position = 0;
	Name=NULL;
}

AnsiString TransportEvent::ToString(void)
{
	AnsiString ret = "TE: position=";
	ret += position;
	if (tick != 0)
	{
		ret += ", When=";
		ret += tick;
	}
	return (ret);
}

void TransportEvent::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("TE: ") + _msg);
}

// =====================================================================================================
TESignal::TESignal(CSignal* _signal, bool _need, int _position)
{
	signal = _signal;
	Name=_signal->GetName();
	need = _need;
	position = _position;
	was=false;
}
TESignal::TESignal(TTLSignal* _signal, bool _need, int _position)
{
	signal = _signal;
	Name=_signal->Name;
	need = _need;
	position = _position;
	was=false;
}

AnsiString TESignal::ToString(void)
{
	AnsiString ret = TransportEvent::ToString();
	ret += ", signal=";
	ret+=Name;
	ret+=" need=";
	ret += need ? "true" : "false";
	return (ret);
}

bool TESignal::Check(SignalEvent* _event)
{
	if(was)
		return(true);
	if (_event->signal != signal)
		return (false);
	if (_event->value != need)
		return (false);
	tick = _event->tick;
	was=true;
	return (true);
}

// =====================================================================================================
TEStrobe::TEStrobe(void* _signal, bool _need, int _position, int _zone_size)
{
	signal = _signal;
	need = _need;
	position = 0;
	zone_size = _zone_size;
	start_position = _position;
	speed = 0;
	first_tick = 0;
	count = 0;
}

AnsiString TEStrobe::ToString(void)
{
	AnsiString ret = TransportEvent::ToString();
	ret += ", signal=Strobe, need=";
	ret += need ? "true" : "false";
	ret += ", speed=";
	ret += speed;
	ret += ", count=";
	ret += count;
	return (ret);
}

bool TEStrobe::Check(SignalEvent* _event)
{
	if (_event->signal != signal)
		return (false);
	if (_event->value != need)
		return (false);
	speed = zone_size;
	if (count == 0)
		speed /= _event->tick - first_tick;
	else
		speed /= _event->tick - tick;
	tick = _event->tick;
	count++;
	position = start_position + count * zone_size;
	return (true);
}
