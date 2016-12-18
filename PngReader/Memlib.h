#ifndef MEMLIB_H
#define MEMLIB_H

#include <windows.h>

LPVOID palloc(DWORD size);
BOOL pfree(LPVOID ptr);
VOID pcopy(PVOID dest,CONST VOID *source,DWORD size);
LPVOID pdup(CONST VOID *source,DWORD size);
VOID pmemset(PVOID dest,DWORD size,BYTE value);

#endif MEMLIB_H