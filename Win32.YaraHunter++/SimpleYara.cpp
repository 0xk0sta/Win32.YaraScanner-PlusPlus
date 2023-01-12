#include "SimpleYara.h"
/* make this a utils class method */

uint8_t *get_rsrc() {
	HRSRC	hRsrc;
	HGLOBAL hDat;
	uint8_t* p;

	hRsrc = FindResource(NULL, MAKEINTRESOURCE(DATA), MAKEINTRESOURCE(YAR));
	if (!hRsrc) return NULL;
	hDat = LoadResource(NULL, hRsrc);
	if (!hDat) return NULL;
	p = (uint8_t*)LockResource(hDat);
	return p;
}

bool SimpleYara::add_rule_from_buf(uint8_t *rule_buffer) {
	
	if (yr_compiler_add_string(this->compiler, (const char *)rule_buffer, NULL) != ERROR_SUCCESS
		|| yr_compiler_get_rules(this->compiler, &(this->rules)) != ERROR_SUCCESS) {
		return FALSE;
	}
	
	return TRUE;
}

YR_RULES *SimpleYara::get_rules() { return this->rules; }

SimpleYara::SimpleYara(std::string rule_file) {
	if (yr_initialize() != ERROR_SUCCESS) throw std::runtime_error("[!]\tError: Error initializing yara engine.\n");

	if (yr_compiler_create(&(this->compiler)) != ERROR_SUCCESS) throw std::runtime_error("[!]\tError: Error creating yara compiler!\n");

	if (this->add_rule_from_buf(get_rsrc()) != TRUE) throw std::runtime_error("[!]\tError: Error compiling rules!\n");
}

SimpleYara::SimpleYara(uint8_t *rule_buffer) {
	if (yr_initialize() != ERROR_SUCCESS) throw std::runtime_error("[!]\tError: Error initializing yara engine.\n");

	if (yr_compiler_create(&(this->compiler)) != ERROR_SUCCESS) throw std::runtime_error("[!]\tError: Error creating yara compiler!\n");

	if (this->add_rule_from_buf(rule_buffer) != TRUE) throw std::runtime_error("[!]\tError: Error compiling rules!\n");
}

SimpleYara::~SimpleYara() {
	if (yr_finalize() != ERROR_SUCCESS) {
		std::cout << "[!]::[Error]::[Finalizing yara engine]" << std::endl;
		exit(1);
	}
}