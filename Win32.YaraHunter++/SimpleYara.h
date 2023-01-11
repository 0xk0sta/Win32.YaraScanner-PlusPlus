#pragma once
#include <Windows.h>
#include <libloaderapi.h>
#include <iostream>
#include <string>
#include <yara.h>

#include "resource.h"

class SimpleYara
{
public:
	SimpleYara(std::string rule_file);
	~SimpleYara();
private:
	bool add_rule_from_buf(uint8_t *rule_buffer);
	YR_COMPILER *compiler;
	YR_RULES	*rules;
};

