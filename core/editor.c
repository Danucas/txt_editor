#include <stdio.h>
#include "lib.h"
#include <stdlib.h>
#include <stdbool.h>

/**
* editor - handle pressed keys
*/
void *editor()
{
	char c[2], *width = _tostring(dimensions[1]);
	char *height = _tostring(dimensions[0] - 1);
	char command[4];
	int pos = 0, y = 0, *line = &(line_column[0]);
	int *column = &(line_column[1]), c_i = 0;
	line_t *doc;
	char *line_arr;
	struct termios old, new;
	struct stat *st = malloc(sizeof(struct stat));

	doc = NULL;
	if (filename != NULL)
	{
		if (!stat(filename, st))
		{	line_arr = read_file(&doc);
			if (line_arr != NULL)
				print_doc(&doc);
			else
				line_arr = (new_line(NULL, &doc))->buffer;
		}
		else
		{	line_arr = (new_line(NULL, &doc))->buffer;
		}
	}
	else
	{	line_arr = (new_line(NULL, &doc))->buffer;
	}
	/* Setting terminal in non blocked to read input*/
	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= (~ICANON & ~ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	/* setting null char at the end of the command buffer*/
	command[3] = '\0';
	/* printing position info*/
	printf("\033[%d;0H", dimensions[1]);
	printf("\033[1;30;47m");
	y = printf("--line: %d, column: %d--", *line, *column);
	while (y <= dimensions[0])
	{	printf(" ");
		y++;
	}
	printf("\033[0m");
	/* setting cursor in position*/
	printf("\033[%d;%dH", (*line + 1), *column);
	command[0] = '0';
	command[1] = '0';
	command[2] = '0';
	// loop reading each key pressed by user
	while ((c[0] = getchar()))
	{	tcsetattr(STDIN_FILENO, TCSANOW, &old);
		// When new line enter pressed
		if (c[0] == '\n')
		{	*column = 1;
			*line += 1;
			line_arr = (new_line(NULL, &doc))->buffer;
		}
		printf("\033[u");
		/* SAVE AND EXIT */
		/* handling ctrl+x s pressed to save the file */
		/* ctrl+x y to save the file  and exit */
		/* ctrl+x n to exit without saving */
		if (c[0] == 24)
			command[0] = 24;
		if ((command[0] == 24 && c[0] == 's') || (command[0] == 24 && c[0] == 'y'))
		{	save_file(&doc);
			if (c[0] == 'y')
				break;
			command[0] = '0', command[1] = '0', c[0] = 1;
		}
		if (command[0] == 24 && c[0] == 'n')
		{	break;
		}
		/* adding new printable character to the buffer  */
		if (c[0] > 31 && c[0] < 127 && command[0] != 27 && command[0] != 24)
		{
			if (*column < (int) strlen(line_arr))
			{	int ind = strlen(line_arr);
				line_arr[ind + 1] = '\0';
				while (ind > (*column - 1))
				{	line_arr[ind] = line_arr[ind - 1];
					ind--;
				}
				line_arr[*column - 1] = c[0];
				*column += 1;
			}
			else
			{	line_arr[*column - 1] = c[0];
				line_arr[*column] = '\0';
				*column += 1;
			}
		}
		/* handling backspace key delete character in the cursor previos position*/
		if (c[0] == 127)
		{	printf("\b");
			c_i = *column - 1;
			if (*column > 1)
			{	*column -= 1;
				while (line_arr[c_i] != '\0')
				{	line_arr[c_i - 1] = line_arr[c_i];
					line_arr[c_i] = '\0';
					c_i++;
				}
				line_arr[c_i - 1] = '\0';
			}
			else if (*column == 1 && *line > 1)
			{	int prev_s = strlen(line_arr) + 1;
				remove_node(&doc, *line);
				*line -= 1;
				line_arr = get_node(&doc);
				*column = (strlen(line_arr) - prev_s) + 2;
				printf("\033[%d;%dH", *line, *column);
			}

		}
		/*navigation*/
		/* capturing escape sequence pressed*/
		if (c[0] == 27)
		{	command[0] = 27;
		}
		/* refresh actual line */
		line_arr = get_node(&doc);
		if (command[0] == 27 && c[0] != 27)
		{
			if (pos < 2)
			{	pos++;
				command[pos] = c[0];
			}
			if (pos == 2)
			{	pos = 0;
				/* printing command*/
				message("comm ");
				int s = 0;

				while (command[s] != '\0')
				{	printf(" %d", command[s]);
					s++;
				}
				printf("   ");
				printf("%s", command);
				if (command[1] == 91 && command[2] == 51)
				{	/* supr key pressed */
					tcsetattr(STDIN_FILENO, TCSANOW, &new);
					c[0] = getchar();
					if (c[0] == 126)
					{
						if (*column < (int) strlen(line_arr))
						{	int p = *column;
							while (line_arr[p] != '\0')
							{
								line_arr[p] = line_arr[p + 1];
								p++;
							}
						}
						else if (*column == (int) strlen(line_arr))
						{	line_arr[*column - 1] = '\0';
						}
						else if (*column > (int) strlen(line_arr))
						{	message("add next line");
						}
					}
					tcsetattr(STDIN_FILENO, TCSANOW, &old);
				}
				if (command[1] == 91 && command[2] == 72)
				{	/* home */
					printf(" home");
					*column = 1;
				}
				if (command[1] == 91 && command[2] == 70)
				{	/* end */
					*column = strlen(line_arr) + 1;
					printf(" end");
				}
				if (command[2] == 65)
				{	/* up */
					if (*line > 1)
						*line -= 1;
				}
				else if (command[2] == 66)
				{	/* down */
					*line += 1;
					if (!get_node(&doc))
					{	/* if buffer is null it print*/
						/* end of buffer at the bottom */
						printf("\033[%d;0H", dimensions[1] + 1);
						y = printf("(End of buffer)");
						while (y < dimensions[0])
						{	printf(" ");
							y++;
						}
						*line -= 1;
					}
				}
				if (command[2] == 68)
				{	/* left */
					if (*column > 1)
						*column -= 1;
				}
				else if (command[2] == 67)
				{	/* right */
					if (line_arr[*column - 1] != '\0')
						*column += 1;
				}
				command[0] = '0';
				command[1] = '0';
				command[2] = '0';
				pos = 0;
			}
		}
		line_arr = get_node(&doc);
		/* print edited line*/
		int off_x = dimensions[0];
		int count = strlen(line_arr);

		if (*line < dimensions[1] - 2)
			printf("\033[%d;0H", *line + 1);
		else
			printf("\033[%d;0H", dimensions[1] - 2);
		print_line(*line + 1, line_arr);
		printf("\033[s");
		if (count >= off_x)
			count = count - off_x;
		while (count < off_x)
		{	printf(" ");
			count++;
		}
		printf("\033[u");
		/* print edited line*/
		setui();
		/* move cursor to pos*/
		if (*line < dimensions[1] - 2)
		{
			if (*column > (int) strlen(line_arr))
			{	printf("\033[%d;%uH", *line + 1, (unsigned int) strlen(line_arr) + 1);
				*column = strlen(line_arr) + 1;
			}
			else
				printf("\033[%d;%dH", *line + 1, *column);
		}
		else
		{
			if (*column > (int) strlen(line_arr))
			{	printf("\033[%d;%uH", dimensions[1] - 1, (unsigned int) strlen(line_arr));
				*column = strlen(line_arr);
			}
			else
				printf("\033[%d;%dH", dimensions[1] - 1, *column);
		}
		/*  move cursor   */
		tcsetattr(STDIN_FILENO, TCSANOW, &new);
	}
	printf("\033[s\033[0;0H");
	printf("\033[2J");
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	free(st);
	free_linked(&doc);
	free(width);
	free(height);
	return (NULL);
}
