#include "handlers.h"
#include "headers.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "url_encode.c"

#define MAX_REQUEST_SIZE (1 << 14)
#define BUF_SIZE (1 << 12)

void hello_handler(int socket_fd) {
    write(socket_fd, "Hello\n", 7);
    close(socket_fd);
}

int extract_request(int fd, char **request) {
    char buf[BUF_SIZE];
    char request_buf[MAX_REQUEST_SIZE];
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
        memcpy(request_buf, buf, bytes_read);
    } while(bytes_read == BUF_SIZE);
    *request = url_encode(request_buf);
    return 0;
}

void file_handler(int socket_fd)  {
    char *request = NULL;
    char *resp_headers = NULL;
    if(extract_request(socket_fd, &request)) return;

    char *request_line = strtok(request, "\n");
    strtok(request_line, " ");
    char *path = strtok(NULL, " ");
    while((*path) == '/') path++; // strip leading slashes (prevents malicious client from accessing host directory structure)

    if (strstr(path, "..") != NULL) { // this is a directory traversal attack
        get_headers(&resp_headers, 400, NULL, 0);    
        write_response(socket_fd, resp_headers, NULL);
        free(request);
        return;
    }

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
    free(request);
}
