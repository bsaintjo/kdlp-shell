#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "args.h"

int parse_word(const char *input, int size)
{
    if (size == 0) {
        return -1;
    }
    for (int i = 0; i < size; i++)
    {
        if (isspace(*input))
        {
            return i + 1;
        }
        else if ((*input) == '\0')
        {
            if (i == 0) {
                return -1;
            } else {
                return i + 1;
            }
        }
        else
        {
            input++;
        }
    }
    return size + 1;
}

char **parse_args(const char *input)
{

    char **args = (char **)malloc(sizeof(char *) * MAX_N_ARGS);

    if (args == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < MAX_N_ARGS; i++)
    {
        args[i] = NULL;
    }

    char **copy = args;

    for (int i = 0; i < MAX_N_ARGS; i++)
    {
        if ((*input == '\0') || !(strcmp(input, "")))
        {
            break;
        }
        int word_idx = parse_word(input, strlen(input));
        if (word_idx == -1)
        {
            break;
        }
        char *arg = (char *)malloc(sizeof(char) * word_idx);
        strlcpy(arg, input, word_idx);
        *copy = arg;
        copy++;
        if (word_idx > (int) strlen(input)) {
            break;
        } else {
            input += word_idx;
        }
    }

    return args;
}

void free_args(char **args) {
    char **copy = args;
    while (*args != NULL) {
        free(*args);
        args++;
    }
    free(copy);
}
