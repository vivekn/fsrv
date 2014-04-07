struct server_options {
    int n_threads;
    char *path;
    char *port;
};

void run_server(struct server_options *);

void base_handler(int);
