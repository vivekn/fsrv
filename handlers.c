#include "handlers.h"
#include "response.h"
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
            write_error_response(fd, 400, "Bad request");
            return -1;
        }
        memcpy(request_buf, buf, bytes_read);
    } while(bytes_read == BUF_SIZE);
    *request = url_decode(request_buf);
    // puts(*request);
    return 0;
}

int check_method(int fd, const char *method) {
    if (strcmp(method, "GET") == 0) {
        return GET;
    } else if (strcmp(method, "HEAD") == 0) {
        return HEAD;
    } 
    write_error_response(fd, 501, "Method not implemented");
    return -1;
}

void file_handler(int socket_fd)  {
    char *request = NULL;
    char *resp_headers = NULL;
    if(extract_request(socket_fd, &request)) return;

    char *request_line = strtok(request, "\n");
    char *method = strtok(request_line, " ");
    int method_type = check_method(socket_fd, method);
    if (method_type == -1) {
        free(request);
        return;
    }

    char *path = strtok(NULL, " ");
    while(*path == '/') path++; // strip leading slashes (prevents malicious client from accessing host directory structure)
    if (strstr(path, "..") != NULL) { // this is a directory traversal attack
        write_error_response(socket_fd, 400, "Bad request");
        free(request);
        return;
    }
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        write_error_response(socket_fd, 404, "Not found"); // File not found
    } else {
        fseek(file, 0, SEEK_END);
        long clen = ftell(file);
        char mime_type[256];
        get_mime_type(path, mime_type);
        get_headers(&resp_headers, 200, mime_type, clen);
        switch(method_type) {
            case GET:
                write_file_response(socket_fd, resp_headers, file);
                break;
            case HEAD:
                write_response(socket_fd, resp_headers, NULL);
        }
    }
    free(request);
}
