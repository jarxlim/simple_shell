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

typedef struct liststr
{
	int numbers;
	char *str;
	struct liststr *next;
} list_t;

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
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct blt
{
	char *type;
	int (*func)(info_t *);
} built_t;

int _shell(info_t *, char **);
int builtin_checker(info_t *);
void cmd_finder(info_t *);
void fork_cmd(info_t *);

int  check_cmd(info_t *, char *);
char *chars_dup(char *, int, int);
char *path_finder(info_t *, char *, char *);

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

int int_checker(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

int _strtoint(char *);
void error_printer(info_t *, char *);
int write_dec(int, int);
char *num_converter(long int, int, int);
void comment_deleter(char *);

int get_exit(info_t *);
int _cmd(info_t *);
int _help(info_t *);

int _history(info_t *);
int get_alias(info_t *);

ssize_t line_check(info_t *);
int _getline(info_t *, char **, size_t *);
void ctrlc_handler(int);

void  _format(info_t *);
void _initiate(info_t *, char **);
void free_info(info_t *, int);

char *_getenv(info_t *, const char *);
int _envron(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);
int env_lister(info_t *);

char **gt_env(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *find_history(info_t *ifn);
int print_hist(info_t *ifn);
int hist_read(info_t *ifn);
int append_list(info_t *ifn, char *buffer, int size);
int hist_recount(info_t *ifn);

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

int chain_test(info_t *, char *, size_t *);
void c_checker(info_t *, char *, size_t *, size_t, size_t);
int change_alias(info_t *);
int change_v(info_t *);
int change_str(char **, char *);

#endif
