#pragma once
#include "Module.h"
class ModulesHandler
{
private:
	Module modules[20];
	uint8_t modules_count;
public:
	ModulesHandler();
	~ModulesHandler();
	//bool set_module_state(char * name, int32_t state);
	bool set_module_state_from_device(char * name, int32_t state);
	bool set_module_state_from_device(char * name, double state);
	bool set_module_state_from_server(char * name, int32_t state);
	bool set_module_state_from_server(char * name, double state);
	bool add_module(Module module_to_add);
};

