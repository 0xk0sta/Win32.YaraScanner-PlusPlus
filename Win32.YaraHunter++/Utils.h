#pragma once
#include <Windows.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "list.h"
#include "resource.h"


typedef struct s_region_info {
	DWORD* base;
	DWORD* allocation;
	DWORD	protect;
	size_t	size;
	DWORD	state;
	DWORD	type;
} t_region_info;

namespace Utils {

	uint8_t		*GetResource();
	int			s_fclose(FILE* f);
	void		*Alloc(size_t sz);
	void		PrintHex(uint8_t *buffer, uint32_t sz);
	const char	*GetProtStr(DWORD prot);
	t_list		*GetProcessRegions(HANDLE hProcess);
	uint8_t*	GetTime();
	uint8_t*	WideToCStr(wchar_t* s);
	HANDLE		s_OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD pid);
};
