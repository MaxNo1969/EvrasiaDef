#ifndef PipeClientH
#define PipeClientH
#include <Classes.hpp>
#include <SyncObjs.hpp>
class PipeClient
{
private:
	HANDLE hPipe;
	void pr(AnsiString _msg);
	void Write(void* _data, int _size);
	int Read(void* _data, int _size);
	void Write(AnsiString _msg);
	AnsiString Read(void);
	PipeClient(void);
	~PipeClient(void);
	static PipeClient* Instance;
	TCriticalSection* cs;
	AnsiString Command0(AnsiString _cmd);
	AnsiString GetConnectionString(void);
public:
	static AnsiString Command(AnsiString _cmd);
	static void Dispose(void);
};
#endif
