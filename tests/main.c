#include "test_headers.c"
#include <unistd.h>

void fork_and_test(void (*func) ()) {
    int child = fork();
    if (child == 0) 
        func();
}

int main() {
    fork_and_test(test_headers);
}
