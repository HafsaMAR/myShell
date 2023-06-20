#include "myShell.h"
/**
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

/*char *cmd_token(char *str, CommandList *current)

{
	static char *buffer;
	char *token;

	if (str != NULL)
	{
		buffer = str;
	}
	else if (buffer == NULL || *buffer == '\0')
	{
		return (NULL);
	}
	while (*buffer != '\0' && my_strchr(";", *buffer) != 0)
	{
		buffer++;
	}
	if (*buffer == '\0')
		return (NULL);
	token = buffer;*/
/* Find the end of the token */
/*while (*buffer != '\0' && my_strchr(";", *buffer) == 0)
{
	if (*buffer == '|')
	{
		*buffer = '\0';
		current->check_cmd = '|';
		break;
	}
	else if (*buffer == '&')
	{
		*buffer = '\0';
		current->check_cmd = '&';
		break;
	}
	else
	{
		buffer++;
	}
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
}*/

/*int skip_operator(char *str, CommandList cmd)
{
	if (*str && my_strchr("|", *str))
	{
		str++;
		if (*str && my_strchr("|", *str))
		{
			str++;
			cmd.command_check = 0;
			return (cmd.command_check);
		}
	}
	else if (*str && my_strchr("&", *str))
	{
		str++;
		if (*str && my_strchr("&", *str))
		{
			str++;
			cmd.command_check = 1;
			return (cmd.command_check);
		}
	}
	return (cmd.command_check);
}*/

char *operatorTokenizer(char *str, char *delimiters, char **save_ptr)
{
	char *token = str;
	while (*str && !my_strchr(delimiters, *str))
		str++;
	/* Check if the end of the string */
	if (*str == '\0')
	{
		*save_ptr = str;
		return (token);
	}
	*str = '\0';
	*save_ptr = str + 1;
	return (token);
}
char *myStrtok_r(char *str, char *delimiters, char **save_ptr, int *check_command)
{
	char *token;
	/*check if input is NULL*/
	if (str == NULL)
	{
		/* Use saved pointer save_ptr*/
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
	/* Skip leading delimiters*/
	while (*str && my_strchr(delimiters, *str))
	{
		str++;
	}
	/* Check if we have reached the end of the string*/

	if (*str == '\0')
	{
		*save_ptr = str;
		return (NULL);
	}

	/* Find the end of the token*/
	token = str;

	while (*str && (!my_strchr(delimiters, *str)))
		str++;
	/* Check if the end of the string */
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
