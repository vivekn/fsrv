#include "server.h"
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUEUED 1000
#define printerr(msg) printf("%s: %s", msg, strerror(errno))

extern int errno;

void run_server(struct server_options *opts) {
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
        printerr("Failed to bind port");
    }
    if (listen(sockfd, MAX_QUEUED) == -1) {
        printerr("Listen failed");
    }

    
    freeaddrinfo(res);

    while(1) {
        int clientsock = accept(sockfd, (struct sockaddr *) &their_addr, &addr_size);
        pid_t pid = fork();
        if (pid == 0) {
            close(sockfd);
            base_handler(clientsock);
            exit(0);
        }
    }
}

void base_handler(int socket_fd) {
    write(socket_fd, "Hello\n", 7);
    close(socket_fd);
}


    
