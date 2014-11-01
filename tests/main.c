#include "test_headers.c"
#include "test_fstring.c"
#include <unistd.h>
#include <stdlib.h>

void fork_and_test(void (*func) ()) {
    int child = fork();
    if (child == 0) {
        func();
        exit(0);
    }
}

int main() {
    fork_and_test(test_headers);
    fork_and_test(test_fstring);
}
