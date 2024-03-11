#ifndef ARGS_H
#define ARGS_H

#include <stdlib.h>

#define MAX_CMD_LEN 255
#define MAX_N_ARGS 32
typedef enum
{
    EXIT,
    CHANGE_DIR,
    EXECUTE,
    CMD_ERROR,
} Command;

Command cmd(char **, int);
int parse_word(const char *, int);
char **parse_args(const char *);
int parse_args2(const char *, char **);
char **parse_args3(const char *, int *);
void free_args(char **);

#endif
