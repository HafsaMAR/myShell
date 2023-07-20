#include "myShell.h"
/**
 * is_delimiter - checks for the delimiter
 * @c: character to check
 * @delim: string of delimiters
 * Return: true or false
 */
bool is_delimiter(char c, const char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (true);
		delim++;
	}
	return (false);
}
/**
 * myStrtok- equivalent to strtok built-in function
 * @str: string to tokenize
 * @delim: delimiter
 * Return: tokens
 */
char *myStrtok(char *str, const char *delim)
{
	static char *buffer;
	char *token;

	if (str != NULL)
		buffer = str;
	else if (buffer == NULL || *buffer == '\0')
		return (NULL);
	while (*buffer != '\0' && is_delimiter(*buffer, delim))
		buffer++;
	if (*buffer == '\0')
		return (NULL);
	token = buffer; /* Find the end of the token */
	while (*buffer != '\0' && !is_delimiter(*buffer, delim))
	{
		if (*buffer == '"')
		{
			buffer++;
			while (*buffer && *buffer != '"')
			{
				buffer++;
			}
			if (*buffer == '"')
			{
				buffer++;
			}
		}
		else
			buffer++;
	}
	if (*buffer != '\0')
	{
		*buffer++ = '\0';
	}
	else
	{
		buffer = NULL;
	}
	return (token);
}

/**
 * my_strcat - concatenates two strings
 * @dest: input value
 * @src: input value
 * Return: void
 */
char *my_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * my_strlen - returns the length of a string
 * @s: string
 * Return: length
 */
int my_strlen(char *s)
{
	int longt = 0;

	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		longt++;
		s++;
	}
	return (longt);
}
