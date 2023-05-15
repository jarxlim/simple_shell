#ifndef HELL_H
#define SHELL_H
#define _GNU_SOURCE
#include <stdio.h>
#include "lists.h"
/**
 * struct param_struct - structure that will hold the shells provided to the user
 * @argv: arguments list from the main funct
 * @buffer: buffer inputing space
 * @args: array that will hold the arguments
 * @nextCommand: The track to te next command ffrom the user
 * @argsCap: number of urguments the attay can cantain
 * @lineCount: number of lines inputed
 * @tokCount: num of token per line
 * @status: Status of the line/ command
 * @env_head: Environmentalvariabbles linked list
 * @alias_head: singly linked list of aliase
 */
typedef struct param_s
{
        char **argv;
        char *buffer;
        char **args;
        char *nextCommand;
        unsigned int argsCap;
        unsigned int lineCount;
        unsigned int tokCount;
        int status;
        list_t *env_head;
        list_t *alias_head;
} paramas_t;

/**
 * struct op - a buildin function
 * @name: buildin name
 * @func: pointer to buildin function
 */
typedef struct op
{
        char *name;
        void (*func)(param_t *);
} op_t;

int proces_string(paramas_t *);
char *_strdup(char *);
char *_strcpy(char *dest, const char *src)
int _getline(paramas_t *);
int _strcmp(char *, char *);
int _strcmp_n(char *, char *, int n);
char *_strtok(char *str, char *delim, char **savePtr);
void run_command(paramas_t *);
void *_realloc(char **ptr, unsigned int old_size, unsigned int new_size);
void _printenv(paramas_t *);
void sigint_handler(int);
char *_getenv(char *name, paramas_t *params);
void _setenv(paramas_t *params);
void _unsetenv(paramas_t *params);
char *get_file(paramas_t *params);

void (*get_builtin(paramas_t *params))(paramas_t *);

void _myExit(paramas_t *params);

void _cd(paramas_t *params);

void _alias(paramas_t *params);

void set_alias(char *name, paramas_t *params);

void make_alias(char *name, char *val, paramas_t *params);
void print_alias(char *name, paramas_t *params);
void print_all_aliases(paramas_t *params);
void print_list_env(list_t *);
void print_list_alias(list_t *);
void free_params(paramas_t *params);
void write_error(paramas_t *params, char *msg);
void _clear(paramas_t *params);
#endif
