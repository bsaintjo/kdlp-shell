#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "args.h"

Command cmd(char **args, int n_args)
{
    if (!strcmp(*args, "exit"))
    {
        if (n_args == 1)
        {
            return EXIT;
        }
        else
        {
            return CMD_ERROR;
        }
    }
    else if (!strcmp(*args, "cd"))
    {
        if (n_args == 2)
        {
            return CHANGE_DIR;
        }
        else
        {
            return CMD_ERROR;
        }
    }
    else if (!strcmp(*args, "")) {
        return EMPTY;
    }
    else if (!strcmp(*args, "exec")) {
        return EXECUTE;
    }
    else
    {
        return EXECUTE;
    }
}

char **parse_args(char *input, int *out)
{

    char *input_copy = strdup(input);
    input_copy[strcspn(input_copy, "\n")] = 0;

    char *token;
    char **args = (char **)malloc(sizeof(char *) * MAX_N_ARGS);
    char **copy = args;
    if (args == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < MAX_N_ARGS; i++)
    {
        args[i] = NULL;
    }

    // TODO: Error for N args > MAX_N_ARGS
    int count = 0;
    while ((token = strsep(&input_copy, " ")) != NULL)
    {
        *copy = strdup(token);
        copy++;
        count++;
    }
    if (out != NULL) {
        *out = count;
    }
    return args;
}

void free_args(char **args)
{
    char **copy = args;
    while (*copy != NULL)
    {
        free(*copy);
        copy++;
    }
    free(args);
}
