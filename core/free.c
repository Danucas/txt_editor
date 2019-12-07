#include "lib.h"
/**
 *free_args - free arguments list
 *@args: the args to free
 */
void free_args(char **args)
{
	int counter = 0;

	if (args != NULL)
	{
		while (args[counter] != NULL)
		{
			if (string_cmp("(nil)", args[counter]) != 5)
			{
				free(args[counter]);
			}
			counter++;
		}
		free(args);
	}
}

void free_linked(line_t **list)
{
	line_t *l = *list, *prev = *list;
	while (l != NULL)
	{
		l = l->next;
		free(prev->buffer);
		free(prev);
		prev = l;
	}
}
/**
 *free_two - free arguments list
 *@one: the args to free
 *@two: the args to free
 */
void free_two(char *one, char *two)
{
	free(one);
	free(two);
}
