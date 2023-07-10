#include "myShell.h"

void freeCommand(Command *command)
{
	int i;
	for (i = 0; i < command->count; i++)
	{
		free(command->arguments[i]);
	}
	command->count = 0;
}

void freeAlias(Alias *alias)
{
	free(alias->aliasname);
	free(alias->value);
}

void freeCommandList(CommandList *Commandlist)
{
	int i;
	for (i = 0; i < Commandlist->count; i++)
	{
		freeCommand(&Commandlist->commands[i]);
	}
	for (i = 0; Commandlist->env[i] != NULL; i++)
	{
		free(Commandlist->env[i]);
	}
	free(Commandlist->env);
	for (i = 0; i < Commandlist->num_aliases; i++)
	{
		freeAlias(&Commandlist->aliases[i]);
	}
	free(Commandlist->aliases);
}
