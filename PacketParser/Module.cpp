#include "Module.h"



Module::Module()
{
}

Module::Module(char name[64], uint8_t id, ModuleType type)
{
	helpers::my_strncpy(_name, name, 64);
	_id = id;
	_type = type;
}


Module::~Module()
{
}

bool Module::SetValueFromDevice(int32_t _value)
{
	if (_type == INT_SENSOR) {
		_int_value = _value;
		_time_of_change = current_state::system_time;
		_need_validation = true;

		return true;
	}
	return false;
}

bool Module::SetValueFromDevice(double _value)
{
	if (_type == FLOATING_SENSOR) {
		_double_value = _value;
		_time_of_change = current_state::system_time;
		_need_validation = true;
		return true;
	}
	return false;
}

bool Module::SetValueFromServer(int32_t _value)
{
	if (_type == INT_TRIGGER) {
		_int_value = _value;
		_time_of_change = current_state::system_time;
		_need_validation = true;
		return true;
	}
	return false;
}

bool Module::SetValueFromServer(double _value)
{
	if (_type == FLOATING_TRIGGER) {
		_double_value = _value;
		_time_of_change = current_state::system_time;
		_need_validation = true;
		return true;
	}
	return false;
}

double Module::GetDoubleValue()
{
	return _double_value;
}

int32_t Module::GetIntValue()
{
	return _int_value;
}
