#include "myShell.h"

/**
 * _getenv - function that works similarly to the library function
 * @variable: name of the environment variable
 * @cmd: pointer to CommandList structure
 * Return: the value of the environment variable
 */
char *_getenv(char *variable, CommandList *cmd)
{
	int i;
	/*char *firstoccurence;*/
	for (i = 0; cmd->env[i] != NULL; i++)
	{
		if (strncmp(variable, cmd->env[i], my_strlen(variable)) == 0)
		{
			/*firstoccurence = strchr(cmd.env[i], '=');*/
			return (cmd->env[i] + my_strlen(variable) + 1);
		}
	}
	return (NULL);
}

/**
 * _itoa - function that convert from int to array
 * @num: int num to convert
 * Return: string result
*/
char *_itoa(int num)
{
	int sign = (num < 0) ? -1 : 1;
	int temp, len = 0;
	char *str;

	num *= sign;
	temp = num;
	do {
		len++;
		temp /= 10;
	} while (temp > 0);

	if (sign == -1)
	{
		len += 1;
		str = malloc(sizeof(char) * (len + 1));
		if (str == NULL)
			return (NULL);
	}
	else
	{

		str = malloc(sizeof(char) * (len + 1));
		if (str == NULL)
			return (NULL);
	}
	str[len] = '\0';
	while (len > 0)
	{
		len--;
		if (sign == -1 && len == 0)
			str[len] = '-';
		else
		{
			str[len] = num % 10 + '0';
			num /= 10;
		}
	}
	return (str);
}

/**
 * my_realloc - function similar to library realloc function
 * @ptr: pointer to object
 * @new_size: new size of the object pointed to by ptr
 * @old_size: it old size
 * Return: pointer to the new object which size is reallocated
*/
void *my_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void *new_ptr;
	size_t i, test_size = (old_size < new_size) ? old_size : new_size;
	char *src, *dest;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		return (NULL);
	}
	src = (char *)ptr;
	dest = (char *)new_ptr;
	for (i = 0; i < test_size; i++)
	{
		dest[i] = src[i];
	}
	free(ptr);
	return (new_ptr);
}

/**
 * _atoi - function similar to atoi
 * @str: string to be converted to number
 * Return: number
*/
int _atoi(char *str)
{
	int result = 0;
	bool is_negative = false;

	if (*str == '-')
	{
		is_negative = true;
		str++;
	}
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			result = result * 10 + (*str - '0');
		}
		else
		{
			break;
		}
		str++;
	}
	if (is_negative)
	{
		result *= -1;
	}
	return (result);
}
