#include "lib.h"

int main(int ac, char **av, char **envp)
{
	pthread_t edit;
	(void) ac;
	(void) av;
	(void) envp;
	if (ac > 1)
	{
		filename = strdup(av[1]);
	}
	else
	{
		filename = NULL;
	}

	dimensions = read_window();
	line_column = malloc(sizeof(int) * 2);
	line_column[0] = 1;
	line_column[1] = 1;
	printf("dims: %d, %d\npos: %d %d\n", dimensions[1], dimensions[0],
	       line_column[0], line_column[1]);
/*setting ui*/
	printf("\033[2J");/*clean the window*/
	setui();
	console_log("initializing\n================================\n");


/*initializing key-pressed listener*/
	if (pthread_create(&edit, NULL, editor, NULL))
	{
		perror("Error: ");
	}
	pthread_join(edit, NULL);
/*key listener */
	free(line_column);
	free(filename);
	free(dimensions);
	return (0);
}
