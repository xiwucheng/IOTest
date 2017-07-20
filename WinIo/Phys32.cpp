// ---------------------------------------------------- //
//                      WinIo v3.0                      //
//				 Direct Hardware Access Under Windows	//
//           Copyright 1998-2010 Yariv Kaplan           //
//               http://www.internals.com               //
// ---------------------------------------------------- //

#include <windows.h>
#include <winioctl.h>
#include "phys32.h"
#include "winio_nt.h"
#include "winio.h"


PBYTE MapPhysToLin(tagPhysStruct &PhysStruct)
{
	PBYTE pbLinAddr = NULL;
	DWORD dwBytesReturned;

	if (!IsWinIoInitialized)
		return FALSE;

	if (!DeviceIoControl(hDriver, IOCTL_WINIO_MAPPHYSTOLIN, &PhysStruct,
		sizeof(tagPhysStruct), &PhysStruct, sizeof(tagPhysStruct),
		&dwBytesReturned, NULL))
	{
		return NULL;
	}

	return (PBYTE)PhysStruct.pvPhysMemLin;
}


BOOL UnmapPhysicalMemory(tagPhysStruct &PhysStruct)
{
	DWORD dwBytesReturned;

	if (!IsWinIoInitialized)
	{
		return FALSE;
	}

	if (!DeviceIoControl(hDriver, IOCTL_WINIO_UNMAPPHYSADDR, &PhysStruct,
		sizeof(tagPhysStruct), NULL, 0, &dwBytesReturned, NULL))
	{
		return FALSE;
	}

	return TRUE;
}

// Support functions

BOOL GetPhysLong(PBYTE pbPhysAddr, PDWORD pdwPhysVal)
{
	PDWORD pdwLinAddr;
	tagPhysStruct PhysStruct;
	BOOL bAccessible = FALSE;

	if (!IsWinIoInitialized)
		return FALSE;

	if (g_Is64BitOS)
	{
		PhysStruct.pvPhysAddress = (DWORD64)*(DWORD*)pbPhysAddr;
	}
	else
	{
		// Avoid sign extension issues
		PhysStruct.pvPhysAddress = (DWORD64)*(DWORD*)pbPhysAddr;
	}

	PhysStruct.dwPhysMemSizeInBytes = 4;

	pdwLinAddr = (PDWORD)MapPhysToLin(PhysStruct);

	if (pdwLinAddr == NULL)
		return FALSE;
	bAccessible = !IsBadReadPtr(pdwLinAddr,4);

	if (bAccessible)
	{
		*pdwPhysVal = *pdwLinAddr;
	}

	UnmapPhysicalMemory(PhysStruct);

	return bAccessible;
}


BOOL SetPhysLong(PBYTE pbPhysAddr, DWORD dwPhysVal)
{
	PDWORD pdwLinAddr;
	tagPhysStruct PhysStruct;
	BOOL bAccessible = FALSE;

	if (!IsWinIoInitialized)
		return FALSE;

	// Avoid sign extension issues
	PhysStruct.pvPhysAddress = (DWORD64)*(DWORD*)pbPhysAddr;

	PhysStruct.dwPhysMemSizeInBytes = 4;

	pdwLinAddr = (PDWORD)MapPhysToLin(PhysStruct);

	if (pdwLinAddr == NULL)
		return FALSE;

	bAccessible = !IsBadWritePtr(pdwLinAddr,4);
	if (bAccessible)
	{
		*pdwLinAddr = dwPhysVal;
	}

	UnmapPhysicalMemory(PhysStruct);

	return bAccessible;
}
