#include "myShell.h"

#define MAX_COMMANDS 100
#define MAX_ARGUMENTS 100

/**
 * parse_cmd - checks the comments and call for
 * tokenizing and executing functions
 * @command_line: inputed command prompt
 * @commandlist: structure containing the shell info
 * Return: 1 to exit the program or 0 otherwise
 */

int parse_cmd(char *command_line, CommandList *commandlist)
{
	char *comment_pos;

	commandlist->count = 0;
	if (command_line[0] == '#')
	{
		*command_line = '\0';
	}
	comment_pos = strstr(command_line, " #");
	if (comment_pos != NULL)
	{
		*comment_pos = '\0';
	}
	tokenizeCommands(command_line, commandlist);
	cmd_check(commandlist);
	freeCommand(commandlist->commands);
	return (commandlist->runarg);
}

/**
 * tokenizeCommands - tokenize the commandline and stores the commands
 * and arguments in the Commandlist and command structures
 * @input: input command
 * @commandList: structure containing all the shell info
 * Return: void
 */

void tokenizeCommands(char *input, CommandList *commandList)
{
	char *token;
	char *rest = input;
	Command command;
	char *argToken, *argRest;

	while ((token = myStrtok_r(rest, ";|&", &rest,
							   &(commandList->command_check[commandList->count]))))
	{
		command.count = 0;
		argRest = token;
		argToken = myStrtok(argRest, " ");
		while (argToken != NULL)
		{
			if (command.count < MAX_ARGUMENTS)
			{
				argToken = special_char_check(argToken, commandList);
				command.arguments[command.count++] = my_strdup(argToken);
				if (argToken[0] == '$')
					free(argToken);
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
/**
 * is_alias - checks if the command is predefined as an aliase
 * @cmdlist: structure containing all the info of shell
 * @i: index of the command in the CommandList structure
 * Return: void
 */
void is_alias(CommandList *cmdlist, int i)
{
	int j;
	Alias *alias = cmdlist->aliases;
	Command cmd = cmdlist->commands[i];

	for (j = 0; j < cmdlist->num_aliases; i++)
	{
		if (alias[i].aliasname != NULL && my_strcmp(alias[i].aliasname,
		cmd.arguments[0]) == 0)
		{
			cmd.arguments[0] = my_realloc(cmd.arguments[0],
			my_strlen(alias[i].value) + 1, my_strlen(cmd.arguments[0]));
			my_strcpy(cmd.arguments[0], alias[i].value);
			break;
		}
	}
}

/**
 * logical_check - checks the logical execution of the commands
 * @cmdlist: structure storing info of the shell
 * @ret: status of the prevous executed command
 * @index: the index of the previously executed command
 * Return: the index of the command to be executed
 */

int logical_check(CommandList *cmdlist, int ret, int index)
{
	int j = index;

	if (cmdlist->command_check[j] == 1 && ret == 0)
	{
		while (cmdlist->command_check[j] == 1)
			j++;
	}
	if (cmdlist->command_check[j] == 2 && ret != 0)
	{
		while (cmdlist->command_check[j] == 2)
		{
			j++;
		}
	}
	return (j);
}
