#include "lib.h"
/**
 *str_concat - Adds two different strings.
 *@s1: 1st string.
 *@s2: 2nd string.
 *Return: A pointer to the new string.
 */
char *str_concat(char *s1, char *s2)
{
	int counter = 0, new_count = 0;/*Iterate each string and new string.*/

	while (s1[new_count] != '\0')/*Iterate s1 till NULL.*/
	{
		new_count++;/*Adding s1's info to new string.*/
	}
	while (s2[counter] != '\0')
	{
		s1[new_count] = s2[counter];
		new_count++;
		counter++;
	}
	s1[new_count] = '\0';
	return (s1);
}
/**
 *string_rem - Take n chars and erase it from the string.(Promt).
 *Description - Remove s1 from s2 and return a pointer to the new string.
 *@s1: String path to remove.
 *@s2: String from where s1 it's going to be removed.
 *Return: Pointer to the new string.
 */
char *string_rem(char *s1, char *s2)
{
	int len1 = string_len(s1);
	int len2 = string_len(s2);/*Get the size of the second string.*/
	int counter = 0, new_count = 0;
	(void) len2;
	while (s2[counter] != '\0')
	{
		int st = string_cmp(s1, &(s2[counter]));
/*		printf("stat: %d len1: %d %s", st, len1, &(s2[counter]));*/
		if (st < len1)
		{
/*			printf(" dismatch\n");*/
			s2[new_count] = s2[counter];
			new_count++;
		}
		else if (st == len1)
		{
/*			printf(" match\n");*/
			counter += len1 - 1;
		}
		counter++;
	}
	s2[new_count] = '\0';
	return (s2);

}
/**
 *string_len - Obtain the lenght of the string.
 *@s: String to get lenght.
 *Return: The lenght of the string.
 */
int string_len(char *s)
{
	int count = 0;

	while (s[count] != '\0')
	{
		count++;
	}
	return (count);
}
/**
 *string_cmp - Compare two strings.
 *@s1: String for campare (Path).
 *@s2: String to compare.
 *Return: Number of coincidences.
 */
int string_cmp(char *s1, char *s2)
{
	int count = 0;

	while (s2[count] != '\0')
	{
		if (s1[count] != s2[count])
			return (count);
		count++;
	}
	return (count);
}
/**
 *str_dup - duplicate a string
 *@from: string to duplicate
 *Return: pointer to new string.
 */
char *str_dup(char *from)
{
	int cont = 0;
	int len = string_len(from);
	char *new_str;

	new_str = malloc(sizeof(char) * (len + 1));
	while (from[cont] != '\0')
	{
		new_str[cont] = from[cont];
		cont++;
	}
	new_str[cont] = '\0';
	return (new_str);
}
