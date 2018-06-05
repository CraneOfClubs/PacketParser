#pragma once

#define NULL 0

namespace helpers {
	char* my_strstr(char *s2, char *s1);
	void my_strncpy(char* _dst, const char* _src, size_t _n);
	void* my_memset(void *s, int c, size_t n);
	double my_stof(char* s);
	int my_atoi(char *str);
}
