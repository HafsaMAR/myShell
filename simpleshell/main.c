#include "myShell.h"

/**
 * main - Entry point
 * Return: exit code of the function executed
*/
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
		commandlist.order += 1;
		if (command_prompt[my_strlen(command_prompt) - 1] == '\n')
			command_prompt[my_strlen(command_prompt) - 1] = '\0';
		check = parse_cmd(command_prompt, &commandlist);
		if (check == 1)
			break;
		if (isatty(STDIN_FILENO))
			my_puts("Cisfun $ ");
	}
	freeCommandList(&commandlist);
	free(command_prompt);
	return (commandlist.status);
}
