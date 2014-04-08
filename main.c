#include <stdio.h>
#include "server.h"
#include "handlers.h"

int main(int argc, char **argv) {
    struct server_options opts;
    opts.port = argv[1];
    run_server(&opts, hello_handler);
    return 0;
}
