#include "response.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#define HEADER_S 2048
#define BUF_SIZE 4096

extern int errno;

void get_status_code(char *result, int status_code) {
    // Auto generated code follows
    switch(status_code) {
        case 100:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 100, "Continue");
            break;
        case 101:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 101, "Switching Protocols");
            break;
        case 200:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 200, "OK");
            break;
        case 201:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 201, "Created");
            break;
        case 202:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 202, "Accepted");
            break;
        case 203:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 203, "Non-Authoritative Information");
            break;
        case 204:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 204, "No Content");
            break;
        case 205:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 205, "Reset Content");
            break;
        case 206:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 206, "Partial Content");
            break;
        case 300:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 300, "Multiple Choices");
            break;
        case 301:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 301, "Moved Permanently");
            break;
        case 302:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 302, "Found");
            break;
        case 303:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 303, "See Other");
            break;
        case 304:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 304, "Not Modified");
            break;
        case 305:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 305, "Use Proxy");
            break;
        case 307:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 307, "Temporary Redirect");
            break;
        case 400:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 400, "Bad Request");
            break;
        case 401:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 401, "Unauthorized");
            break;
        case 402:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 402, "Payment Required");
            break;
        case 403:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 403, "Forbidden");
            break;
        case 404:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 404, "Not Found");
            break;
        case 405:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 405, "Method Not Allowed");
            break;
        case 406:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 406, "Not Acceptable");
            break;
        case 407:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 407, "Proxy Authentication Required");
            break;
        case 408:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 408, "Request Time-out");
            break;
        case 409:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 409, "Conflict");
            break;
        case 410:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 410, "Gone");
            break;
        case 411:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 411, "Length Required");
            break;
        case 412:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 412, "Precondition Failed");
            break;
        case 413:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 413, "Request Entity Too Large");
            break;
        case 414:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 414, "Request-URI Too Large");
            break;
        case 415:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 415, "Unsupported Media Type");
            break;
        case 416:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 416, "Requested range not satisfiable");
            break;
        case 417:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 417, "Expectation Failed");
            break;
        case 500:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 500, "Internal Server Error");
            break;
        case 501:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 501, "Not Implemented");
            break;
        case 502:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 502, "Bad Gateway");
            break;
        case 503:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 503, "Service Unavailable");
            break;
        case 504:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 504, "Gateway Time-out");
            break;
        case 505:
            sprintf(result, "HTTP/1.1 %d %s\r\n", 505, "HTTP Version not supported");
            break;
        default:
            sprintf(result, "HTTP/1.1 %d %s\r\n", status_code, "OK");
            break;
    }
}

/* Depends on the file command provided by the shell */
void get_mime_type(char *filename, char *mime_type) {
    char command[256];
    sprintf(command, "file --mime-type -b %s", filename);
    FILE* pipe = popen(command, "r");
    int read = fscanf(pipe, "%s", mime_type);
    if (!read) strcpy(mime_type, "application/octet-stream"); // Default mime type
    pclose(pipe);
}

void get_headers(char **result, int status_code, const char *mimetype, long clen) {
    *result = (char *) malloc(HEADER_S);
    get_status_code(*result, status_code);
    if (mimetype != NULL)
        append_header(*result, "Content-Type", mimetype);
    char slen[33];
    sprintf(slen, "%ld", clen);
    if (clen > 0)
        append_header(*result, "Content-Length", slen);
    append_header(*result, "Connection", "close");
}

// This is not very efficient, but I don't want to add too much complexity for now.
void append_header(char *result, const char *key, const char *value) {
    strcat(result, key);
    strcat(result, ": ");
    strcat(result, value);
    strcat(result, "\r\n");
}

// We don't care about what the client sends, just flush it so that write calls don't block.
void flush_client(int sockfd) {
    char buf[BUF_SIZE];
    int read = recv(sockfd, buf, BUF_SIZE, MSG_PEEK | MSG_DONTWAIT); // Check if there is any data available
    if (read >= 0) {
        do
        read = recv(sockfd, buf, BUF_SIZE, 0);
        while (read == BUF_SIZE);
    }
}

void write_response(int sockfd, char *headers, char *body) {
    strcat(headers, "\r\n");
    int hlen = strlen(headers);
    write(sockfd, headers, hlen);
    free(headers);
    if (body != NULL) {
        int blen = strlen(body);
        write(sockfd, body, blen);
        close(sockfd);
        free(body);
    } else {
        close(sockfd);
    }

}

void write_file_response(int sockfd, char *headers, FILE *file) {
    strcat(headers, "\r\n");
    int hlen = strlen(headers);
    write(sockfd, headers, hlen);
    free(headers);

    int fd = fileno(file);
    char buf[BUF_SIZE];

    lseek(fd, 0, SEEK_SET);

    int bytes_read = read(fd, buf, BUF_SIZE);
    if (bytes_read == -1) {
        perror("Error reading file");
        exit(errno);
    }
    while(bytes_read > 0) {
        puts("writing chunk");
        write(sockfd, buf, bytes_read);
        bytes_read = read(fd, buf, BUF_SIZE);
    }
    close(fd);
    fclose(file);
    close(sockfd);
}

void write_error_response(int socket_fd, int status_code) {
    char *headers = NULL;
    get_headers(&headers, status_code, NULL, 0);
    write_response(socket_fd, headers, NULL);
}