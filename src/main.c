#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "args.h"

#ifdef __unix__
#include <linux/limits.h>
#endif

#ifdef __APPLE__
#define PATH_MAX 4096
#endif

int run(char *cmd, int size)
{
    if (strncmp(cmd, "exit", size) == 0)
    {
        return 1;
    }
    else if (strncmp(cmd, "hello", size) == 0)
    {
        return 2;
    }
    else
    {
        return -1;
    }
}

int main(void)
{
    char input[1024];

    while (1)
    {
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        printf("%s$ ", cwd);
        char *res = fgets(input, 1024, stdin);
        if (res == NULL)
        {
            break;
        }

        char **args = parse_args(res);

        if (strcmp(*args, ""))
        {
            printf("Unrecognized command: %s\n", *args);
        }
    }

    return 0;
}
