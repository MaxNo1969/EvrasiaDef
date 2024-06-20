// ---------------------------------------------------------------------------
#ifndef uCRequestH
#define uCRequestH
// ---------------------------------------------------------------------------
#include<System.hpp>
class CRequest
{
private:
	int timeout;
	int data_size;
	AnsiString data;
	AnsiString cmd;
	int format_size;
	AnsiString IntToHex2(int _v);
	AnsiString IntToHex(int _v);
public:
	int abonent;
	CRequest(int _abonent,int _timeout,AnsiString _type,AnsiString _cmd);
	inline int DataSize()
	{
		return (data_size);
	}
	inline void Data(AnsiString _v)
	{
		data=_v;
	}
	AnsiString Get();
};
#endif
