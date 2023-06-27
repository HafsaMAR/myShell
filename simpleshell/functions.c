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
		if (strncmp(cmd->env[i], variable, strlen(variable)) == 0)
		{
			/*firstoccurence = strchr(cmd.env[i], '=');*/
			return (cmd->env[i] + strlen(variable) + 1);
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
