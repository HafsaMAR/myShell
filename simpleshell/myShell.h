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

typedef struct Alias
{
	char *aliasname;
	char *value; 
} Alias;

typedef struct
{
	Command commands[MAX_COMMANDS];
	int command_check[MAX_COMMANDS];
	int status;
	char **env;
	int runarg;
	int count;
	Alias *aliases;
	int num_aliases;
} CommandList;


typedef struct builtin
{
	char *name;
	void (*func)(CommandList *, int);
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
int errputs(char *str);
void errputchar(char c);
/* commands*/

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
char *StrtokCommand(char *str, char *delimiters, char **save_ptr);
/*string_manipulation2*/
char *my_strchr(char *str, int chr);
/*char *cmd_token(char *str, cmd *current);*/
char *my_strcat(char *dest, char *src);
char *myStrtok_r(char *str, char *delimiters, char **save_ptr, int *check_command);
char *my_strcpy(char *d, const char *s);
int my_strncmp(const char *s1, const char *s2, size_t n);
/*functions*/
char *_getenv(char *variable, CommandList *cmd);
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
char *command_path(char *cmd);
char *is_command(CommandList *commandlist, int i);
void parse_cmd(char *command_line, CommandList commandlist);
/* builtins */
void get_environ(CommandList *info);
void cmd_env(CommandList *cmd, int index);
void cmd_exit(CommandList *cmd, int index);
void cmd_alias(CommandList *cmd, int index);

/* freeshell */
void freeCommand(Command *command);
void freeAlias(Alias *alias);
void freeCommandList(CommandList *Commandlist);
#endif
