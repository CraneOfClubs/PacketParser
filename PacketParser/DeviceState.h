#pragma once
#include <stdint.h>

class DeviceState {

public:
	DeviceState();
	char device_name[64];
	uint64_t system_time;
};
