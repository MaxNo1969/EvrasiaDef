#ifndef ReplyFXH
#define ReplyFXH
#include<System.hpp>

class ReplyFX
{
private:
	int Abonent;
	int PLC;
protected:
	AnsiString Head;
public:
	ReplyFX(int _Abonent, int _PLC);
	virtual bool Parse(AnsiString _l) = 0;
};

class ReplyFX_NAK : public ReplyFX
{
public:
	ReplyFX_NAK(int _Abonent, int _PLC) : ReplyFX(_Abonent, _PLC)
	{
		Error="Ok";
	}
	bool Parse(AnsiString _l);
	AnsiString Error;
};

class ReplyFX_ACK : public ReplyFX
{
public:
	ReplyFX_ACK(int _Abonent, int _PLC) : ReplyFX(_Abonent, _PLC)
	{
	}
	bool Parse(AnsiString _l);
};

class ReplyFX_STX : public ReplyFX
{
public:
	ReplyFX_STX(int _Abonent, int _PLC) : ReplyFX(_Abonent, _PLC)
	{
	}
	bool Parse(AnsiString _l);
	AnsiString result;
};
#endif
