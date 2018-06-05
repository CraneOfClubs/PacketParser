#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include "Helpers.h"
#include "DeviceState.h"

enum ModuleType {
	FLOATING_SENSOR,
	INT_SENSOR,
	FLOATING_TRIGGER,
	INT_TRIGGER,
	BOOL_TRIGGER
};

//Ive heard about inheritance, but there is no RTTI at embedded.
class Module
{
public:
	Module(char name[64], uint8_t id, ModuleType type);
	~Module();
	bool SetValueFromDevice(int32_t _value);
	bool SetValueFromDevice(double _value);
	bool SetValueFromServer(int32_t _value);
	bool SetValueFromServer(double _value);
	double GetDoubleValue();
	int32_t GetIntValue();
	bool _need_validation = false;
private:

	Module();
	uint8_t _id;
	char _name[64];
	int32_t _int_value;
	double _double_value;
	uint64_t _time_of_change;
	ModuleType _type;
};

