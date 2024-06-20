#ifndef CatchTTLH
#define CatchTTLH
#include "uCRListT.h"
#include "TTLSignal.h"
#include "SignalEvent.h"

class CatchTTL
{
private:
	DWORD startTick;
	double frequency;

	CRListT<TTLSignal>S;

//	TTLSignal Control;
//	TTLSignal Strobe;

	double TickByCount_Ms(int _count);
	CRListT<SignalEvent>L;
	CatchTTL(DWORD _tick, double _real_frequency_Hz);
	static CatchTTL* Instance;

	void Add0(unsigned int* _buf, int _size);
	SignalEvent* GetNext0(void);
	TTLSignal* ByName0(AnsiString _Name);
	int count_in;
	int count_out;

public:
	static void Start(DWORD _tick, double _real_frequency_Hz);
	static void Add(unsigned int* _buf, int _size);
	static SignalEvent* GetNext(void);
	static void Dispose(void);
	static TTLSignal* ByName(AnsiString _Name);
};
extern CatchTTL* Instance=NULL;
#endif
