#include "handlers.h"
#include "headers.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_REQUEST_SIZE (1 << 14)
#define BUF_SIZE (1 << 12)

void hello_handler(int socket_fd) {
    write(socket_fd, "Hello\n", 7);
    close(socket_fd);
}

int extract_request(int fd, char *request) {
    char buf[BUF_SIZE];
    int total_bytes = 0, bytes_read;
    do {
        bytes_read = read(fd, buf, BUF_SIZE);
        total_bytes += bytes_read;
        if (total_bytes > MAX_REQUEST_SIZE) {
            char *response = NULL;
            get_headers(&response, 400, NULL, 0);
            write_response(fd, response, NULL);
            return -1;
        }
        memcpy(request, buf, bytes_read);
    } while(bytes_read == BUF_SIZE);
    return 0;
}

void file_handler(int socket_fd)  {
    char request[MAX_REQUEST_SIZE];
    if(extract_request(socket_fd, request)) return;

    char *request_line = strtok(request, "\n");
    strtok(request_line, " ");
    char *path = strtok(NULL, " ");
    char *resp_headers = NULL;
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        get_headers(&resp_headers, 404, NULL, 0);
        write_response(socket_fd, resp_headers, NULL);
    } else {
        int clen = fseek(file, 0, SEEK_END);
        rewind(file);
        char mime_type[256];
        get_mime_type(path, mime_type);
        get_headers(&resp_headers, 200, mime_type, clen);
        write_file_response(socket_fd, resp_headers, file);
    }
}
