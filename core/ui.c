#include <stdio.h>
#include "lib.h"
#include <stdlib.h>
#include <stdbool.h>

/**
 *setui- draw the ui
 *prints the ui the header and the foot
 */
void setui()
{
	int y;
	window_resize();
	printf("\033[0;0H");
	/*      printing header*/
	printf("\033[1;37;46m");

	if (filename == NULL)
	{
		filename = strdup("new_file.myown");
	}
	int cou = printf("File: %s | size: %d x %d", filename, dimensions[0], dimensions[1]);
	while (cou <= dimensions[0])
	{
		printf(" ");
		cou++;
	}
	/*      end of header*/
/*      print bottom        */
	printf("\033[%d;0H", dimensions[1]);
	y = printf("\033[30;47m--line: %d, column: %d-- Easix", line_column[0], line_column[1]);
	while (y <= dimensions[0])
	{
		printf(" ");
		y++;
	}
	printf("\033[0m");
/*      bottom   */

/*              cleaning footer
	printf("\033[%d;0H", dimensions[1] + 1);
	int y = printf(" ");
	while (y < dimensions[0])
	{
		printf(" ");
		y++;
	}

      printing foot
	printf("\033[0m");
	printf("\033[%d;0H", dimensions[1] + 1);
	printf("Text editor in C made by Daniel Rodriguez castillo");
	printf("\033[2;0H");
      foot printed */

}
