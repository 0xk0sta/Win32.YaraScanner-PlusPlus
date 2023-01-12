#include "Agent.h"

Agent::Agent(SimpleYara *yara) :  yara(yara) {}

Agent::~Agent() {}

void Agent::ProcScanner() {
	t_udata			udata;
	uint8_t			*time;
	int				bwritten;
	HANDLE			snapshot;
	HANDLE			phndl;
	PROCESSENTRY32	proc_entry;

	bwritten = 0;
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	proc_entry.dwSize = sizeof(PROCESSENTRY32);
	Process32First(snapshot, &proc_entry);
	do {
		phndl = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, proc_entry.th32ProcessID);
		if (!phndl) {
			phndl = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, proc_entry.th32ProcessID);
		}
		if (phndl) {
			udata.pid = proc_entry.th32ProcessID;
			udata.procname = (uint8_t*)proc_entry.szExeFile;
			time = Utils::GetTime();
			//printf("[i]::[%s]::[Info]::[Processing proc]::[%s]::[%u]\n", time, udata.procname, udata.pid);
			this->Callback_ScanProc(phndl, &udata);
			CloseHandle(phndl);
			Sleep(100);
		}
	} while (Process32Next(snapshot, &proc_entry));
	CloseHandle(snapshot);
}

int Agent::AgentCallback(YR_SCAN_CONTEXT * context, int message, void * message_data, void * user_data) {
	YR_RULE			*rule;
	YR_STRING		*str;
	t_udata			*udata;
	uint8_t			*time;

	if (message == CALLBACK_MSG_RULE_MATCHING) {
		rule = (YR_RULE*)message_data;
		udata = (t_udata*)user_data;
		yr_rule_strings_foreach(rule, str) {
			time = Utils::GetTime();
			printf("[*]::[%s]::[%s]::[Process]::[%s]::[PID]::[%lu]::@::[Offet]::[0x%p]::[Rule]::[%s]\n", time, "Hit", udata->procname, udata->pid, udata->base, str->identifier);
			free(time);
		}

	}
	return CALLBACK_CONTINUE;
}


void Agent::ScanRegion(HANDLE hProc, t_region_info *region, t_udata *udata) {
	uint8_t			*buffer;
	SIZE_T			b_read;

	b_read = 0;
	buffer = (uint8_t*)Utils::Alloc(sizeof(uint8_t) * (region->size + 1));
	buffer[region->size] = 0;
	udata->base = region->base;
	if (ReadProcessMemory(hProc, region->base, buffer, region->size, &b_read)
		&& b_read > 0) {
		if (b_read > HUNDREDMB) {
			printf("[·]::Warning::[The region is too big: %lu]\n", b_read);
			return;
		}
		else yr_rules_scan_mem(this->yara->GetRules(), buffer, region->size, SCAN_FLAGS_PROCESS_MEMORY, (this->AgentCallback), udata, 0);
	}
	free(buffer);
}

void Agent::Callback_ScanProc(HANDLE hProc, t_udata *udata) {
	t_region_info* region;
	t_list			*regs;
	t_list			*aux;

	regs = Utils::GetProcessRegions(hProc);
	if (!regs)
		return;
	aux = regs;
	while (aux->next != NULL) {
		region = (t_region_info*)aux->content;
		if (region->protect == PAGE_NOACCESS) {
			aux = aux->next;
			continue;
		}
		ScanRegion(hProc, region, udata);
		aux = aux->next;
	}
	lst_free(regs);
}