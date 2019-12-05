#include "lib.h"

void clear_line(int line)
{
	int p = 1;
	printf("\033[%d;0H", line);
	while (p < dimensions[0] + 2)
	{
		printf(" ");
		p++;
	}
	return;
}


void message(char *string)
{
	printf("\033[%d;0H%s", dimensions[0] + 1, string);
}
