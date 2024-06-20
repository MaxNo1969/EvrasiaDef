#ifndef JTransportH
#define JTransportH
#include "Bank.h"
#include "Signal.h"
#include <vector>
using namespace std;

// ---------------------------------------------------------------------------
class JTransport
{
private:
	struct Point
	{
		bool On;
		DWORD tick;
		double position;
		CSignal* signal;

		Point(TIniFile* _ini, CSignal* _signal,bool _On);
		AnsiString ToString(void);
		bool Check(bool _half);
	};

	int TubeLength;
	double TubeLengthTest;
	double TubeSpeed_mm_ms;
	vector<Point>MP;
	Bank* bank;
	DWORD startTick;
	Point* p_length_test;
//	Point* p_length0;
//	Point* p_length1;
	Point* p_base1_off;
	Point* p_base2_on;
	Point* p_speed0;
	Point* p_speed1;
	Point* p_half;
//	Point* p_base1;
	bool half;

	void pr(AnsiString _msg);

	bool started;

	Point* Find(CSignal* _signal,bool _On);

	bool error;
	AnsiString errorMsg;
	bool IsThick;
	bool IsCross;
	bool IsLine;

public:
	JTransport(TIniFile* _ini, Bank* _bank, bool _IsThick, bool _IsCross,
		bool _IsLine);
	void Start(void);
	bool Exec(DWORD _tick);
	bool ExecTest(DWORD _tick);
	void Report(void);

	inline bool IsError(void)
	{
		return (error);
	};

	inline AnsiString GetErrorMsg()
	{
		return (errorMsg);
	}
};
// ---------------------------------------------------------------------------
#endif
