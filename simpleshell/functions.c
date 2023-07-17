#include "myShell.h"

/**
 * _getenv - function that works similarly to the library function
 * @variable: name of the environment variable
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

void replaceFirstArguments(CommandList *commandList, const char *newValue, int index)
{
	Command *command;
	if (commandList == NULL)
		return;
	command = &commandList->commands[index];
	if (command->count > 0)
	{
		my_strcpy(command->arguments[0], newValue);
	}
}

char *_itoa(int num)
{
	int sign = (num < 0) ? -1 : 1;
	int temp, len = 0;
	char *str;

	num *= sign;
	temp = num;
	do
	{
		len++;
		temp /= 10;
	} while (temp > 0);

	if (sign == -1)
	{
		len += 1;
		str = malloc(sizeof(char) * (len + 1));
		if (str == NULL)
		{
			my_puts("Memory allocation failed.\n");
			return NULL;
		}
	}
	else
	{

		str = malloc(sizeof(char) * (len + 1));
		if (str == NULL)
		{
			my_puts("Memory allocation failed.\n");
			return NULL;
		}
	}
	str[len] = '\0';
	while (len > 0)
	{
		len--;
		if (sign == -1 && len == 0)
		{
			str[len] = '-';
		}
		else
		{
			str[len] = num % 10 + '0';
			num /= 10;
		}
	}
	return (str);
}
