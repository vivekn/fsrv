#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#define MAX_QUEUED 128

struct server_options {
    int n_threads;
    char *path;
    char *port;
};

void run_server(struct server_options *, void (*) (int));

#ifndef CREATE_LISTENING_SOCKET
#define CREATE_LISTENING_SOCKET
// Including implementation here to avoid repetition.
int create_listening_socket(struct server_options *opts) {
    if (chdir(opts->path) == -1) {
        perror("Error opening path");
        exit(errno);
    }

    int sockfd;
    struct addrinfo myname, *res;
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
    return sockfd;
}
#endif
