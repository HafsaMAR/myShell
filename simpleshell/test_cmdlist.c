#include "myShell.h"

#define MAX_COMMANDS 100
#define MAX_ARGUMENTS 100
/*#define MAX_LENGTH 100*/

void tokenizeCommands(char *input, CommandList *commandList)
{
	char *token;
	char *rest = input;
	Command command;
	char *argToken, *argRest;

	while ((token = myStrtok_r(rest, ";|&", &rest, &(commandList->command_check[commandList->count]))))
	{
		command.count = 0;

		argRest = token;
		argToken = myStrtok(argRest, " ");
		while (argToken != NULL)
		{
			if (command.count < MAX_ARGUMENTS)
			{
				command.arguments[command.count++] = strdup(argToken);
			}
			argToken = myStrtok(NULL, " ");
		}
		/* Terminate the arguments array with NULL pointer*/
		command.arguments[command.count] = NULL;

		if (commandList->count < MAX_COMMANDS)
		{
			commandList->commands[commandList->count++] = command;
		}
	}
}

void printCommands(CommandList *commandList)
{
	int i, j;
	printf("Commands:\n");
	for (i = 0; i < commandList->count; i++)
	{
		printf("Command %d:\n", i + 1);
		printf("command-check = %d\n", commandList->command_check[i]);
		for (j = 0; j < commandList->commands[i].count; j++)
		{
			printf("Argument %d: %s\n", j + 1, commandList->commands[i].arguments[j]);
		}
		printf("\n");
	}
}

char *command_path(char *cmd)
{
	struct stat status;	
	char *path = malloc(sizeof(char) * 100);
	if (path == NULL)
	{
		return(NULL);
	}
	/*char *command_path, *command_pathcpy, *pathcpy;
	pathcpy = strdup(path);
	command_path = myStrtok(pathcpy, ":");

	while (command_path)
	{
		command_pathcpy = strdup(command_path);*/

		my_strcpy(path, "/usr/bin/");
 		my_strcat(path, cmd);
		if (stat(path, &status) == 0)
		{
			/*if (pathcpy != NULL)
			{
				free(pathcpy);
				path = NULL;
			}*/
			return (path);
		}
		/*if (command_pathcpy)
		{
			free(command_pathcpy);
			command_pathcpy = NULL;
		}
		command_path = myStrtok(NULL, ":");
	}*/
	return (NULL);
}

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
	cmd = command->arguments[0];
	command_check = command_path(cmd);
	if (stat(cmd, &st) == 0)
	{
		return (cmd);
	}
	else if (command_check != NULL)
	{
		/* TODO : change the first argument of each Command structure to a command_check*/
		/* use ReplaceFirstArg function */
		return (command_check);
	}
	return (NULL);
}

void cmd_check(CommandList *cmdlist)
{
	int i = 0, ret = 0, wstatus;
	Command *cmd;
	char /**argument,*/ *command_path;
	pid_t child_pid;
	for (i = 0; i < cmdlist->count; i++)
	{
		cmd = &cmdlist->commands[i];
		/*argument = cmd->arguments[0];*/
		/* check if cmdlist->command->argument[0] == builtin->name exec builtin function*/
		command_path = is_command(cmdlist, i);
		if (command_path != NULL)
		{
			child_pid = fork();
			if (child_pid == 0)
			{
				ret = execve(command_path, cmd->arguments, environ);
				if (ret == -1)
				{
					perror(cmd->arguments[0]);
				}
				_exit(ret);
			}
			else
			{
				wait(&wstatus);
				/* Get the exit status of the child */
				if (WIFEXITED(wstatus))
					cmdlist->status = WEXITSTATUS(wstatus);
			}
		}
		else
		{
			errputs(cmd->arguments[0]);
			errputs(": command not found\n");
			cmdlist->status = 127;
		}
		if (cmdlist->command_check[i] == 2 && command_path == NULL)
		{
			i++;
		}
		else if (cmdlist->command_check[i] == 1 && command_path != NULL)
		{
			i++;
		}

	}
}

void parse_cmd(char *command_line, CommandList commandlist)
{
	/*Command *command;
	int i = 0;
*/ char *comment_pos = my_strchr(command_line, '#');
	commandlist.count = 0;
	if (comment_pos != NULL)
	{
		*comment_pos = '\0';
	}
	tokenizeCommands(command_line, &commandlist);
	cmd_check(&commandlist);
/*	command = &commandlist.commands[i];
	for (i = 0; i < MAX_COMMANDS; i++)
	{
		if (command->arguments[i])
			free(command->arguments[i]);
		command->count = 0;
	}
	commandlist.count = 0;
*/}

int main(void)
{
	ssize_t get = 0;
	char *command_prompt = NULL;
	CommandList commandlist;
	size_t n = 0;
	commandlist.runarg = 0;
	get_environ(&commandlist);
	while (1)
	{
		if (isatty(STDIN_FILENO) && commandlist.runarg == 0)
		{
			my_puts("Cisfun $ ");
		}
		get = getline(&command_prompt, &n, stdin);
		if (get == -1)
		{
			free(command_prompt);
			command_prompt = NULL;
			exit(-1);
		}
		if (command_prompt[my_strlen(command_prompt) - 1] == '\n')
			command_prompt[my_strlen(command_prompt) - 1] = '\0';
		parse_cmd(command_prompt, commandlist);
	}
	if (command_prompt != NULL)
		free(command_prompt);
	return (0);
}
