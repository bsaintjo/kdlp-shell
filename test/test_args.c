#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "../src/args.h"

void test_execv(void) {
    // Executable name without a path
    const char *path = "/bin/ls";

    // Command-line arguments
    char *args[] = { "ls", "-l", NULL }; 
        // Attempt to execute "ls" using execv
    if (execv(path, args) == -1) {
        perror("execv");
    }
}

void test_cmd_exit(void) {
    char *cmd_str = "exit";
    int n_args = -1;
    char **args = parse_args(cmd_str, &n_args);
    assert(n_args == 1);
    Command res = cmd(args, n_args);
    assert(res == EXIT);
    free_args(args);
}


// void test_cmd_exit(void) {
//     const char *cmd_str = "exit";
//     char **args = (char **) malloc(sizeof(char *) * MAX_N_ARGS);
//     int n_args = parse_args2(cmd_str, args);
//     assert(n_args == 0);
//     Command res = cmd(args, n_args);
//     Command answer = EXIT;
//     assert(res == answer);

//     const char *cmd_str2 = "exit extra";
//     int n_args2 = parse_args2(cmd_str2, args);
//     assert(n_args2 == 1);
//     Command res2 = cmd(args, n_args2);
//     Command answer2 = CMD_ERROR;
//     assert(res2 == answer2);

//     free_args(args);
// }

// void test_cmd_cd(void) {
//     const char *cmd_str = "cd new_dir";
//     char **args = (char **) malloc(sizeof(char *) * MAX_N_ARGS);
//     int n_args = parse_args2(cmd_str, args);
//     assert(n_args == 1);
//     Command res = cmd(args, n_args);
//     assert(res == CHANGE_DIR);

//     const char *cmd_str2 = "cd new new";
//     int n_args2 = parse_args2(cmd_str2, args);
//     assert(n_args2 == 2);
//     Command res2 = cmd(args, n_args2);
//     assert(res2 == CMD_ERROR);

//     const char *cmd_str3 = "cd";
//     int n_args3 = parse_args2(cmd_str3, args);
//     assert(n_args3 == 0);
//     Command res3 = cmd(args, n_args3);
//     assert(res3 == CMD_ERROR);

//     free_args(args);
// }

void test_parse_args(void) {
    char *arg_str = "test is a test";
    int n_args = 0;
    char **parsed = parse_args(arg_str, &n_args);
    assert(!strcmp(*parsed, "test"));

    int count = 0;
    char **copy = parsed;
    while (*copy != NULL) {
        copy++;
        count += 1;
    }
    assert(count == 4);
    assert(n_args == 4);

    free_args(parsed);
}

int main(void) {
    test_parse_args();
    test_cmd_exit();
    // test_cmd_exit2();
    // test_cmd_cd();
    // test_execv();
    return 0;
}
