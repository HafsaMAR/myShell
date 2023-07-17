#include "myShell.h"

#define MAX_COMMANDS 100
#define MAX_ARGUMENTS 100
/*#define MAX_LENGTH 100*/

char *special_char_check(char *argtoken, CommandList *CommandList)
{
	pid_t pid;
	char *env_value, *str;
	if (argtoken[0] == '$')
	{
		if (my_strncmp(argtoken, "$?", 2) == 0)
		{
			str = _itoa(CommandList->status);
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
			env_value = _getenv(argtoken + 1, CommandList);
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
				argToken = special_char_check(argToken, commandList);
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
	char *path = NULL;

	char *command_path, *pathcpy, *command_pathcpy;
	path = getenv("PATH");
	pathcpy = strdup(path);
	command_path = myStrtok(pathcpy, ":");
	command_pathcpy = malloc(my_strlen(pathcpy));
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
	if (stat(cmd, &st) == 0)
	{
		return (cmd);
	}
	else if ((command_check = command_path(cmd)) != NULL)
	{
		/* TODO : change the first argument of each Command structure to a command_check*/
		/* use ReplaceFirstArg function */
		return (command_check);
	}
	return (NULL);
}

int builtin_cmd(CommandList *cmdlist, int i)
{
	int j = 0;
	Command command = cmdlist->commands[i];
	cmdlist->builtins = update_builtins();
	while (cmdlist->builtins[j].name != NULL)
	{
		if (my_strncmp(cmdlist->builtins[j].name, command.arguments[0], my_strlen(command.arguments[0])) == 0)
		{
			cmdlist->builtins[j].func(cmdlist, i);
			break;
		}
		j++;
	}
	return (j);
}

void cmd_check(CommandList *cmdlist)
{
	int i = 0, ret = 0, wstatus, check;
	Command *cmd;
	char /**argument,*/ *command_path;
	pid_t child_pid;
	for (i = 0; i < cmdlist->count; i++)
	{
		cmd = &cmdlist->commands[i];
		check = builtin_cmd(cmdlist, i);
		if (check > 5)
		{
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
						_exit(ret);
					}
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
		}
		if (cmdlist->command_check[i] == 2 && command_path == NULL)
		{
			i++;
		}
		else if (cmdlist->command_check[i] == 1 && command_path != NULL)
		{
			i++;
		}
		/*if (command_path)
		{
			free(command_path);
			command_path = NULL;
		}*/
	}
}

int parse_cmd(char *command_line, CommandList commandlist)
{
	/*Command *command = commandlist.commands[];
	int i = 0;
*/ char *comment_pos;
	commandlist.count = 0;
	if (command_line[0] == '#')
	{
		*command_line = '\0';
	}
	comment_pos = strstr(command_line, " #");
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
	*/
	return (commandlist.runarg);
}

int main(void)
{
	char *command_prompt = NULL;
	CommandList commandlist = {0};
	size_t n = 0;
	ssize_t nread = 0;
	int check = 0;

	get_environ(&commandlist);

	if (isatty(STDIN_FILENO))
		my_puts("Cisfun $ ");

	while ((nread = getline(&command_prompt, &n, stdin)) != -1)
	{

		if (command_prompt[my_strlen(command_prompt) - 1] == '\n')
			command_prompt[my_strlen(command_prompt) - 1] = '\0';
		check = parse_cmd(command_prompt, commandlist);
		if (check == 1)
			break;
		if (isatty(STDIN_FILENO))
			my_puts("Cisfun $ ");
	}
	freeCommandList(&commandlist);
	free(command_prompt);

	return (commandlist.status);
}
