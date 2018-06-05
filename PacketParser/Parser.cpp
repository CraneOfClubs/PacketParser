//Coded for embedded devices (STM32 to be exact)
//A lot of techniques are useful to only this case
//No standart c library, a lot ot defines, etc.
#define DEBUG
#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include "ModulesHandler.h"
#include "Helpers.h"
#include "Module.h"
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

ModulesHandler modules_handler;
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


	void find_modules_in_headers() {
		char str_counter[16];
		char module_name[BICYCLE_HEADER_SIZE];
		char module_type[BICYCLE_HEADER_SIZE];
		char module_value[BICYCLE_HEADER_SIZE];
		helpers::my_memset(str_counter, '\0', 16);
		helpers::my_memset(module_name, '\0', BICYCLE_HEADER_SIZE);
		helpers::my_memset(module_type, '\0', BICYCLE_HEADER_SIZE);
		helpers::my_memset(module_value, '\0', BICYCLE_HEADER_SIZE);
		for (uint8_t i = 0; i < header_amount; i++) {
			if (helpers::my_strstr(headers_name[i], (char*)"module_name")) {
				for (uint8_t j = 0; j < BICYCLE_HEADER_SIZE; j++) {
					if (headers_name[i][j] == '-') {
						helpers::my_memset(str_counter, '\0', 16);
						helpers::my_strncpy(str_counter, headers_name[i] + j, 16);
					}
				}
				helpers::my_strncpy(module_name, headers_value[i], BICYCLE_HEADER_SIZE);
			}
			if (str_counter[0] != '\0') {
				if (helpers::my_strstr(headers_name[i], (char*)"module_type") && helpers::my_strstr(headers_name[i], str_counter)) {
					helpers::my_strncpy(module_type, headers_value[i], BICYCLE_HEADER_SIZE);
				}
				if ((helpers::my_strstr(headers_name[i], (char*)"module_value") || helpers::my_strstr(headers_name[i], (char*)"module_state")) && helpers::my_strstr(headers_name[i], str_counter)) {
					helpers::my_strncpy(module_value, headers_value[i], BICYCLE_HEADER_SIZE);
						bool bool_val;
						int int_val;
						double double_val;
						VAL_TYPE res = helpers::parse_value(module_value, &int_val, &double_val, &bool_val);
						if (res == INT) {
							modules_handler.set_module_state_from_server(module_name, int_val);
						}
						if (res == DOUBLE) {
							modules_handler.set_module_state_from_server(module_name, double_val);
						}
						if (res == BOOL) {
							if (bool_val)
								modules_handler.set_module_state_from_server(module_name, 1);
							else
								modules_handler.set_module_state_from_server(module_name, 0);
						}
				}
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
		find_modules_in_headers();
	}


}


int main() {
	char test[1024] = "Bicycle=v0.1;device_name=hall_controller;type=ack;module_name-1=heater_trigger;module_type-1=bool_trigger;module_state-1=off;module_name-2=light_trigger;module_type-2=variadic_trigger;module_value-2=255;local_time=252624;destination=smserver;End_Bicycle";

	Module test_module((char*)"heater_trigger", 1, BOOL_TRIGGER);
	modules_handler.add_module(test_module);
	Module test_module1((char*)"light_trigger", 1, INT_TRIGGER);
	modules_handler.add_module(test_module1);
	//modules_handler.set_module_state_from_device((char*)"test_module", 10);

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