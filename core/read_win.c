#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <pthread.h>

int *read_window(void)
{
        FILE *wfile = popen("tput cols", "r");
        FILE *hfile = popen("tput lines", "r");
        char wid[4];
        char hei[4];
        int width, height;
	int *dim = malloc(sizeof(int) * 2);

        fgets(wid, 4, wfile);
        fgets(hei, 4, hfile);
        pclose(wfile);
        pclose(hfile);
        width = atoi(wid);
        height = atoi(hei);
        if (dim == NULL)
          {
            printf("\033[32mError allocating space for dimensions\033[30m");
            return(NULL);
          }
        *dim = width - 1;
        *(dim + 1) = height - 1;
	return (dim);
}
