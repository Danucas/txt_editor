#include "lib.h"
/**
* remove_node - remove a node from the doc
*@head: the head of the doc
*@index: position in the doc to remove
*/
void remove_node(line_t **head, int index)
{
	line_t *l = *head, *prev = *head;
	int pos = 1;

	while (l != NULL)
	{
		if (pos == index)
		{
			prev->next = l->next;
			prev->buffer = strcat(prev->buffer, l->buffer);
			clear_line(pos + 1);
			free(l->buffer);
			free(l);
			break;
		}
		prev = l;
		l = l->next;
		pos++;
	}
}
/**
* get_node - get a node from the doc
*@head: the head of the doc
*Return: the pointer to the node
*/
char *get_node(line_t **head)
{
	line_t *l = *head;
	int pos = 1;

	while (l != NULL)
	{
		if (pos == line_column[0])
		{
			return (l->buffer);
		}
		l = l->next;
		pos++;
	}
	return (NULL);
}

/**
* new_line - append a new line to the doc
*@head: the head of the doc
*@content: the buffer for the line to add
*Return: the pointer to the line
*/
line_t *new_line(char *content, line_t **head)
{
	line_t *last_list = *head, *new_node = malloc(sizeof(line_t));
	char *n_line = malloc(200);
	int pos = 0;

	if (content == NULL)
	{	n_line[0] = '\0';
	}
	else
	{
		while (content[pos] != '\0')
		{	n_line[pos] = content[pos];
			pos++;
		}
		if (content[0] == '\n')
			n_line[0] = '\0';
		else
			n_line[pos] = '\0';
	}
	new_node->buffer = n_line;
	pos = 1;

	if (last_list == NULL)
	{	new_node->next = NULL;
		*head = new_node;
		return (new_node);
	}
	while (last_list)
	{
		if (pos == line_column[0] - 1)
		{	new_node->next = last_list->next;
			last_list->next = new_node;
			break;
		} else if (last_list->next == NULL)
		{	new_node->next = last_list->next;
			last_list->next = new_node;
		}
		last_list = last_list->next;
		pos++;
	}
	return (new_node);
}
