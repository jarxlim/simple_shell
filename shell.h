#ifndef SHELL_H
#define SHELL_H

#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define COMMANDS_NORM   0
#define COMMANDS_OR     1
#define COMMANDS_AND    2
#define COMMANDS_CHAIN  3
#define BUFF_R_SIZE 1024
#define BUFF_W_SIZE 1024
#define BUFFER_FLUSH -1
#define FILE_HIST       ".simple_shell"
#define H_MAXIMUM       4096
#define LOWER_CONVERTER		1
#define UNSIGN_CONVERTER	2
#define USE_GETLINE 0
#define USE_STRTOK 0

extern char **environ;
/**
 * struct liststr - This is the structure fo list
 * @numbers: the number ass the data in the linked list
 * @str: the string as also data
 * @next: the link to the next element of the linkedlist
 */
typedef struct liststr
{
	int numbers;
	char *str;
	struct liststr *next;
} list_t;
/**
 * struct pinfo - the struct that will hold ekk argumennts we will need
 * @arv: getline string generated
 * @argv: arrayof strings from arv
 * @path: Path of the current executed command
 * @argc: number of arguments
 * @count_line: nnmber of errors found
 * @num_err: exit number
 * @count_fline: flag fo input count
 * @file_name: name of te program
 * @envp: list of copy oof envron
 * @hist: history node in the list
 * @_alias: the node in list called alias
 * @environ: the main copy of te environmental vars
 * @change_env: whether environs are changed or not
 * @stats: the status of previous executed commands
 * @buffer_cmd: the poinetr to the commans_tyoe
 * @commands_type: tyop CMD like ||, && and othe gate command
 * @file_reader: file_desc for read line inpput
 * @hist_size: thenumber of the lines counterd from history
 */

typedef struct pinfo
{
	char *arv;
	char **argv;
	char *path;
	int argc;
	unsigned int count_line;
	int num_err;
	int count_fline;
	char *file_name;
	list_t *envp;
	list_t *hist;
	list_t *_alias;
	char **environ;
	int change_env;
	int stats;
	char **buffer_cmd;
	int commands_type;
	int file_reader;
	int hist_size;
} set_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct blt -builtin string and related function
 *@type: the builtin command flag
 *@func: the function for making the operation to the structure
 */
typedef struct blt
{
	char *type;
	int (*func)(set_t *);
} built_t;

/**PROTOTYPES USED*/
int _shell(set_t *, char **);
int builtin_checker(set_t *);
void cmd_finder(set_t *);
void fork_cmd(set_t *);
int  check_cmd(set_t *, char *);
char *chars_dup(char *, int, int);
char *path_finder(set_t *, char *, char *);
int loophsh(char **);
void _prints(char *);
int printchar(char);
int _pchar(char c, int fd);
int _printsf(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *_leet(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _putstr(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memfill(char *, char, unsigned int);
void freef(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int int_checker(set_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _strtoint(char *);
void error_printer(set_t *, char *);
int write_dec(int, int);
char *num_converter(long int, int, int);
void comment_deleter(char *);
int get_exit(set_t *);
int _cmd(set_t *);
int _help(set_t *);
int _history(set_t *);
int get_alias(set_t *);
ssize_t line_check(set_t *);
int _getline(set_t *, char **, size_t *);
void ctrlc_handler(int);
void  _format(set_t *);
void _initiate(set_t *, char **);
void free_info(set_t *, int);
char *_getenv(set_t *, const char *);
int _envron(set_t *);
int my_setenv(set_t *);
int my_unsetenv(set_t *);
int env_lister(set_t *);
char **gt_env(set_t *);
int _unsetenv(set_t *, char *);
int _setenv(set_t *, char *, char *);
char *find_history(set_t *ents);
int print_hist(set_t *ents);
int hist_read(set_t *ents);
int append_list(set_t *ents, char *buffer, int size);
int hist_recount(set_t *ents);
list_t *prepend_node(list_t **, const char *, int);
list_t *append_node(list_t **, const char *, int);
size_t list_printer(const list_t *);
int detach_node(list_t **, unsigned int);
void free_list(list_t **);
size_t list_length(const list_t *);
char **list_string(list_t *);
size_t _lister(const list_t *);
list_t *node_list(list_t *, char *, char);
ssize_t find_node(list_t *, list_t *);
int chain_test(set_t *, char *, size_t *);
void c_checker(set_t *, char *, size_t *, size_t, size_t);
int change_alias(set_t *);
int change_v(set_t *);
int change_str(char **, char *);

#endif
