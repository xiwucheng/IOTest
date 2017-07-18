#ifndef WINIO_H
#define WINIO_H

#include "winio_nt.h"

#ifndef WINIO_DLL
#define WINIO_API extern "C" _declspec(dllexport)
#else
#define WINIO_API 
#endif

WINIO_API BOOL  InitializeWinIo();
WINIO_API void  ShutdownWinIo();
WINIO_API PBYTE  MapPhysToLin(tagPhysStruct &PhysStruct);
WINIO_API BOOL  UnmapPhysicalMemory(tagPhysStruct &PhysStruct);
WINIO_API BOOL  GetPhysLong(PBYTE pbPhysAddr, PDWORD pdwPhysVal);
WINIO_API BOOL  SetPhysLong(PBYTE pbPhysAddr, DWORD dwPhysVal);
WINIO_API BOOL  GetPortVal(WORD wPortAddr, PDWORD pdwPortVal, BYTE bSize);
WINIO_API BOOL  SetPortVal(WORD wPortAddr, DWORD dwPortVal, BYTE bSize);

extern HANDLE hDriver;
extern BOOL IsWinIoInitialized;
extern BOOL g_Is64BitOS;

BOOL InstallWinIoDriver(PWSTR pszWinIoDriverPath, BOOL IsDemandLoaded = FALSE);
BOOL StartWinIoDriver();
BOOL StopWinIoDriver();
BOOL  RemoveWinIoDriver();

#endif
