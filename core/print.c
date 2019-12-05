#include "lib.h"

int isvariable = 0;
int iscomment = 0;
int check_keywords(char *buff)
{
	int pos = 0;
	char *blue = "\033[34m";
	char *red = "\x1b[38;5;9m";
	char *yellow = "\x1b[38;5;202m";
	char *green = "\x1b[38;5;40m";
	char *cyan = "\x1b[38;5;92m";
	char *magenta = "\x1b[38;5;200m";
	if (!strncmp(buff, "if ", 3) || !strncmp(buff, "else ", 5))
	{
		printf("%s", magenta);
	}
	else if (!strncmp(buff, "while ", 6) || !strncmp(buff, "for ", 4))
	{
		printf("%s", cyan);
	}
	else if (!strncmp(buff, "int ", 4) || !strncmp(buff, "char ", 5))
	{
	        printf("%s", green);
		isvariable = 1;
	}
	else if (!strncmp(buff, "/*", 2))
	{
	        printf("%s", red);
		iscomment = 1;
	}
	else
	{
		printf("\033[0m");
		if (isvariable)
		{
			printf("%s", yellow);
			isvariable = 0;
		}
		if (iscomment)
		{
			if (!strncmp(buff, "*/", 2))
			{
				iscomment = 0;
			}
			printf("%s", red);
		}
	}

	printf("%s", buff);

	(void) pos;
	(void) blue;
	(void) yellow;
	return (1);
}


void print_line(int line, char *line_arr)
{
	char *keyword = malloc(100);
	int pos = 0;
	int key_c = 0;
	while(line_arr[pos] != '\0')
	{
		if (line_arr[pos] == ' ' || line_arr[pos + 1] == '\0')
		{
			keyword[key_c] = line_arr[pos];
			keyword[key_c + 1] = '\0';
			check_keywords(keyword);
			key_c = 0;
			keyword[0] = '\0';
			pos++;
		}
		else
		{
			keyword[key_c] = line_arr[pos];
			pos++;
			key_c++;
		}
	}
	free(keyword);
	(void) line;
}
