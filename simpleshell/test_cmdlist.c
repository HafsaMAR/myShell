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

char *command_path(char *cmd, CommandList *shell)
{
	struct stat st;
	char *path = _getenv("PATH", shell);
	char *command_path = myStrtok(path, ":");
	char *command_pathcpy;
	while (command_path)
	{
		command_pathcpy = strdup(command_path);
		my_strcat(command_pathcpy, "/");
		my_strcat(command_pathcpy, cmd);
		if (stat(command_pathcpy, &st) == 0)
		{
			return (command_pathcpy);
		}
		command_path = myStrtok(NULL, ":");
	}
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
	command_check = command_path(cmd, commandlist);
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

/*void exec_cmd(CommandList *commandlist, int index)
{
	Command *cmd = &commandlist->commands[index];
	pid_t child_pid;
	int ret, wstatus;
	child_pid = fork();
	if (child_pid == 0)
	{
		ret = execve(cmd->arguments[0], cmd->arguments, environ);
		if (ret == -1)
		{
			perror("Error execution\n");
			_exit(ret);
		}
	}
	else
	{
		wait(&wstatus);
	}
}*/

void cmd_check(CommandList *cmdlist)
{
	int i = 0, ret, wstatus;
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
			perror(cmd->arguments[0]);
			perror(": command not found\n");
			cmdlist->status = 127;
		}
	}
}

void parse_cmd(char *command_line, CommandList commandlist)
{
	char *comment_pos = my_strchr(command_line, '#');
	shellnode *node = malloc(sizeof(shellnode));
	commandlist.count = 0;
	if (node == NULL)
	{
		perror("Error: Memory Allocation");
		return;
	}
	if (comment_pos != NULL)
	{
		*comment_pos = '\0';
	}
	tokenizeCommands(command_line, &commandlist);
	cmd_check(&commandlist);
	printCommands(&commandlist);
}

int main(void)
{
	ssize_t get = 0;
	char *command_prompt = NULL;
	CommandList commandlist;
	size_t n = 0;
	commandlist.runarg = 0;
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
