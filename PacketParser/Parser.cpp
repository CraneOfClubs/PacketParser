//Coded for embedded devices (STM32 to be exact)
//A lot of techniques are useful to only this case
//No standart c library, a lot ot defines, etc.
#define DEBUG
#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include "Helpers.h"
#ifdef DEBUG

#include <cstring>
#endif // DEBUG


#define BICYCLE_PACKET_SIZE 1024

#define BICYCLE_HEADERS_AMOUNT 20
#define BICYCLE_HEADER_SIZE 64
#define OPERATING_BUFFER BICYCLE_HEADER_SIZE * 2 + 2
#define OPENING "Bicycle="
#define ENDING "End_Bicycle"
#define DELIMITER ';'
#define EQUAL_SETTER '='

namespace bicycle_parser {
	char buffer[BICYCLE_PACKET_SIZE];
	char operating_buffer[BICYCLE_PACKET_SIZE];
	char headers_name[BICYCLE_HEADERS_AMOUNT][BICYCLE_HEADER_SIZE];
	char headers_value[BICYCLE_HEADERS_AMOUNT][BICYCLE_HEADER_SIZE];
	uint16_t cur_header = 0;
	uint16_t header_amount = 0;
	uint16_t cursor_pos = 0;

	void append_char(char character) {
		buffer[cursor_pos++] = character;
	}

	void clear_buffer() {
		cursor_pos = 0;
	}

	void load_to_operating_buffer(char* string_from, uint16_t start_index, uint16_t amount) {
		helpers::my_memset(operating_buffer, '\0', BICYCLE_PACKET_SIZE);
		uint16_t cur_op_buf_index = 0;
		for (uint16_t i = start_index; i < start_index + amount; i++) {
			operating_buffer[cur_op_buf_index] = string_from[i];
			cur_op_buf_index++;
		}
	}

	bool is_bicycle_packet() {
		if (helpers::my_strstr(buffer, (char*)OPENING) != NULL && helpers::my_strstr(buffer, (char*)ENDING) != NULL) {
			return true;
		}
		else return false;
	}

	void split_operating_buffer() {
		//uint16_t start_index = 0;
		uint16_t delim_index = 0;
		for (uint16_t i = 0; i < cursor_pos; i++) {
			if (operating_buffer[i] == EQUAL_SETTER) {
				helpers::my_strncpy(headers_name[cur_header], operating_buffer, i);
				delim_index = i;
			}
			if (operating_buffer[i] == '\0') {
				helpers::my_strncpy(headers_value[cur_header], operating_buffer + delim_index + 1, i - delim_index);
				header_amount++;
				cur_header++;
				return;
			}
		}
	}

	void split_headers() {
		uint16_t start_index = 0;
		header_amount = 0;
		cur_header = 0;
		for (uint16_t i = 0; i < cursor_pos; i++) {
			if (buffer[i] == DELIMITER || buffer[i] == '\0') {
				load_to_operating_buffer(buffer, start_index, i - start_index);
				split_operating_buffer();
				start_index = i + 1;
			}
		}
	}

}

int main() {
	char test[1024] = "Bicycle=v0.1;device_name=hall_controller;type=ack;module_name-1=heater_trigger;module_type-1=bool_trigger;module_state-1=off;module_name-2=light_trigger;module_type-2=variadic_trigger;module_value-2=255;local_time=252624;destination=smserver;End_Bicycle";


	strcpy(test, "Bicycle=v0.1;device_name=hall_controller;type=ack;module_name-1=heater_trigger;module_type-1=bool_trigger;module_state-1=off;module_name-2=light_trigger;module_type-2=variadic_trigger;module_value-2=255;local_time=252624;destination=smserver;End_Bicycle");
	for (int i = 0; i < 1024; i++) {
		if (test[i] == '\0')
			break;
		bicycle_parser::append_char(test[i]);
	}
	auto test2 = bicycle_parser::is_bicycle_packet();
	bicycle_parser::split_headers();

	auto test4 = bicycle_parser::headers_name[0];
	auto test3 = 0;
}