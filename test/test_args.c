#include <stdio.h>
#include "../src/args.h"
#include <string.h>
#include <assert.h>

void test_strcpy_safe(void) {
    char *src = "this is a";
    char *dst = (char *) malloc(sizeof(char) * 5);
    strlcpy(dst, src, 5);
    char *answer = "this";
    printf("%s\n", dst);
    assert(!(strcmp(answer, dst)));
}

void test_parse_word(void) {
    char *src = "this is a";
    int word_idx = parse_word(src, strlen(src));
    assert(word_idx == 5);

    char *src2 = "this";
    int word_idx2 = parse_word(src2, strlen(src2));
    assert(word_idx2 == 5);

    char *src3 = "";
    int word_idx3 = parse_word(src3, strlen(src3));
    assert(word_idx3 == -1);
}

void test_parse_args(void)
{
    char *arg_str = "test is a test";
    char **parsed = parse_args(arg_str);
    int count = 0;
    while (*parsed != NULL)
    {
        printf("%s\n", *parsed);
        parsed++;
        count += 1;
    }
    assert(count == 4);
}

int main(void)
{
    // test_strcpy_safe();
    test_parse_word();
    test_parse_args();
    return 0;
}