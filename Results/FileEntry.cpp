#pragma hdrstop
#include "FileEntry.h"
#pragma package(smart_init)
FileEntry::FileEntry(WIN32_FIND_DATA* _file_data)
{
	name = _file_data->cFileName;
	time = _file_data->ftLastWriteTime;
}

// ---------------------------------------------------------------------------
int __fastcall FileEntry::Comparer(void* _e0, void* _e1)
{
	FileEntry* e0 = (FileEntry*)_e0;
	FileEntry* e1 = (FileEntry*)_e1;
	if (e0->time.dwHighDateTime < e1->time.dwHighDateTime)
		return (-1);
	if (e0->time.dwHighDateTime == e1->time.dwHighDateTime)
	{
		if (e0->time.dwLowDateTime < e1->time.dwLowDateTime)
			return (-1);
		if (e0->time.dwLowDateTime == e1->time.dwLowDateTime)
			return (0);
		return (1);
	}
	return (1);
}

// ---------------------------------------------------------------------------
AnsiString FileEntry::ToString(void)
{
	AnsiString ret = name;
	ret += " H";
	ret += time.dwHighDateTime;
	ret += " L";
	ret += time.dwLowDateTime;
	return (ret);
}

