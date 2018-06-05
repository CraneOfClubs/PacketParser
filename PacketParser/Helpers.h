#pragma once

#define NULL 0

enum VAL_TYPE {
	BOOL,
	INT,
	DOUBLE,
	UNDEFINED
};


namespace helpers {
	char* my_strstr(char *s2, char *s1);
	void my_strncpy(char* _dst, const char* _src, size_t _n);
	void* my_memset(void *s, int c, size_t n);
	double my_stof(char* s);
	int my_atoi(char *str);
	VAL_TYPE get_type_from_string(char* str);
	VAL_TYPE parse_value(char* str, int* int_val, double* double_val, bool* bool_val);
	size_t my_strlen(const char *str);
}
