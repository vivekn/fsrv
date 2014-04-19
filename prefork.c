#include "server.h"
#define NUM_PROCS 1

void run_server(struct server_options *opts, void (*handler) (int)) {
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int sockfd = create_listening_socket(opts);

    // Create process pool
    for(int i = 0; i < NUM_PROCS - 1; i++) {
        pid_t pid = fork();
        if (pid == 0) break;
    }

    while(1) {
        int clientsock = accept(sockfd, (struct sockaddr *) &their_addr, &addr_size);
        handler(clientsock);
        close(clientsock);
    }
}

