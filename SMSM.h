#ifndef SMSMH
#define SMSMH
#include <System.hpp>
#include <SyncObjs.hpp>
#include <vector>
using namespace std;

// ---------------------------------------------------------------------------
class SMSM
{
private:
	static SMSM* Instance;
	HWND main_handle;
	TCriticalSection* cs;
	AnsiString msg;
	UINT MsgId;
	struct Msg
	{
		AnsiString msg;
		AnsiString name;
	};
	vector<Msg> Asc;
	vector<Msg> Ans;

	SMSM(void);
	~SMSM(void);

public:
	static void Init(HWND _main_handle);
	static void Dispose(void);
	static UINT GetMsgId(void);
	static void SetPost(AnsiString _msg);
	static void SetPost(AnsiString _msg,AnsiString _name);
	static AnsiString GetPost(AnsiString* _name,bool* _Ok);
	static void SetAnswer(AnsiString _msg,AnsiString _name);
	static AnsiString GetAnswer(AnsiString _name,bool* _Ok);
};

SMSM* SMSM::Instance = NULL;
// ---------------------------------------------------------------------------
#endif
