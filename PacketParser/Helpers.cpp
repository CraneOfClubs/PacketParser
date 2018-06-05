#include "Helpers.h"


namespace helpers {
	char* my_strstr(char *s2, char *s1)
	{
		int i, j;
		int flag = 0;

		if ((s2 == NULL || s1 == NULL)) return NULL;

		for (i = 0; s2[i] != '\0'; i++)
		{
			if (s2[i] == s1[0])
			{
				for (j = i; ; j++)
				{
					if (s1[j - i] == '\0') { flag = 1; break; }
					if (s2[j] == s1[j - i]) continue;
					else break;
				}
			}
			if (flag == 1) break;
		}

		if (flag) return (s2 + i);
		else return NULL;
	}

	void my_strncpy(char* _dst, const char* _src, size_t _n)
	{
		size_t i = 0;
		while (i++ != _n && (*_dst++ = *_src++));
	}

	void* my_memset(void *s, int c, size_t n)
	{
		unsigned char* p = (unsigned char*)s;
		while (n--)
			*p++ = (unsigned char)c;
		return s;
	}

	double my_stof(char* s) {
		float rez = 0, fact = 1;
		if (*s == '-') {
			s++;
			fact = -1;
		};
		for (int point_seen = 0; *s; s++) {
			if (*s == '.') {
				point_seen = 1;
				continue;
			};
			int d = *s - '0';
			if (d >= 0 && d <= 9) {
				if (point_seen) fact /= 10.0f;
				rez = rez * 10.0f + (float)d;
			};
		};
		return rez * fact;
	};

	int my_atoi(char *str)
	{
		int res = 0;
		for (int i = 0; str[i] != '\0'; ++i)
			res = res * 10 + str[i] - '0';
		return res;
	}

	VAL_TYPE get_type_from_string(char* str) {
		if (my_strstr(str, (char*)"."))
			return DOUBLE;
		if (my_strstr(str, (char*)"true") || my_strstr(str, (char*)"on") || my_strstr(str, (char*)"false") || my_strstr(str, (char*)"off"))
			return BOOL;
		return INT;
	}

	VAL_TYPE parse_value(char* str, int* int_val, double* double_val, bool* bool_val) {
		VAL_TYPE val_res = get_type_from_string(str);
		*int_val = 0;
		*double_val = 0.0;
		*bool_val = false;
		if (val_res == DOUBLE) {
			*double_val = my_stof(str);
		}
		if (val_res == INT) {
			*int_val = my_atoi(str);
		}
		if (val_res == BOOL) {
			if (my_strstr(str, (char*)"true") || my_strstr(str, (char*)"on"))
				*bool_val = true;
			if (my_strstr(str, (char*)"false") || my_strstr(str, (char*)"off"))
				*bool_val = false;
		}
		return val_res;
	}


	size_t my_strlen(const char *str)
	{
		const char *s;

		for (s = str; *s; ++s)
			;
		return (s - str);
	}
}