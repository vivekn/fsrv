#include "server.h"

void run_server(struct server_options *opts, void (*handler) (int)) {
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int sockfd = create_listening_socket(opts);

    while(1) {
        int clientsock = accept(sockfd, (struct sockaddr *) &their_addr, &addr_size);
        pid_t pid = fork();
        if (pid != 0) {
            close(sockfd);
            handler(clientsock);
            exit(0);
        }
        close(clientsock);
    }
}

