#ifndef TransportEventH
#define TransportEventH
#include <System.hpp>
#include "Signal.h"
#include "TTLSignal.h"
#include "SignalEvent.h"

class TransportEvent
{
private:
protected:
	DWORD tick;
	int position;
	void pr(AnsiString _msg);
	AnsiString Name;
public:
	TransportEvent(void);
	virtual AnsiString ToString(void);

	inline DWORD When(void)
	{
		return (tick);
	}

	inline int Position(void)
	{
		return (position);
	}
};

class TESignal : public TransportEvent
{
private:
	void* signal;
	bool need;
	bool was;
public:
	TESignal(CSignal* _signal, bool _need, int _position);
	TESignal(TTLSignal* _signal, bool _need, int _position);
	AnsiString ToString();
	bool Check(SignalEvent* _event);

	inline bool Was(void)
	{
		return (was);
	}
};

class TEStrobe : public TransportEvent
{
private:
	void* signal;
	bool need;
	int count;
	int zone_size;
	int start_position;
	double speed;
public:
	TEStrobe(void* _signal, bool _need, int _position, int _zone_size);
	DWORD first_tick;
	AnsiString ToString();
	bool Check(SignalEvent* _event);

	inline double Speed(void)
	{
		return (speed);
	}
};

#endif
