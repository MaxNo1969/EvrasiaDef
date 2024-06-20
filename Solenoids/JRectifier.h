#ifndef JRectifierH
#define JRectifierH
#include <StdCtrls.hpp>
#include "Job.h"
#include "Rectifier.h"
class RectifierTh;
class JRectifier : public Job
{
private:
	friend RectifierTh;
	ModBus modBus;
	Rectifier Cross;
	Rectifier Thick;
	TCriticalSection* CS1;
	bool Stop0(char _tp);
	bool Exec0(char _tp);
	AnsiString GetErrorMsg0(char _tp);
	RectifierTh* CrossTh;
	RectifierTh* ThickTh;
	void pr(AnsiString _msg);
	Rectifier::State StateCross;
	Rectifier::State StateThick;
	bool ExecTh(char _tp);
public:
	JRectifier();
	~JRectifier(void);

	bool Start(char _tp);
	bool Stop(char _tp);
	void Exec(void);
	char GetIU(char _tp);
	Rectifier::State GetState(char _c);
};
class RectifierTh : public TThread
{
private:
	void __fastcall Execute();
	JRectifier* jRectifier;
	char tp;
public:
	__fastcall RectifierTh(JRectifier* _jRectifier, char _tp);
};
#endif
