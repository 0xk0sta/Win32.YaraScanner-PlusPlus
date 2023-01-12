#pragma once
#include "SimpleYara.h"
#include <Windows.h>
#include <winnt.h>
#include <tlhelp32.h>
#include <stringapiset.h>
#include <yara.h>
#include "list.h"
#include "Utils.h"
#define HUNDREDMB 104857600 


class Agent
{
	private:
		typedef struct s_udata {
			uint8_t* procname;
			DWORD* base;
			DWORD	pid;
		} t_udata;
		t_udata		udata;
		SimpleYara	*yara;
	public:
		Agent(SimpleYara *yara);
		~Agent();
		void			ProcScanner(void);
		static int		AgentCallback(YR_SCAN_CONTEXT *context, int message, void *message_data, void *user_data);
		void			ScanRegion(HANDLE hProc, t_region_info *region, t_udata *udata);
		void			Callback_ScanProc(HANDLE hProc, t_udata *udata);
	
};

