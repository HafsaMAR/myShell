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
/**
 * struct Alias - structure storing the aliases
 * @aliasname: name of the alias
 * @value: the value of the alias
*/
typedef struct Alias
{
	char *aliasname;
	char *value;
} Alias;

typedef struct builtin builtin;

/**
 * struct Command - structure storing the argument of each command line
 * @arguments: array of arguments with max length of MAX_ARGUMENTS
 * @count: number of the arguments stored
*/
typedef struct Command
{
	char *arguments[MAX_ARGUMENTS];
	int count;
} Command;

/**
 * struct CommandList - structure storing all shell info
 * @commands: array of Command structure storing arguments of each commandline
 * @command_check: value to check the logical execution of the commands
 * @status: return value or exit code of the commands
 * @env: copy of environment
 * @runarg: value to check the running or the abortion of the program
 * @count: number of Commands stored
 * @aliases: pointer to Alias atructure
 * @num_aliases: number of aliases stored
 * @builtins: pointer to builtin structure
 * @order: the order of the command passed through stdin
*/
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
	int order;
} CommandList;


/**
 * struct builtin - struct storing the names and pointer to built-in function
 * @name: name of the function similar to the built-in
 * @func: pointer to function similar to built-ins
*/
struct builtin
{
	char *name;
	void (*func)(CommandList *, int);
};

/**********************CMD_PARSE**********************/
int parse_cmd(char *command_line, CommandList *commandlist);
void tokenizeCommands(char *input, CommandList *commandList);
void is_alias(CommandList *cmdlist, int i);
int logical_check(CommandList *cmdlist, int ret, int index);

/***********************CMD_EXEC***********************/
char *special_char_check(char *argtoken, CommandList *Commandlist);
char *command_path(char *cmd);
char *is_command(CommandList *commandlist, int i);
int builtin_cmd(CommandList *cmdlist, int i);
void cmd_check(CommandList *cmdlist);

/***********************BUILTINS***********************/
void cmd_setenv(CommandList *shell, int index);
void cmd_exit(CommandList *cmd, int index);
void cmd_env(CommandList *cmd, int index);
void cmd_unsetenv(CommandList *cmd, int index);
void cmd_cd(CommandList *cmd, int index);

/******************BUILTINS_FUNCTIONS******************/
void get_environ(CommandList *info);
void update_env(char *variable, char *value, CommandList *info);
builtin *update_builtins();

/***********************ALIASES***********************/
void set_alias(CommandList *cmd, char *arg);
void set_new_alias(char *arg, CommandList *cmd);
void print_alias(CommandList *cmd, char *alias_name);
void print_aliasList(CommandList *cmd);
void cmd_alias(CommandList *cmd, int index);

/**********************FUNCTIONS**********************/
char *_getenv(char *variable, CommandList *cmd);
char *_itoa(int num);
void *my_realloc(void *ptr, size_t new_size, size_t old_size);
int _atoi(char *str);

/*******************STR_MANIPULATION*******************/
bool is_delimiter(char c, const char *delim);
char *myStrtok(char *str, const char *delim);
char *my_strcat(char *dest, char *src);
int my_strlen(char *s);
int my_strlen_const(const char *s);

/******************STR_MANIPULATION2******************/
char *my_strchr(char *str, int chr);
char *myStrtok_r(char *str, char *delimiters,
char **save_ptr, int *check_command);
char *my_strcpy(char *d, const char *s);
int my_strncmp(const char *s1, const char *s2, size_t n);
int my_strcmp(char *s1, char *s2);

/******************STR_MANIPULATION3******************/
char *my_strncpy(char *dest, char *src, size_t n);
char *my_strdup(char *str);

/**********************FREESHELL**********************/
void freeCommand(Command *command);
void freeAlias(Alias *alias);
void freeCommandList(CommandList *Commandlist);

/**********************PRINTING**********************/
void my_putchar(char c);
int my_puts(char *str);
void errputchar(char c);
int errputs(char *str);
void errprint(CommandList *cmdlist, int i);
#endif
