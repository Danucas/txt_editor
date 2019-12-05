#include "lib.h"

void save_file(line_t **head)
{
	size_t size = 100;
	int readed;
	if (!strncmp(filename, "new_file.myown", 14))
	{
		message("save as: ");
		filename = malloc(100);
		readed = getline(&filename, &size , stdin);
		if (readed > 0)
		{
			filename[readed - 1] = '\0';
			clear_line(dimensions[1] - 1);
		}
	}
	int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	line_t *p = *head;

	(void) size;
	while (p)
	{
		write(fd, p->buffer, strlen(p->buffer));
		if (p->next)
			write(fd, "\n", 1);
		p = p->next;
	}
	close(fd);
	message("File saved as: ");
	printf("%s", filename);
}
