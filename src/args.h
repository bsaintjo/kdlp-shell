#ifndef ARGS_H
#define ARGS_H

#include <stdlib.h>

#define MAX_CMD_LEN 255
#define MAX_N_ARGS 32

int parse_word(const char *, int);
char **parse_args(const char *);
void free_args(char **);

#endif