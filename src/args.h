#ifndef ARGS_H
#define ARGS_H

#include <stdlib.h>

#define MAX_CMD_LEN 255
#define MAX_N_ARGS 32

int parse_word(char *, int);
void strcpy_safe(char *, char *, size_t);
char **parse_args(char *);
void free_args(char **);

#endif