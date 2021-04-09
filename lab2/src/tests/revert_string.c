#include "revert_string.h"

void RevertString(char *str)
{
	int i = 0;
	char a;

	while (str[i] != '\0')
		i++;
	int j = 0;
	while (j < (i / 2))
	{
		a = str[i - j - 1];
		str[i - j - 1] = str[j];
		str[j] = a;
		j++;
	}
}

