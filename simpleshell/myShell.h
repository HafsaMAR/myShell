#ifndef MYSHELL_H
#define MYSHELL_H
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;
#define SIZE_BUFFER 1024
#define MAX_LENGTH 200
#define MAX_COMMANDS 100
#define MAX_ARGUMENTS 100
typedef struct
{
	char *arguments[MAX_ARGUMENTS];
	int count;
} Command;

typedef struct
{
	Command commands[MAX_COMMANDS];
	int command_check[MAX_COMMANDS];
	int status;
	char **env;
	int count;
} CommandList;

typedef struct builtin
{
	char *name;
	void (*func)(CommandList);
}builtin;


typedef struct shellnode
{
	char **argv;
	int cmd_count;
	int status;
	struct shellnode *next;
} shellnode;

#define SHELLNODE_INIT \
	{                  \
		NULL, 0, 0     \
	}

/* BUFFER */

/* print function */
void my_putchar(char);
int my_puts(char *);
/* commands*/
void parse_cmd(char *command_line);
/* execve */
void fork_cmd(char *commandline, shellnode *head);
int num_token(char *commandline);
char **copyStringToArgv(shellnode *node, int ac);
/*string_manipulation*/
bool is_delimiter(char c, const char *delim);
char *myStrtok(char *str, const char *delim);
char *my_strcpy(char *d, const char *s);
int my_strlen(char *s);
int my_strlen_const(const char *s);
/*string_manipulation2*/
char *my_strchr(char *str, int chr);
/*char *cmd_token(char *str, cmd *current);*/
char *my_strcat(char *dest, char *src);
char *myStrtok_r(char *str, char *delimiters, char **save_ptr, int *check_command);
char *my_strcpy(char *d, const char *s);
int my_strncmp(const char *s1, const char *s2, size_t n);
/*functions*/
char *_getenv(const char *variable);
void replaceFirstArguments(CommandList *commandList, const char *newValue, int index);
/*structure nodes*/
shellnode *createNode(const char *node);
void insertNode(shellnode **head, const char *node);
void freelist(shellnode *head);
void displayPaths(const shellnode *head);
void add_node(shellnode **head, const char *str);
/* structure*/
void replaceDoublePointer(shellnode *node, char *newcommand);
/* test_cmdlist*/
char *command_path(char *command);
char *is_command(CommandList *commandlist, int i);
#endif
