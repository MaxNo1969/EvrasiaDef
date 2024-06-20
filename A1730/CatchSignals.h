#ifndef CatchSignalsH
#define CatchSignalsH
#include "Signal.h"
#include "SignalEvent.h"

class CatchSignals
{
public:
private:
	int signals_size;
	int size;
	CSignal** signals;
	SignalEvent* events;
	int count_done;
	int count;

	inline int GetCount(void)
	{
		return(count);
	}
	SignalEvent* Get(int _index);
	bool started;
public:
	CatchSignals(int _signals_size, int _size);
	~CatchSignals(void);
	void AddSignal(int _index, CSignal* _signal);
	void Clear(void);
	void Start(void);
	void Stop(void);
	SignalEvent* GetNext(void);
	void Exec(void);
	void Report(void);
};
#endif
