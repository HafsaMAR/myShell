#include "myShell.h"

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
