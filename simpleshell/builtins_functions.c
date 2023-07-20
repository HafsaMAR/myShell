#include "myShell.h"

/**
 * get_environ - function that gets the env info and
 * store them in the CommandList structure
 * @info: structure containing the info of the shell
 * Return: void
*/
void get_environ(CommandList *info)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		i++;
	}
	info->env = malloc((i + 1) * sizeof(char *));
	if (info->env == NULL)
	{
		perror("Error: Allocation Memory\n");
		return;
	}
	for (i = 0; environ[i] != NULL; i++)
	{
		info->env[i] = my_strdup(environ[i]);
	}
	info->env[i] = NULL;
}

/**
 * update_env - function that update the env info in the CommandList structure
 * @variable: variable to update
 * @value: value of the env variable
 * @info: structure containing the info of the shell
 * Return: void
*/

void update_env(char *variable, char *value, CommandList *info)
{
	int i;

	for (i = 0; info->env[i] != NULL; i++)
	{
		if (my_strncmp(variable, info->env[i], strlen(variable)) == 0)
		{
			my_strcpy(info->env[i], variable);
			my_strcat(info->env[i], "=");
			my_strcat(info->env[i], value);
		}
	}
}

/**
 * update_builtins - function sets an array of the builtins
 * Return: array of builtin
*/

builtin *update_builtins()
{
	static builtin array[] = {
		{"exit", cmd_exit},
		{"env", cmd_env},
		{"setenv", cmd_setenv},
		{"unsetenv", cmd_unsetenv},
		{"cd", cmd_cd},
		{"alias", cmd_alias},
		{NULL, NULL}};
	return (array);
}
