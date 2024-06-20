#ifndef ProtocolH
#define ProtocolH
#include "uTFProtocol.h"
class TPr
{
private:
	TPr(void);
	~TPr(void);
	static TPr* Instance;
	TCriticalSection* cs;
	TFProtocol* FProtocol;
public:
	void static pr(AnsiString _msg);
	void static Clear(void);
	void static Dispose(void);
	void static Show(void);
	void static DateTimeMark(AnsiString _msg);
	void static DateTimeMark(void);
};
#endif
