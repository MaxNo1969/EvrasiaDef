#ifndef JSpeed502H
#define JSpeed502H
#include "Job.h"
#include "Inverter.h"

//---------------------------------------------------------------------------
class JSpeed502 : public Job
{
private:
	enum class ECmd
	{
		Speed, Stop, None
	};
	int step;
	DWORD startTick;
	ECmd cmd;
	ECmd state;
	int frequency;
	void SetError(AnsiString _msg);
	AnsiString type;
	void ExecStop(void);
	void ExecSpeed(void);
	void ExecCheck(void);
	Inverter* inverter;
public:
	JSpeed502(AnsiString _type, CInv* _Inv);
	~JSpeed502(void);
	int GetSpeed();
	void SetSpeed(int _frequency);
	void SetSpeed(void);
	void Exec(void);
	void Reset(void);

	inline bool IsComplete()
	{
		return (cmd == ECmd::None);
	}
};
//---------------------------------------------------------------------------
#endif
