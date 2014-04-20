#include "server.h"
#include <pthread.h>
#define NUM_THREADS 50

struct thread_args {
    int socket;
    void (*handler) (int);
};

void * thread_loop(void *args) {
    struct thread_args *targs = (struct thread_args *) args;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;

    while(1) {
        int clientsock = accept(targs->socket, (struct sockaddr *) &their_addr,
            &addr_size);
        targs->handler(clientsock);
        close(clientsock);
    }
    return NULL;
}

void run_server(struct server_options *opts, void (*handler) (int)) {
    int sockfd = create_listening_socket(opts);
    pthread_t threads[NUM_THREADS];
    struct thread_args targs = {sockfd, handler};

    for(int i = 0; i < NUM_THREADS; i++) 
        pthread_create(&threads[i], NULL, thread_loop, &targs);

    for(int i = 0; i < NUM_THREADS; i++) 
        pthread_join(threads[i], NULL);
}

