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
    EMPTY,
    CMD_ERROR,
} Command;

Command cmd(char **, int);
char **parse_args(char *, int *);
void free_args(char **);

#endif
