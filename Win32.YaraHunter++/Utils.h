#pragma once
#include <Windows.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "list.h"


typedef struct s_region_info {
	DWORD* base;
	DWORD* allocation;
	DWORD	protect;
	size_t	size;
	DWORD	state;
	DWORD	type;
} t_region_info;

class Utils {
public:
	static int			s_fclose(FILE* f);
	static void			*Alloc(size_t sz);
	static void			PrintHex(uint8_t *buffer, uint32_t sz);
	static const char	*GetProtStr(DWORD prot);
	static t_list		*GetProcessRegions(HANDLE hProcess);
	static uint8_t*		GetTime();
	static uint8_t*		WideToCStr(wchar_t* s);
	static HANDLE		s_OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD pid);
};
