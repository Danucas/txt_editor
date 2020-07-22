#include "lib.h"
/**
* clear_line - deletes the content of a line and wipe it
* @line: line index on the doc
*/
void clear_line(int line)
{
	int p = 1;

	printf("\033[%d;0H", line);
	while (p < dimensions[0] + 2)
	{
		printf(" ");
		p++;
	}
}
/**
* message - prints to the text editor console at the bottom
* @string: string to print in console
*/
void message(char *string)
{
	printf("\033[%d;0H%s", dimensions[0] + 1, string);
}
