#include "lib.h"
/**
 *setui- draw the ui
 */
void setui()
{
	printf("\033[0;0H");
/*      printing header*/
	printf("\033[1;37;40m");

	if (filename == NULL)
	{
		filename = "new_file.myown";
	}
	int cou = printf("File name: %s,width: [%d], height: [%d]", filename, dimensions[0], dimensions[1]);
	while (cou <= dimensions[0])
	{
		printf(" ");
		cou++;
	}
/*      end of header*/

/*      printing bottom*/
	printf("\033[0m");
	printf("\033[%d;0H", dimensions[1] + 1);
	printf("Text editor in C made by Daniel Rodriguez castillo");
	printf("\033[2;0H");
/*      bottom printed */

}

int main(int ac, char **av, char **envp)
{
	pthread_t key_listener;
	(void) ac;
	(void) av;
	(void) envp;
	if (ac > 1)
	{
		filename = av[1];
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


/*initializing key-pressed listener*/
	if (pthread_create(&key_listener, NULL, main_listener, NULL))
	{
		perror("Error: ");
	}
	pthread_join(key_listener, NULL);
/*key listener */
	return (0);
}
