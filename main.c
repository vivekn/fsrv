#include <stdio.h>

// The below line is a hack to prevent a linker error. FIXME
#define CREATE_LISTENING_SOCKET
#include "server.h"

#include "handlers.h"
#include <string.h>
#include <assert.h>


int main(int argc, char **argv) {
    struct server_options opts;
    opts.path = argv[1];
    opts.port = argv[2];
    run_server(&opts, file_handler);
    return 0;
}
