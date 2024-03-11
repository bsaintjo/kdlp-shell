#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/args.h"

void test_cmd_exit(void) {
    const char *cmd_str = "exit";
    char **args = (char **) malloc(sizeof(char *) * MAX_N_ARGS);
    int n_args = parse_args2(cmd_str, args);
    assert(n_args == 0);
    Command res = cmd(args, n_args);
    Command answer = EXIT;
    assert(res == answer);

    const char *cmd_str2 = "exit extra";
    int n_args2 = parse_args2(cmd_str2, args);
    assert(n_args2 == 1);
    Command res2 = cmd(args, n_args2);
    Command answer2 = CMD_ERROR;
    assert(res2 == answer2);

    free_args(args);
}

void test_cmd_cd(void) {
    const char *cmd_str = "cd new_dir";
    char **args = (char **) malloc(sizeof(char *) * MAX_N_ARGS);
    int n_args = parse_args2(cmd_str, args);
    assert(n_args == 1);
    Command res = cmd(args, n_args);
    assert(res == CHANGE_DIR);

    const char *cmd_str2 = "cd new new";
    int n_args2 = parse_args2(cmd_str2, args);
    assert(n_args2 == 2);
    Command res2 = cmd(args, n_args2);
    assert(res2 == CMD_ERROR);

    const char *cmd_str3 = "cd";
    int n_args3 = parse_args2(cmd_str3, args);
    assert(n_args3 == 0);
    Command res3 = cmd(args, n_args3);
    assert(res3 == CMD_ERROR);

    free_args(args);
}

void test_parse_word(void) {
    const char *src = "this is a";
    int word_idx = parse_word(src, strlen(src));
    assert(word_idx == 5);

    const char *src2 = "this";
    int word_idx2 = parse_word(src2, strlen(src2));
    assert(word_idx2 == 5);

    const char *src3 = "";
    int word_idx3 = parse_word(src3, strlen(src3));
    assert(word_idx3 == -1);
}

void test_parse_args(void) {
    const char *arg_str = "test is a test";
    char **parsed = parse_args(arg_str);
    assert(!strcmp(*parsed, "test"));

    int count = 0;
    while (*parsed != NULL) {
        parsed++;
        count += 1;
    }
    assert(count == 4);

    free_args(parsed);
}

int main(void) {
    // test_strcpy_safe();
    test_parse_word();
    test_parse_args();
    test_cmd_exit();
    test_cmd_cd();
    return 0;
}
