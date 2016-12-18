#include "Memlib.h"

LPVOID palloc(DWORD size)
{
	return HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,size);
}

BOOL pfree(LPVOID ptr)
{
	return HeapFree(GetProcessHeap(),0,ptr);
}

VOID pcopy(PVOID dest,CONST VOID *source,DWORD size)
{
	CopyMemory(dest,source,size);
}

LPVOID pdup(CONST VOID *source,DWORD size)
{
	LPVOID ptr;
	if ((ptr=palloc(size))==NULL)
		return ptr;
	pcopy(ptr,source,size);
	return ptr;
}

VOID pmemset(PVOID dest,DWORD size,BYTE value)
{
	FillMemory(dest,size,value);
}
