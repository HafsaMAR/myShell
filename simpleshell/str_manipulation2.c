#include "myShell.h"
/**
 * my_strchr - function similar to the library strchr func
 * @str: pointer to the string to search
 * @chr: character to search for
 * Return: Pointer to the first occurrence of chr in str or NULL otherwise
 */
char *my_strchr(char *str, int chr)
{
	while (*str != (char)chr)
		if (!*str++)
			return (0);

	return (str);
}

/**
 * myStrtok_r - function similar to strtok_r function
 * @str: string tokenized
 * @delimiters: string containing the delimiters
 * @save_ptr: pointer to a char pointer that stores the context between calls
 * @check_command: takes value 0, 1 or 2 depending on separators of the input
 * Return: pointer to the token's first character on (success) / NULL otherwise
*/

char *myStrtok_r(char *str, char *delimiters, char **save_ptr,
int *check_command)
{
	char *token;

	if (str == NULL)
	{
		str = *save_ptr;
	}
	if (strstr(str, "||"))
	{
		*check_command = 1;
	}
	else if (strstr(str, "&&"))
	{
		*check_command = 2;
	}
	else
	{
		*check_command = 0;
	}
	while (*str && my_strchr(delimiters, *str))
	{
		str++;
	}
	if (*str == '\0')
	{
		*save_ptr = str;
		return (NULL);
	}
	token = str;

	while (*str && (!my_strchr(delimiters, *str)))
		str++;
	if (*str == '\0')
	{
		*save_ptr = str;
		return (token);
	}
	*str = '\0';
	*save_ptr = str + 1;
	return (token);
}

/**
 * my_strcpy - function for copy string
 * @d: destination of string
 * @s: source of string
 * Return: function copied
 */
char *my_strcpy(char *d, const char *s)
{
	int i = 0;

	if (d == s || s == 0)
		return (d);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

/**
 * my_strncmp - function similar to library strnmcp
 * @s1: first NULL terminated string to compare
 * @s2: second NULL terminated string to compare with
 * @n: The maximum number of characters to compare
 * Return: 0 if equal, negative value if s1 > s2, positive otherwise
*/
int my_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		if (s1[i] == '\0')
			return (0);
	}
	return (0);
}
