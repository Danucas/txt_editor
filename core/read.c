#include "lib.h"

char *read_file(line_t **head)
{
	int fd;
	int rd_stat;
	char *buff = malloc(1024);
	char *out = malloc(100);
	char **lines;
	int pos = 0, copy = 1;
	message("reading ");
	printf("%s", filename);

	fd = open(filename, O_RDONLY);
	rd_stat = read(fd, buff, 1023);
	*head = NULL;
	while ((int) rd_stat > 0)
	{
		buff[rd_stat] = '\0';
		lines = _strtok(buff, "\n");
		if (lines == NULL)
			return (NULL);
		pos = 0;
		while (lines[pos] != NULL)
		{
			out[0] = '\0';
			strcat(out, "rd_pos: ");
			char *j = _tostring(pos);
			strcat(out, j);
			free(j);
			strcat(out, " cop_pos: ");
			j = _tostring(copy);
			strcat(out, j);
			free(j);
			strcat(out, " cont: ");
			strcat(out, lines[pos]);
			strcat(out, "\n");
			console_log(out);
			line_column[0] = (copy);
			new_line(lines[pos], head);
			pos++;
			copy++;
		}
		rd_stat = read(fd, buff, 1023);
	}
	close(fd);
	free(buff);
	free(out);
	(void) head;
	if (lines != NULL)
	{
		free_args(lines);
		return ((*head)->buffer);
	}
	return (NULL);
}
