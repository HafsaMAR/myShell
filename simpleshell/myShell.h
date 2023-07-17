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

typedef struct Alias
{
	char *aliasname;
	char *value;
} Alias;

typedef struct builtin builtin;

typedef struct Command
{
	char *arguments[MAX_ARGUMENTS];
	int count;
} Command;

typedef struct CommandList
{
	Command commands[MAX_COMMANDS];
	int command_check[MAX_COMMANDS];
	int status;
	char **env;
	int runarg;
	int count;
	Alias *aliases;
	int num_aliases;
	builtin *builtins;
} CommandList;

struct builtin
{
	char *name;
	void (*func)(CommandList *, int);
};

/* print function */
void my_putchar(char);
int my_puts(char *);
int errputs(char *str);
void errputchar(char c);

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
char *_itoa(int num);

/* test_cmdlist*/
char *command_path(char *cmd);
char *is_command(CommandList *commandlist, int i);
int parse_cmd(char *command_line, CommandList commandlist);
/* builtins */
void get_environ(CommandList *info);
void cmd_setenv(CommandList *shell, int index);
void cmd_env(CommandList *cmd, int index);
void cmd_exit(CommandList *cmd, int index);
void cmd_unsetenv(CommandList *cmd, int index);
void update_env(char *variable, char *value, CommandList *info);
void cmd_cd(CommandList *cmd, int index);
void print_alias(CommandList *cmd, char *alias_name);
void print_aliasList(CommandList *cmd);
void cmd_alias(CommandList *cmd, int index);
builtin *update_builtins();
/* freeshell */
void freeCommand(Command *command);
void freeAlias(Alias *alias);
void freeCommandList(CommandList *Commandlist);
#endif
