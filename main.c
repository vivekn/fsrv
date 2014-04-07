#include <stdio.h>
#include "server.h"

int main(int argc, char **argv) {
    struct server_options opts;
    opts.port = argv[1];
    run_server(&opts);
    return 0;
}
