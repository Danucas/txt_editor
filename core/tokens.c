#include "lib.h"


line_t *add_node(char *s, line_t **head);

/**
 *clean_up - clean the input line by spaces
 *@line: line to be cleaned
 *Return: the cleaned line
 */

char *clean_up(char **line)
{
	char *l = *line;
	int pos = 0, cl_pos = 0;
	char *cleaned = malloc(sizeof(char) * 1024);

	if (cleaned == NULL)
		printf("Cleaned is NULL\n");
	while (l[pos] != '\0')
	{

		if (l[pos] != ' ')
		{
			cleaned[cl_pos] = l[pos];
			cl_pos++;
		}
		else if (cl_pos > 0 && l[pos] == ' ')
		{
			if (cleaned[cl_pos - 1] != ' ' && cleaned[cl_pos - 1] != '\n')
			{
				if (l[pos + 1] != ' ' && l[pos + 1] != '\n' && l[pos + 1] != '\0')
				{
					cleaned[cl_pos] = l[pos];
					cl_pos++;
				}
			}
		}
		pos++;
	}
	cleaned[cl_pos] = '\0';
	free(*line);
	*line = cleaned;
	return (*line);
}
/**
 *check_token - check if the char is equal to any of the tokens
 *@line: line to break
 *@token: delimitator
 *Return: 0 if it not exists
 */
int check_token(char *line, char *token)
{
	int pos = 0;

	while (token[pos] != '\0')
	{
		if (*line == token[pos])
			return (1);
		pos++;
	}
	return (0);
}
/**
 *_get_list_len - Separate a line and return a list.
 *@line: line to break
 *@token: delimitator
 *Return: Pointer the first item os a list string.
 */
size_t _get_list_len(char *line, char *token)
{
	size_t lc = 0, argc = 0;

	while (line[lc] != '\0')
	{
		if (check_token(&(line[lc]), token) || line[lc + 1] == '\0')
		{
				argc++;
				if (line[lc + 1] == '\0')
				{
					argc++;
					break;
				}
		}
		lc++;

	}
	return (argc);
}
/**
 *_strtok - Separate a line and return a list.
 *@line: line to break
 *@token: delimitator
 *Return: Pointer to the first item on the string list.
 */
char **_strtok(char *line, char *token)
{
	char *buff = malloc(100);
	size_t cont = 0, lc = 0, argc = 0, ac;
	char **args;
	int end = 0;

	(void) ac;
	if (line == NULL || token == NULL)
	{
		free(buff);
		return (NULL);
	}
	if (line[0] == '\0')
	{
		free(buff);
		return (NULL);
	}
	argc = _get_list_len(line, token);
	ac = argc;
	args = malloc(sizeof(char *) * (argc + 1));
	argc = 0;
	while (line[lc] != '\0')
	{
		if (check_token(&(line[lc]), token) || line[lc + 1] == '\0')
		{
			if (line[lc + 1] == '\0')
			{	buff[cont] = line[lc];
				buff[cont + 1] = '\0';
				end = 1;
			}
			else
			{
				buff[cont] = '\0';
			}
			if (cont == 0)
			{
				buff[0] = '\n';
				buff[1] = '\0';
			}
			if (argc < ac)
				args[argc] = str_dup(buff);
			argc++;
			cont = 0;
			if (end == 1)
				break;
		}
		else
		{
			buff[cont] = line[lc];
			cont++;
		}
		lc++;
	}
	free(buff);
	args[argc] = NULL;
	return (args);
}
