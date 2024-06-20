#pragma hdrstop
#include "Save1730.h"
#pragma package(smart_init)
#include <stdio.h>
#include "PA.h"

Save1730::Save1730(AnsiString _path)
{
	PA pa = PA(_path);
	if (!pa.Item("IsSave").Bool())
	{
		IO = NULL;
		return;
	}
	size = pa.Item("Size").Int() * 1024 * 1024;
	size/=sizeof(IOtag);
	fname=pa.Item("FileName").String();
	count=0;
	IO=new IOtag[size];
}

Save1730::~Save1730()
{
	Save();
	if (IO != NULL)
		delete IO;
}

void Save1730::Add(DWORD _in, DWORD _out)
{
	if(IO==NULL)
		return;
	if(count>=size)
		return;
	IO[count].in=(WORD)_in;
	IO[count].out=(WORD)_out;
	count++;
}

void Save1730::Save(void)
{
	if(IO==NULL)
		return;
	if(count==0)
		return;
	FILE *file=fopen(fname.c_str(), "ab");
	if(file==NULL)
		return;
	fwrite(IO,sizeof(IOtag),count,file);
	fclose(file);
	count=0;
}
