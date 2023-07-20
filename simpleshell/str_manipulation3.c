#include "myShell.h"

/**
 * my_strncpy - copy n first char form src to dest
 * @src: Pointer to the source null-terminated string to be copied from
 * @dest: pointer to null-terminated string in which to be stored
 * @n: max number of char to be copied
 * Return: pointer to dest
*/
char *my_strncpy(char *dest, char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	for (; i < n ; i++)
	{
		dest[i] = '\0';
	}
	return (dest);
}

/**
 * my_strdup - duplicates the string str
 * @str: string to be duplicated
 * Return: pointer to the duplicated string
*/

char *my_strdup(char *str)
{
	size_t len = my_strlen(str);
	char *dup_str;

	if (str == NULL)
	{
		return (NULL);
	}
	dup_str = malloc((len + 1) * sizeof(char));
	if (dup_str == NULL)
	{
		return (NULL);
	}
	my_strcpy(dup_str, str);
	return (dup_str);
}
