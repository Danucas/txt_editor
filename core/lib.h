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

typedef struct LINE
{	char *buffer;
	struct LINE *next;
} line_t;

void *editor();
int *read_window();
void window_resize(void);
void setui(void);
char **_strtok(char *line, char *token);
char *_tostring(int number);
int string_len(char *s);
int string_cmp(char *s1, char *s2);
char *str_concat(char *s1, char *s2);
void str_cpy(char *from, char *to);
char *str_dup(char *from);
char **_strtok(char *line, char *token);
char *string_rem(char *s1, char *s2);
void free_args(char **args);
void free_linked(line_t **list);
void save_file(line_t **doc);
void remove_node(line_t **head, int index);
char *get_node(line_t **head);
line_t *new_line(char *content, line_t **head);
char *read_file(line_t **head);
void clear_line(int line);
void message(char *string);
void print_line(int line, char *line_arr);
void print_doc(line_t **doc);
void console_log(char *string);
#endif
