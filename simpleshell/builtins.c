#include "myShell.h"

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
		info->env[i] = strdup(environ[i]);
	}
	info->env[i] = NULL;
}

void cmd_setenv(CommandList *shell, int index)
{
	Command *command = &shell->commands[index];
	int i = 0;
	int check = 0;
	while (shell->env[i])
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
	if (check == 0)
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
	Command *arg = &cmd->commands[index];
	if (arg->count == 1)
	{
		cmd->status = 0;
		cmd->runarg = 1;
	}
	else if (arg->count == 2 && arg->arguments[1] != NULL)
	{
		cmd->status = atoi(arg->arguments[1]);
		cmd->runarg = 1;
	}
	else
	{
		perror("Usage: exit status\n");
	}
}
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
void cmd_unsetenv(CommandList *cmd, int index)
{
	Command *current = &cmd->commands[index];
	int pos, i = 0;
	while (cmd->env[i])
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
		}
		else
		{
			errputs("cd: OLDPWD not set");
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
				temp = realloc(alias[i].value, valuelen + 1);
				if (temp != NULL)
				{
					alias[i].value = temp;
				}
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
			strncpy(alias[i].value, equalsign + 1, valuelen);
			alias[i].value[valuelen] = '\0';
			check = 1;
			break;
		}
	}
	if (check == 0)
	{
		cmd->num_aliases += 1;
		alias = realloc(alias, cmd->num_aliases * sizeof(Alias));
		if (alias == NULL)
		{
			perror("Memory allocation failed.");
			return;
		}
		alias[cmd->num_aliases - 1].aliasname = malloc(aliaslen + 1);
		alias[cmd->num_aliases - 1].value = malloc(valuelen + 1);
		if (alias[cmd->num_aliases - 1].aliasname == NULL || alias[cmd->num_aliases - 1].value == NULL)
		{
			perror("Memory allocation failed.");
			return;
		}

		strncpy(alias[cmd->num_aliases - 1].aliasname, arg, aliaslen);
		strncpy(alias[cmd->num_aliases - 1].value, equalsign + 1, valuelen);
		alias[cmd->num_aliases - 1].aliasname[aliaslen] = '\0';
		alias[cmd->num_aliases - 1].value[valuelen] = '\0';

		cmd->aliases = alias;
	}
}

/* TODO: Define a function to free the memory allocated for the aliases.*/

void print_alias(CommandList *cmd, char *alias_name)
{
	Alias alias;
	int i = 0;
	for (; i < cmd->num_aliases; i++)
	{
		alias = cmd->aliases[i];
		if (strcmp(alias.aliasname, alias_name) == 0)
		{
			my_puts("alias ");
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
