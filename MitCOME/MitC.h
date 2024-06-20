#ifndef MitCH
#define MitCH
#include<System.hpp>

class MitC
{
public:
	static char ENQ;
	static char STX;
	static char ETX;
	static char ACK;
	static char NAK;
	static char CR;
	static char LF;

	inline AnsiString ENQs()
	{
		return (AnsiString(ENQ));
	}

	inline static AnsiString STXs()
	{
		return (AnsiString(STX));
	}

	inline static AnsiString ETXs()
	{
		return (AnsiString(ETX));
	}

	inline static AnsiString ACKs()
	{
		return (AnsiString(ACK));
	}

	inline static AnsiString NAKs()
	{
		return (AnsiString(NAK));
	}

	inline static AnsiString CRs()
	{
		return (AnsiString(CR));
	}

	inline static AnsiString LFs()
	{
		return (AnsiString(LF));
	}
	static AnsiString MitC::CRC(AnsiString _packet);

};
#endif
