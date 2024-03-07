#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#ifdef __unix__
#include <linux/limits.h>
#endif

#ifdef __APPLE__
#define PATH_MAX 4096 
#endif 

int first_word(char *input, int size) {
    for (int i = 0; i < size; i++) {
        if (isspace(*input)) {
            return i;
        } else {
            input++;
        }
    }
    return -1;
}

int run(char *cmd, int size) {
    if (strncmp(cmd, "exit", size) == 0) {
        return 1;
    } else
    if (strncmp(cmd, "hello", size) == 0) {
        return 2;
    } else {
        return -1;
    }
}

int main(void)
{
    char input[1024];

    while (1) {
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        printf("%s$ ", cwd);
        char *res = fgets(input, 1024, stdin);
        if (res == NULL) {
            break;
        }

        // Copy first word in command to cmd
        int first_word_len = first_word(res, 255);
        char cmd[256] = {0};
        strncpy(cmd, res, first_word_len);
        cmd[first_word_len] = '\0'; 

        if (res[0] != '\n') {
            printf("Unrecognized command: %s\n", cmd);
            printf("Cmd %d\n", run(cmd, 256));
        }
    }

    return 0;
}
