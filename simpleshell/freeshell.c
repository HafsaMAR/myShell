#include "myShell.h"

/**
 * freeCommand - function that frees the Command structure
 * @command: pointer to structure to be freed
 * Return: void
*/
void freeCommand(Command *command)
{
	int i;

	for (i = 0; i < command->count; i++)
	{
		if (command->arguments[i] != NULL)
			free(command->arguments[i]);
	}
	command->count = 0;
}

/**
 * freeAlias - function that free the Alias structure
 * @alias: pointer to Alias structure
 * Return: void
*/
void freeAlias(Alias *alias)
{
	if (alias->aliasname != NULL)
		free(alias->aliasname);
	if (alias->value != NULL)
		free(alias->value);
}

/**
 * freeCommandList - function that frees all the structure
 * @Commandlist: pointer to Commandlist structure to be freed
 * Return: void
*/

void freeCommandList(CommandList *Commandlist)
{
	int i;

	for (i = 0; i < Commandlist->count; i++)
	{
		freeCommand(&Commandlist->commands[i]);
	}
	for (i = 0; Commandlist->env[i] != NULL; i++)
	{
		if (Commandlist->env[i] != NULL)
			free(Commandlist->env[i]);
	}
	free(Commandlist->env);
	for (i = 0; i < Commandlist->num_aliases; i++)
	{
		freeAlias(&Commandlist->aliases[i]);
	}
	free(Commandlist->aliases);
}
