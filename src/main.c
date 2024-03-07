#include <stdio.h>
#include <unistd.h>
#include <string.h>

#ifdef __unix__
#include <linux/limits.h>
#endif

#ifdef __APPLE__
#define PATH_MAX 4096 
#endif 

int main(void)
{
    char input[1024];

    while (!feof(stdin)) {
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        printf("%s$ ", cwd);
        char *res = fgets(input, 1024, stdin);
        if (res[0] != '\n') {
            printf("Unrecognized command\n");
        }
    }

    return 0;
}
