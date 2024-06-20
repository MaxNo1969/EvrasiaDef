#ifndef FileEntryH
#define FileEntryH
#include<System.hpp>
// ---------------------------------------------------------------------------
struct FileEntry
{
	AnsiString name;
	_FILETIME time;

	FileEntry(WIN32_FIND_DATA* _file_data);
	static int __fastcall Comparer(void* e0, void* e1);
	AnsiString ToString(void);
};

#endif
