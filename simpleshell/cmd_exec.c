#include "myShell.h"

/**
 * special_char_check - function that checks the special character $
 * @argtoken: argument to check
 * @Commandlist: structure that contains all the simple shell info
 * Return: the value controlled by the special char
 */
char *special_char_check(char *argtoken, CommandList *Commandlist)
{
	pid_t pid;
	char *env_value, *str;

	if (argtoken[0] == '$')
	{
		if (my_strncmp(argtoken, "$?", 2) == 0)
		{
			str = _itoa(Commandlist->status);
			argtoken = str;
		}
		else if (my_strncmp(argtoken, "$$", 2) == 0)
		{
			pid = getpid();
			str = _itoa(pid);
			argtoken = str;
		}
		else
		{
			env_value = _getenv(argtoken + 1, Commandlist);
			if (env_value)
			{
				argtoken = env_value;
			}
			else
				argtoken = "";
		}
	}
	return (argtoken);
}

/**
 * command_path - concatenate the name of the executable file to its path
 * @cmd: command in question
 * Return: command path or NULL if not find
 */

char *command_path(char *cmd)
{
	struct stat status;
	char *path = NULL;
	char *command_path, *pathcpy, *command_pathcpy;

	path = getenv("PATH");
	pathcpy = my_strdup(path);
	command_path = myStrtok(pathcpy, ":");
	command_pathcpy = malloc(my_strlen(pathcpy) + my_strlen(cmd) + 2);
	while (command_path)
	{
		my_strcpy(command_pathcpy, command_path);
		my_strcat(command_pathcpy, "/");
		my_strcat(command_pathcpy, cmd);
		if (stat(command_pathcpy, &status) == 0)
		{
			if (pathcpy != NULL)
			{
				free(pathcpy);
			}
			return (command_pathcpy);
		}
		command_path = myStrtok(NULL, ":");
	}
	if (pathcpy)
	{
		free(pathcpy);
	}
	if (command_pathcpy)
		free(command_pathcpy);
	return (NULL);
}

/**
 * is_command - checks the execution of the external commands
 * @commandlist: structure containing the info of the structure
 * @i: the index of the command in question in the structure
 * Return: the command to be executed or NULL if not find
 */

char *is_command(CommandList *commandlist, int i)
{
	Command *command;
	struct stat st;
	char *cmd, *command_check;

	if (commandlist == NULL || commandlist->count == 0)
		return (NULL);
	command = &commandlist->commands[i];
	if (command->count == 0)
		return (NULL);

	is_alias(commandlist, i);
	cmd = my_strdup(command->arguments[0]);
	command_check = command_path(cmd);
	if (stat(cmd, &st) == 0)
	{
		free(command_check);
		return (cmd);
	}
	else if (command_check != NULL)
	{
		free(cmd);
		return (command_check);
	}
	free(cmd);
	if (command_check)
		free(command_check);
	return (NULL);
}

/**
 * builtin_cmd - function that checks if the command is a builtin command
 * @cmdlist: structure containing the info of the shell
 * @i: the index if the command in the CommanList structure
 * Return: the order of the builtin
 */

int builtin_cmd(CommandList *cmdlist, int i)
{
	int j = 0;
	Command command = cmdlist->commands[i];

	cmdlist->builtins = update_builtins();
	while (cmdlist->builtins[j].name != NULL)
	{
		if (my_strncmp(cmdlist->builtins[j].name, command.arguments[0],
					   my_strlen(command.arguments[0])) == 0)
		{
			cmdlist->builtins[j].func(cmdlist, i);
			break;
		}
		j++;
	}
	return (j);
}

/**
 * cmd_check - function that exec the functions
 * @cmdlist: pointer to structure containing the info of the shell
 * Return: void
 */

void cmd_check(CommandList *cmdlist)
{
	int i = 0, ret = 0, wstatus, check;
	Command *cmd;
	char *command_path = NULL;
	pid_t child_pid;

	for (i = 0; i < cmdlist->count; i++)
	{
		cmd = &cmdlist->commands[i];
		check = builtin_cmd(cmdlist, i);
		if (check > 5)
		{
			command_path = is_command(cmdlist, i);
			if (command_path != NULL)
			{
				child_pid = fork();
				if (child_pid == 0)
				{
					ret = execve(command_path, cmd->arguments, environ);
					if (ret == -1)
					{
						free(command_path);
						_exit(ret);
					}
				}
				else
				{
					wait(&wstatus);
					if (WIFEXITED(wstatus))
						cmdlist->status = WEXITSTATUS(wstatus);
				}
			}
			else
			{
				errprint(cmdlist, i);
				cmdlist->status = 127;
			}
		}
		i = logical_check(cmdlist, cmdlist->status, i);
		free(command_path);
	}
}
