#ifndef TTLSignalH
#define TTLSignalH
#include<System.hpp>

class TTLSignal
{
private:
	unsigned int mask;
	bool prev;

public:
	TTLSignal(void);
	TTLSignal(int _pos, AnsiString _name);
	void SetPos(int _pos);
	int Exec(unsigned int _w);

	AnsiString Name;
};
#endif
