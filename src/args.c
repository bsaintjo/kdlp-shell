#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "args.h"

Command cmd(char **args, int n_args)
{
    if (!strcmp(*args, "exit"))
    {
        if (n_args == 0)
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
        if (n_args == 1)
        {
            return CHANGE_DIR;
        }
        else
        {
            return CMD_ERROR;
        }
    }
    else
    {
        return EXECUTE;
    }
}

int parse_word(const char *input, int size)
{
    if (size == 0)
    {
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
            if (i == 0)
            {
                return -1;
            }
            else
            {
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

char **parse_args3(const char *input, int *out)
{
    char *token;
    char *copy = input;
    char **args = (char **)malloc(sizeof(char *) * 32);
    if (args == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < 32; i++)
    {
        args[i] = NULL;
    }

    int count = 0;
    while ((token = strsep(&copy, " ")) != NULL)
    {
        *args = strdup(token);
        count++;
    }
    if (out != NULL) {
        *out = count;
    }
    return args;
}

int parse_args2(const char *input, char **dst)
{
    if (dst == NULL)
    {
        return -1;
    }

    for (int i = 0; i < MAX_N_ARGS; i++)
    {
        dst[i] = NULL;
    }

    int n_args = 0;
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
        if (arg == NULL)
        {
            return -1;
        }

        strlcpy(arg, input, word_idx);
        *dst = arg;
        dst++;
        if (word_idx > (int)strlen(input))
        {
            break;
        }
        else
        {
            input += word_idx;
        }
        n_args += 1;
    }

    return n_args;
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
        if (arg == NULL)
        {
            return NULL;
        }

        strlcpy(arg, input, word_idx);
        *copy = arg;
        copy++;
        if (word_idx > (int)strlen(input))
        {
            break;
        }
        else
        {
            input += word_idx;
        }
    }

    return args;
}

void free_args(char **args)
{
    char **copy = args;
    while (*args != NULL)
    {
        free(*args);
        args++;
    }
    free(copy);
}
