#include "SimpleYara.h"
/* make this a utils class method */

bool SimpleYara::AddRuleFromBuffer(uint8_t *rule_buffer) {
	
	if (yr_compiler_add_string(this->compiler, (const char *)rule_buffer, NULL) != ERROR_SUCCESS
		|| yr_compiler_get_rules(this->compiler, &(this->rules)) != ERROR_SUCCESS) {
		return FALSE;
	}
	
	return TRUE;
}

YR_RULES *SimpleYara::GetRules() { return this->rules; }

SimpleYara::SimpleYara() {
	if (yr_initialize() != ERROR_SUCCESS) throw std::runtime_error("[!]::Error::[Error initializing yara engine.]");

	if (yr_compiler_create(&(this->compiler)) != ERROR_SUCCESS) throw std::runtime_error("[!]::Error::[Error creating yara compiler!]");

	if (this->AddRuleFromBuffer(Utils::GetResource()) != TRUE) throw std::runtime_error("[!]::Error::[Error compiling rules!]");
}

SimpleYara::SimpleYara(uint8_t *rule_buffer) {
	if (yr_initialize() != ERROR_SUCCESS) throw std::runtime_error("[!]::Error::[Error initializing yara engine.]");

	if (yr_compiler_create(&(this->compiler)) != ERROR_SUCCESS) throw std::runtime_error("[!]::Error::[Error creating yara compiler!]");

	if (this->AddRuleFromBuffer(rule_buffer) != TRUE) throw std::runtime_error("[!]::Error::[Error compiling rules!]");
}

SimpleYara::~SimpleYara() {
	if (yr_finalize() != ERROR_SUCCESS) {
		std::cout << "[!]::[Error]::[Finalizing yara engine]" << std::endl;
		exit(1);
	}
}