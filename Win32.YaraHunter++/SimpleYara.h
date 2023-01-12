#pragma once
#include <Windows.h>
#include <libloaderapi.h>
#include <iostream>
#include <string>
#include <yara.h>
#include "utils.h"


class SimpleYara
{
public:
	SimpleYara(void);
	SimpleYara(uint8_t *rule_buffer);
	~SimpleYara();
	YR_RULES *GetRules(void);
private:
	bool AddRuleFromBuffer(uint8_t *rule_buffer);
	YR_COMPILER *compiler;
	YR_RULES	*rules;
};

