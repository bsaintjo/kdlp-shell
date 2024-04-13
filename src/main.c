#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
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

        char *bin_path;
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

        case EXECUTE:
            fprintf(stderr, "Executing command\n");
            if (!strcmp(args[0], "exec"))
            {
                bin_path = args[1];
                args++;
            }
            else
            {
                bin_path = args[0];
            }
            if ((bin_path[0] == '.') || (bin_path[0] == '/'))
            {
                pid_t pid = fork();
                if (pid == -1)
                {
                    perror("Fork failed");
                    return 1;
                }
                else if (pid == 0)
                {
                    fprintf(stderr, "Executing from child process\n");
                    execv(bin_path, args);
                }
                else
                {
                    fprintf(stderr, "Waiting for child process\n");
                    int child_exit_status;
                    waitpid(-1, &child_exit_status, 0);
                }
            }
            else
            {
                int result = execv(bin_path, args);
                if (result == -1)
                {
                    perror("Failed to execute command");
                    return 1;
                }
            }

            return 0;

        default:
            printf("Unrecognized command: %s\n", *args);
            break;
        }

        free_args(args);
    }

    return 0;
}
