#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long hex_to_l(char *s)
{
    long	res;

	res = 0;
	if (*s == '0')
		s++;
	if (*s == 'x')
		s++;
    while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
			res = res * 16 + *s - '0';
		else
		{
			if (*s >= 'a' && *s <= 'f')
				res = res * 16 + *s - 'W';
			else
				res = res * 16 + *s - '7';
		}
        s++;
    }
    return (res);
}

int main(void)
{
	long hihi;
	char *str = "0xff";

	hihi = hex_to_l(str);
	printf("%ld",hihi);
}