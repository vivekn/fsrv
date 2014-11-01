#include <assert.h>
#include "fstring.h"
#include "string.h"


void test_new() {
    fstring * test = fstring_new("Vivek");
    assert(memcmp(test->data, "Vivek", 5) == 0);
    assert(test->length == 5);
}

void test_fstrcat() {
    fstring *test = fstring_new("Hello");
    fstring *res = fstrcat(test, "World");
    assert(memcmp(res->data, "HelloWorld", 10) == 0);
    assert(memcmp(test->data, "HelloWorld", 10) == 0);
}

void test_free() {
    fstring *test = fstring_new("Hello");
    fstring_free(test);
    printf("%ld\n", sizeof(test));
    assert(test->data == NULL);
}

void test_fstring () {
    puts("Testing dynamic strings");
    test_new();
    test_fstrcat();
    test_free();
    puts("Passed");
}
