#include "myShell.h"

/**
 * cmd_setenv - function that do the setenv builtin work
 * @shell: pointer to structure containing the shell info
 * @index: index of the command in question stored in the structure
 * Return: void
 */
void cmd_setenv(CommandList *shell, int index)
{
	Command *command = &shell->commands[index];
	int i = 0;
	int check = 0;

	while (shell->env[i])
	{
		if (my_strncmp(command->arguments[1], shell->env[i],
					   my_strlen(command->arguments[1])) == 0)
		{
			my_strcpy(shell->env[i], command->arguments[1]);
			my_strcat(shell->env[i], "=");
			my_strcat(shell->env[i], command->arguments[2]);
			check = 1;
		}
		i++;
	}
	if (check == 0)
	{
		shell->env = my_realloc(shell->env, i + 1, i);
		shell->env[i] = malloc(my_strlen(command->arguments[1]) +
							   my_strlen(command->arguments[2]) + 2);
		my_strcpy(shell->env[i], command->arguments[1]);
		my_strcat(shell->env[i], "=");
		my_strcat(shell->env[i], command->arguments[2]);
		shell->env[i + 1] = NULL;
	}
}

/**
 * cmd_exit - functin that exit the shell program
 * @cmd: structure containing the info of the shell
 * @index: index of the command stored in the structure
 * Return: void
 */
void cmd_exit(CommandList *cmd, int index)
{
	Command *arg = &cmd->commands[index];
	int value;

	if (arg->count == 1)
	{
		cmd->runarg = 1;
	}
	else if (arg->count == 2)
	{
		value = _atoi(arg->arguments[1]);
		if (value > 0 || my_strncmp(arg->arguments[1], "0", 1) == 0)
		{
			cmd->status = value;
		}
		else
		{
			errputs("./hsh: ");
			errputs(_itoa(cmd->order));
			errputs(": exit: Illegal number: ");
			errputs(arg->arguments[1]);
			errputchar('\n');
			cmd->status = 2;
		}
		cmd->runarg = 1;
		return;
	}
}

/**
 * cmd_env - function that do the work of env buitin
 * @cmd: structure storing the info of the shell
 * @index: index of the command stored in the structure
 * Return: void
 */
void cmd_env(CommandList *cmd, int index)
{
	int i = 0;

	(void)index; /* Casting the parameter to void to ignore it */

	while (cmd->env[i])
	{
		printf("%s\n", cmd->env[i]);
		i++;
	}
}

/**
 * cmd_unsetenv - unset the env value stored
 * @cmd: structure containing the info of the shell
 * @index: index of the function executed
 * Return: void
 */
void cmd_unsetenv(CommandList *cmd, int index)
{
	Command *current = &cmd->commands[index];
	int pos, i = 0;

	while (cmd->env[i])
	{
		if (my_strncmp(current->arguments[1], cmd->env[i],
					   my_strlen(current->arguments[1])) == 0)
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

/**
 * cmd_cd - function similar to the cd built-in
 * @cmd: structure containing the info of the shell
 * @index: index of the function executed
 * Return: void
 */
void cmd_cd(CommandList *cmd, int index)
{
	char *path, *oldpwd;
	char buf[SIZE_BUFFER];
	int chdir_status;
	Command command = cmd->commands[index];

	oldpwd = getcwd(buf, SIZE_BUFFER);

	if (command.arguments[1] == NULL)
	{
		path = _getenv("HOME", cmd);
	}
	else if (my_strncmp(command.arguments[1], "-", 1) == 0)
	{
		path = _getenv("OLDPWD", cmd);
		if (path)
		{
			my_puts(path + '\0');
			my_putchar('\n');
		}
		else
		{
			/*errputs("cd: OLDPWD not set");*/
			path = oldpwd;
		}
	}
	chdir_status = chdir(path);
	if (chdir_status == 0)
	{
		update_env("PWD", path, cmd);
		update_env("OLDPWD", oldpwd, cmd);
	}
}
