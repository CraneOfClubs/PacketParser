#include "ModulesHandler.h"



ModulesHandler::ModulesHandler()
{
}


ModulesHandler::~ModulesHandler()
{
}


//void ModulesHandler::value_init() {
//
//}

bool ModulesHandler::set_module_state_from_device(char* name, int32_t state) {
	if (!modules_count)
		return false;
	for (uint8_t i = 0; i < modules_count; i++) {
		if (helpers::my_strstr(modules[i].GetName(), name)) {
			if (modules[i].GetType() == INT_SENSOR) {
				modules[i].SetValueFromDevice(state);
			}
		}
	}
	return false;
}

bool ModulesHandler::set_module_state_from_device(char* name, double state) {
	if (!modules_count)
		return false;
	for (uint8_t i = 0; i < modules_count; i++) {
		if (helpers::my_strstr(modules[i].GetName(), name)) {
			if (modules[i].GetType() == FLOATING_SENSOR) {
				modules[i].SetValueFromDevice(state);
			}
		}
	}
	return false;
}

bool ModulesHandler::set_module_state_from_server(char* name, int32_t state) {
	if (!modules_count)
		return false;
	for (uint8_t i = 0; i < modules_count; i++) {
		if (helpers::my_strstr(modules[i].GetName(), name)) {
			if (modules[i].GetType() == INT_SENSOR) {
				modules[i].SetValueFromServer(state);
			}
		}
	}
	return false;
}

bool ModulesHandler::set_module_state_from_server(char* name, double state) {
	if (!modules_count)
		return false;
	for (uint8_t i = 0; i < modules_count; i++) {
		if (helpers::my_strstr(modules[i].GetName(), name)) {
			if (modules[i].GetType() == FLOATING_SENSOR) {
				modules[i].SetValueFromServer(state);
			}
		}
	}
	return false;
}

bool ModulesHandler::add_module(Module module_to_add) {
	modules[modules_count++] = module_to_add;
	return true;
}
