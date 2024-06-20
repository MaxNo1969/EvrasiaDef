// ---------------------------------------------------------------------------
#ifndef uFunctionsH
#define uFunctionsH
#include <Forms.hpp>
#include <stdio.h>
// ---------------------------------------------------------------------------
int ModuleInt(AnsiString _module);
AnsiString IntModule(int _module);
int DefTypeInt(AnsiString _module,AnsiString _DefType);
AnsiString IntDefType(int _module,int _DefType);
void FATAL(AnsiString _msg);
void Fread(void* _buf, int _size, int _n, FILE* _df);
AnsiString LastErrorMsg();
#endif

