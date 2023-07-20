#include "myShell.h"

/**
 * set_alias - update or set a new alias
 * @cmd: structure containing the info of the shell
 * @arg: string containing the alias name and value
 * Return: void
*/
void set_alias(CommandList *cmd, char *arg)
{
	Alias *alias = cmd->aliases;
	int i, check = 0;
	char *temp, *equalsign = strchr(arg, '=');
	size_t aliaslen = equalsign - arg;
	size_t valuelen = strlen(equalsign + 1);

	for (i = 0; i < cmd->num_aliases; i++)
	{
		if (strncmp(arg, alias->aliasname, aliaslen) == 0)
		{
			if (strlen(alias[i].value) < valuelen)
			{
				temp = my_realloc(alias[i].value, valuelen + 1, my_strlen(alias[i].value));
				if (temp != NULL)
					alias[i].value = temp;
				else
				{
					perror("Memory allocation failed.");
					return;
				}
			}
			else
			{
				free(alias[i].value);
				alias[i].value = malloc(valuelen + 1);
				if (alias[i].value == NULL)
				{
					perror("Memory allocation failed.");
					return;
				}
			}
			my_strncpy(alias[i].value, equalsign + 1, valuelen);
			alias[i].value[valuelen] = '\0';
			check = 1;
			break;
		}
	}
	if (check == 0)
		set_new_alias(arg, cmd);
}

/**
 * set_new_alias - function that set a new alias
 * @arg: string containing the value and name of the alias
 * @cmd: structure containing the info of a shell
 * Return: void
*/

void set_new_alias(char *arg, CommandList *cmd)
{
	Alias *alias = cmd->aliases;
	char *equalsign = strchr(arg, '=');
	size_t aliaslen = equalsign - arg;
	size_t valuelen = strlen(equalsign + 1);

	cmd->num_aliases += 1;
		alias = my_realloc(alias, cmd->num_aliases * sizeof(Alias),
		(cmd->num_aliases - 1) * sizeof(Alias));
		if (alias == NULL)
		{
			perror("Memory allocation failed.");
			return;
		}
		alias[cmd->num_aliases - 1].aliasname = malloc(aliaslen + 1);
		alias[cmd->num_aliases - 1].value = malloc(valuelen + 1);
		if (alias[cmd->num_aliases - 1].aliasname == NULL ||
		alias[cmd->num_aliases - 1].value == NULL)
		{
			perror("Memory allocation failed.");
			return;
		}

		my_strncpy(alias[cmd->num_aliases - 1].aliasname, arg, aliaslen);
		my_strncpy(alias[cmd->num_aliases - 1].value, equalsign + 1, valuelen);
		alias[cmd->num_aliases - 1].aliasname[aliaslen] = '\0';
		alias[cmd->num_aliases - 1].value[valuelen] = '\0';

		cmd->aliases = alias;
}


/**
 * print_alias - funtion that prints the alias value to stdout
 * @cmd: structure containing the info of the shell
 * @alias_name: name of the alias
 * Return: void
*/

void print_alias(CommandList *cmd, char *alias_name)
{
	Alias alias;
	int i = 0;

	for (; i < cmd->num_aliases; i++)
	{
		alias = cmd->aliases[i];
		if (strcmp(alias.aliasname, alias_name) == 0)
		{
			my_puts(alias.aliasname);
			my_puts("=\'");
			my_puts(alias.value);
			my_puts("\'\n");
			cmd->status = 0;
			return;
		}
	}
	perror("Cisfun: alias: ");
	errputs(alias_name);
	perror(": not found\n");
}

/**
 * print_aliasList - print the list of all the aliases stored
 * @cmd: structure containing the info of the program
 * Return: void
*/
void print_aliasList(CommandList *cmd)
{
	Alias alias;
	int i = 0;

	for (i = 0; i < cmd->num_aliases; i++)
	{
		alias = cmd->aliases[i];
		my_puts(alias.aliasname);
		my_puts("=\'");
		my_puts(alias.value);
		my_putchar('\'');
		my_putchar('\n');
	}
}

/**
 * cmd_alias - function similar to builtin alias
 * @cmd: structure storing all the program info
 * @index: index of the command in the CommandList structure
 * Return: void
*/
void cmd_alias(CommandList *cmd, int index)
{
	Command current_cmd = cmd->commands[index];
	int i = 1;

	if (current_cmd.count == 1)
	{
		print_aliasList(cmd);
	}
	else
	{
		while (i < current_cmd.count)
		{
			if (my_strchr(current_cmd.arguments[i], '=') != NULL)
			{
				set_alias(cmd, current_cmd.arguments[i]);
			}
			else
			{
				print_alias(cmd, current_cmd.arguments[i]);
			}
			i++;
		}
	}
}
