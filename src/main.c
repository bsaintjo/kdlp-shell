#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "args.h"

#define PATH_MAX 4096

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

        int n_args = -1;
        char **args = parse_args(res, &n_args);
        Command to_execute = cmd(args, n_args);
        fprintf(stderr, "Parsed %d arguments\n", n_args);

        switch (to_execute)
        {
        case CHANGE_DIR:
            fprintf(stderr, "Changing directory\n");
            chdir(args[1]);
            break;
        
        case EXIT:
            fprintf(stderr, "Exiting shell\n");
            free_args(args);
            return 0;
            // break;
        
        default:
            printf("Unrecognized command: %s\n", *args);
            break;
        }

        free_args(args);
    }

    return 0;
}
