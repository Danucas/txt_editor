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

int *read_window();
void window_resize();
void setui();



char *_tostring(int number);

void *main_listener();

#endif
