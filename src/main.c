#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>

int main(void)
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("Hello world!\n");
    printf("cwd: %s\n", cwd);

    return 0;
}
