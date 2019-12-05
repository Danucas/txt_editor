#ifndef EDITOR_LIBS
#define EDITOR_LIBS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int *dimensions;
int *line_column;
char *filename;

typedef struct LINE{
	char *buffer;
	struct LINE *next;
}line_t;

void *editor();


int *read_window();
void window_resize();
void setui();



char *_tostring(int number);


void save_file(line_t **doc);
void remove_node(line_t **head, int index);
char *get_node(line_t **head);
line_t *new_line(char *content, line_t **head);

void clear_line(int line);
void message(char *string);
void print_line(int line, char *line_arr);
#endif
