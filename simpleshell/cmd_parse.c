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
