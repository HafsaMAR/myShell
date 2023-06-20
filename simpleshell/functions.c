#include "myShell.h"

/**
 * _getenv - function that works similarly to the library function
 * @variable: name of the environment variable
 * Return: the value of the environment variable
 */
void get_env(CommandList *info)
{
	int i = 0;
	while (environ[i] != NULL)
	{
		i++;
	}
	info->env = malloc((i + 1) * sizeof(char *));
	if (info->env == NULL)
	{
		perror("Allocation error");
	}
	for (i = 0; environ[i] != NULL; i++)
	{
		info->env[i] = strdup(environ[i]);
	}
	info->env[i] = NULL;
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
