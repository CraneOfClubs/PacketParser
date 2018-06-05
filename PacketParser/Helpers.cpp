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
}