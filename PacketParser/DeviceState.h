#pragma once
#include <stdint.h>
#include "Module.h"

namespace current_state {
	void value_init() {

	}
	char device_name[64];
	uint64_t system_time;
	Module modules[20];
	uint8_t modules_count;
}
