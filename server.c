#include "server.h"
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_QUEUED 1000

extern int errno;

void run_server(struct server_options *opts, void (*handler) (int)) {
    if (chdir(opts->path) == -1) {
        perror("Error opening path");
        exit(errno);
    }

    int sockfd;
    struct addrinfo myname, *res;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    memset(&myname, 0, sizeof(myname));
    myname.ai_family = AF_UNSPEC;
    myname.ai_socktype = SOCK_STREAM;
    getaddrinfo(NULL, opts->port, &myname, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("Failed to bind port");
        exit(errno);
    }
    if (listen(sockfd, MAX_QUEUED) == -1) {
        perror("Listen failed");
        exit(errno);
    }

    freeaddrinfo(res);

    while(1) {
        int clientsock = accept(sockfd, (struct sockaddr *) &their_addr, &addr_size);
        pid_t pid = fork();
        if (pid == 0) {
            close(sockfd);
            handler(clientsock);
            exit(0);
        }
    }
}

