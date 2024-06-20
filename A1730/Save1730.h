#ifndef Save1730H
#define Save1730H
#include<System.hpp>

class Save1730
{
private:
	struct IOtag
	{
		WORD in;
		WORD out;
	};
	IOtag* IO;
	int size;
	int count;
	AnsiString fname;
	void Save(void);
public:
	Save1730(AnsiString _path);
	~Save1730(void);
	void Add(DWORD _in, DWORD _out);

	inline bool IsSave()
	{
		return (IO != NULL);
	}
};
#endif
