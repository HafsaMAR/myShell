#include "myShell.h"
/**
 * my_putchar - function for print char caracter
 * @c: char caracter
 */
void my_putchar(char c)
{
	static char BUFFER[SIZE_BUFFER];
	static size_t i;

	i = 0;
	BUFFER[i++] = c;
	if (i == SIZE_BUFFER)
	{
		write(STDOUT_FILENO, BUFFER, SIZE_BUFFER);
		i = 0;
	}
	/* Flush buffer at end */
	if (i > 0)
	{
		write(STDOUT_FILENO, BUFFER, i);
		i = 0;
	}
}

/**
 * my_puts - function for print string
 * @str: string
 * Return: total number of char written
 */
int my_puts(char *str)
{
	int byte;

	byte = write(STDOUT_FILENO, str, strlen(str));
	if (byte == -1)
	{
		return (EOF);
	}
	return (byte);
}

void errputchar(char c)
{
	static char BUFFER[SIZE_BUFFER];
	static size_t i;

	i = 0;
	BUFFER[i++] = c;
	if (i == SIZE_BUFFER)
	{
		write(STDERR_FILENO, BUFFER, SIZE_BUFFER);
		i = 0;
	}
	/* Flush buffer at end */
	if (i > 0)
	{
		write(STDERR_FILENO, BUFFER, i);
		i = 0;
	}
}

int errputs(char *str)
{
	int byte;

	byte = write(STDERR_FILENO, str, strlen(str));
	if (byte == -1)
	{
		return (EOF);
	}
	return (byte);
}
