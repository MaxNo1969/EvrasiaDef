#ifndef JobH
#define JobH
#include<System.hpp>
#include <vector>
#include "SignalListDef.h"
#include "JHeads.h"
using namespace std;

// ---------------------------------------------------------------------------
class Job
{
private:
	class Alarm
	{
	public:
		bool need;
		CSignal* signal;
		DWORD period;
		Alarm()
		{
            period=0;
        }
	};

	vector<Alarm>LA;

protected:
	bool error;
	AnsiString errorMsg;

	void pr(AnsiString _msg);
	void ppr(AnsiString _msg);

	bool complete;
	void SetError(AnsiString _msg);
	void Exec();

public:
	bool verbal;

	Job(void);
	// virtual ~Job(void){};

	inline bool IsError(void)
	{
		return (error);
	};

	inline AnsiString GetErrorMsg()
	{
		return (errorMsg);
	}
	void ResetError();
	void AddAlarm(CSignal* _signal);
	void AddAlarm(CSignal* _signal, bool _need);
	void AddAlarm(CSignal* _signal, bool _need,int _period);
	void DropAlarm(CSignal* _signal);

	inline void DropAlarms(void)
	{
		LA.clear();
	}
	void Reset(void);
	bool IsComplete();
};
// ---------------------------------------------------------------------------
#endif
