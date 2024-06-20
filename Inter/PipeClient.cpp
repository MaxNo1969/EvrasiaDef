#pragma hdrstop
#include "PipeClient.h"
#include "uFunctions.h"
#include<stdio.h>
#pragma package(smart_init)
PipeClient* PipeClient::Instance = NULL;

PipeClient::PipeClient(void)
{
	AnsiString name = "Thickness";
	DWORD openTimeout = 5000;
	DWORD openTimeout1 = 1000;
	AnsiString s = GetConnectionString();
	if(s==NULL)
		s=AnsiString("\\\\.\\pipe\\")+name;

	WideString wname = s;
	DWORD startTick = GetTickCount();
	for (; ;)
	{
		if (WaitNamedPipe(wname.c_bstr(), openTimeout1))
			break;
		if (GetTickCount() - startTick > openTimeout)
		{
			AnsiString a = "Необходимо включить основную программу установки";
			WideString w = a;
			if (Application->MessageBoxW(w.c_bstr(), L"Ошибка", MB_ICONERROR | MB_RETRYCANCEL) == IDRETRY)
				startTick = GetTickCount();
			else
				throw;
		}
		Sleep(openTimeout1);
	}
	hPipe = CreateFile(wname.c_bstr(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
		FATAL(AnsiString("PipeClient::PipeClient: не смогли открыть канал: ") + name + " " + LastErrorMsg());
	cs = new TCriticalSection();
	AnsiString cmd="Write;Defect.Work.Path;";
	cmd+=Application->ExeName;
	AnsiString ret=Command0(cmd);
	if(ret!="Ok")
		FATAL(AnsiString("PipeClient::PipeClient: не смогли записать путь"));
	cmd="Path;Defectoscope;On";
	ret=Command0(cmd);

}

PipeClient::~PipeClient(void)
{
	CloseHandle(hPipe);
	delete cs;
}

int PipeClient::Read(void* _data, int _size)
{
	unsigned long l;
	if (ReadFile(hPipe, _data, _size, &l, NULL) == 0)
	{
		AnsiString a="PipeClient::Read: не смогли прочитать: ";
		a+=LastErrorMsg();
		CloseHandle(hPipe);
		cs->Leave();
		FATAL(a);
	}
	return ((int) l);
}

void PipeClient::Write(void* _data, int _size)
{
	unsigned long l;
	if (WriteFile(hPipe, _data, _size, &l, NULL) == 0)
	{
		AnsiString a="PipeClient::Write: не смогли записать: ";
		a+=LastErrorMsg();
		CloseHandle(hPipe);
		cs->Leave();
		FATAL(a);
	}
	if ((int)l != _size)
	{
		AnsiString a="PipeClient::Write: не смогли записать нужное количество байт";
		a+=LastErrorMsg();
		CloseHandle(hPipe);
		cs->Leave();
		FATAL(a);
	}
}

void PipeClient::Write(AnsiString _msg)
{
	Write(_msg.c_str(), _msg.Length());
}

AnsiString PipeClient::Read(void)
{
	unsigned long l;
	char data[1024];
	int size = Read(data, 1024);
	AnsiString ret;
	for (int i = 0; i < size; i++)
		ret += data[i];
	return (ret);
}

AnsiString PipeClient::Command0(AnsiString _cmd)
{
	AnsiString ret;
	cs->Enter();
	Write(_cmd);
	ret = Read();
	cs->Leave();
	return (ret);
}

AnsiString PipeClient::Command(AnsiString _cmd)
{
	if (Instance == NULL)
		Instance = new PipeClient();
	return (Instance->Command0(_cmd));
}

void PipeClient::Dispose(void)
{
	if (Instance == NULL)
		return;
	delete Instance;
	Instance == NULL;
}

AnsiString PipeClient::GetConnectionString(void)
{
	AnsiString fname = ChangeFileExt(Application->ExeName, ".pip");
	FILE* df = fopen(fname.c_str(), "r");
	if (df == NULL)
		return (NULL);
	char s[256];
	int ret=fscanf(df,"%250s",s);
	fclose(df);
	if(ret<=0)
		return (NULL);
	return(AnsiString(s));
}
