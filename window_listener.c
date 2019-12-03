#include "lib.h"

void window_resize()
{
	int old_width = dimensions[1];
	int old_height = dimensions[0];

	dimensions = read_window();
	if (old_width != dimensions[1])
	{
		printf("\033[2J");
		setui();
	}
	if (old_height != dimensions[0])
	{
		printf("\033[2J");
		setui();
	}
}
