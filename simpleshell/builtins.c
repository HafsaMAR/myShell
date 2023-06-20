#include "myShell.h"

builtin *update_builtins()
{
	static builtin array[] = {
		{"exit", cmd_exit},
		{"env", cmd_env},
		{"setenv", cmd_setenv},
		{"unsetenv", cmd_unsetenv},
		{"cd", cmd_cd},
		{"alias", cmd_alias},
		{NULL, NULL}
	};
	return (array);
}

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
		perror("Error: Allocation Memory\n");
		return;
	}
	for (i = 0; environ[i] != NULL; i++)
	{
		info->env[i] = strdup(environ[i]);
	}
	info->env[i] = NULL;
}

void cmd_setenv(CommandList *shell, int index)
{
	Command *command = &shell->commands[index];
	int i = 0;
	int check = 0;
	while(shell->env[i])
	{
		if (my_strncmp(command->arguments[1], shell->env[i], my_strlen(command->arguments[1])) == 0)
		{
			my_strcpy(shell->env[i], command->arguments[1]);
			my_strcat(shell->env[i], "=");
			my_strcat(shell->env[i], command->arguments[2]);
			check = 1;
		}
		i++;
	}
	if (check = 0)
	{
		shell->env = realloc(shell->env, i + 1);
		shell->env[i] = malloc(my_strlen(command->arguments[1]) + my_strlen(command->arguments[2]) + 2);
		my_strcpy(shell->env[i], command->arguments[1]);
		my_strcat(shell->env[i], "=");
		my_strcat(shell->env[i], command->arguments[2]);
		shell->env[i + 1] = NULL;		
	}
}
void cmd_exit(CommandList *cmd, int index)
{

}
void cmd_env(CommandList *cmd, int index)
{
	int i = 0;
	while(cmd->env[i])
	{
		printf("%s\n", cmd->env[i]);
		i++;
	}
}
void cmd_unsetenv(CommandList *cmd, int index)
{
	Command *current = &cmd->commands[index];
	int pos, i = 0;
	while(cmd->env[i])
	{
		if (my_strncmp(current->arguments[1], cmd->env[i], my_strlen(current->arguments[1])) == 0)
		{
			pos = i;
			break;
		}
		i++;
	}
	for (i = pos; cmd->env[i] != NULL; i++)
	{
		my_strcpy(cmd->env[i], cmd->env[i + 1]);
	}
}
void cmd_cd(CommandList *cmd, int index)
{
}
void cmd_alias(CommandList *cmd, int index)
{

}
