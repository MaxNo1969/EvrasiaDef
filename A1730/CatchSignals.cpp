#pragma hdrstop
#include "CatchSignals.h"
#include "uFunctions.h"
#include "Protocol.h"
#pragma package(smart_init)

CatchSignals::CatchSignals(int _signals_size, int _size)
{
	signals_size = _signals_size;
	if (size < 0)
		size = 0;
	size = _size;
	if (size < 0)
		size = 0;
	signals = new CSignal*[signals_size];
	events = new SignalEvent[size];
	Clear();
}

CatchSignals::~CatchSignals(void)
{
	delete signals;
	delete events;
}

void CatchSignals::Clear(void)
{
	count = 0;
	count_done = 0;
	started = false;
}

void CatchSignals::Start(void)
{
	started = true;
}

void CatchSignals::Stop(void)
{
	started = false;
}

void CatchSignals::AddSignal(int _index, CSignal* _signal)
{
	signals[_index] = _signal;
}

SignalEvent* CatchSignals::Get(int _index)
{
	if (_index >= count)
		return (NULL);
	return (events + _index);
}

SignalEvent* CatchSignals::GetNext(void)
{
	if (count_done >= count)
		return (NULL);
	return (events + count_done++);
}

void CatchSignals::Exec(void)
{
	if (!started)
		return;
	for (int i = 0; i < signals_size; i++)
	{
		CSignal* s = signals[i];
		if (s->value_prev != s->value)
		{
			if (count >= size)
				return;
			// FATAL(AnsiString("CatchSignals::Exec: превышен буфер событий: ")
			// +size);
			SignalEvent* e = events + count;
			e->signal = s;
			e->tick = s->last_changed;
			e->value = s->value;
			count++;
		}
	}
}

void CatchSignals::Report(void)
{
	for (int i = 0; i < count; i++)
	{
		AnsiString a = "CatchSignals: ";
		SignalEvent* e = events + i;
//		a += e->signal->name;
//		a += "=";
		a += e->value ? "true" : "false";
		a += " tick=";
		a += e->tick;
		a += i < count_done ? " done" : "";
		TPr::pr(a);
	}
}
