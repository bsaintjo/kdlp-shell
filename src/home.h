#ifndef HOME_H
#define HOME_H

#include <stdlib.h>
#include <string.h>

char *expand_tilde(char *);

char *expand_tilde(char *filepath)
{
    if (filepath[0] == '~')
    {
        char *home = getenv("HOME");
        char *expanded = (char *)malloc(strlen(home) + strlen(filepath) + 1);
        strcpy(home, expanded);
        return home;
    }
    else
    {
        return filepath;
    }
}
#endif