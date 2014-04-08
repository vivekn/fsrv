#include "headers.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define HEADER_S 2048
#define BUF_SIZE 4096


void get_status_code(char *result, int status_code) {
    // Auto generated code follows
    switch(status_code) {
        case 100:
            sprintf(result, "%d %s\r\n", 100, "Continue");
            break;
        case 101:
            sprintf(result, "%d %s\r\n", 101, "Switching Protocols");
            break;
        case 200:
            sprintf(result, "%d %s\r\n", 200, "OK");
            break;
        case 201:
            sprintf(result, "%d %s\r\n", 201, "Created");
            break;
        case 202:
            sprintf(result, "%d %s\r\n", 202, "Accepted");
            break;
        case 203:
            sprintf(result, "%d %s\r\n", 203, "Non-Authoritative Information");
            break;
        case 204:
            sprintf(result, "%d %s\r\n", 204, "No Content");
            break;
        case 205:
            sprintf(result, "%d %s\r\n", 205, "Reset Content");
            break;
        case 206:
            sprintf(result, "%d %s\r\n", 206, "Partial Content");
            break;
        case 300:
            sprintf(result, "%d %s\r\n", 300, "Multiple Choices");
            break;
        case 301:
            sprintf(result, "%d %s\r\n", 301, "Moved Permanently");
            break;
        case 302:
            sprintf(result, "%d %s\r\n", 302, "Found");
            break;
        case 303:
            sprintf(result, "%d %s\r\n", 303, "See Other");
            break;
        case 304:
            sprintf(result, "%d %s\r\n", 304, "Not Modified");
            break;
        case 305:
            sprintf(result, "%d %s\r\n", 305, "Use Proxy");
            break;
        case 307:
            sprintf(result, "%d %s\r\n", 307, "Temporary Redirect");
            break;
        case 400:
            sprintf(result, "%d %s\r\n", 400, "Bad Request");
            break;
        case 401:
            sprintf(result, "%d %s\r\n", 401, "Unauthorized");
            break;
        case 402:
            sprintf(result, "%d %s\r\n", 402, "Payment Required");
            break;
        case 403:
            sprintf(result, "%d %s\r\n", 403, "Forbidden");
            break;
        case 404:
            sprintf(result, "%d %s\r\n", 404, "Not Found");
            break;
        case 405:
            sprintf(result, "%d %s\r\n", 405, "Method Not Allowed");
            break;
        case 406:
            sprintf(result, "%d %s\r\n", 406, "Not Acceptable");
            break;
        case 407:
            sprintf(result, "%d %s\r\n", 407, "Proxy Authentication Required");
            break;
        case 408:
            sprintf(result, "%d %s\r\n", 408, "Request Time-out");
            break;
        case 409:
            sprintf(result, "%d %s\r\n", 409, "Conflict");
            break;
        case 410:
            sprintf(result, "%d %s\r\n", 410, "Gone");
            break;
        case 411:
            sprintf(result, "%d %s\r\n", 411, "Length Required");
            break;
        case 412:
            sprintf(result, "%d %s\r\n", 412, "Precondition Failed");
            break;
        case 413:
            sprintf(result, "%d %s\r\n", 413, "Request Entity Too Large");
            break;
        case 414:
            sprintf(result, "%d %s\r\n", 414, "Request-URI Too Large");
            break;
        case 415:
            sprintf(result, "%d %s\r\n", 415, "Unsupported Media Type");
            break;
        case 416:
            sprintf(result, "%d %s\r\n", 416, "Requested range not satisfiable");
            break;
        case 417:
            sprintf(result, "%d %s\r\n", 417, "Expectation Failed");
            break;
        case 500:
            sprintf(result, "%d %s\r\n", 500, "Internal Server Error");
            break;
        case 501:
            sprintf(result, "%d %s\r\n", 501, "Not Implemented");
            break;
        case 502:
            sprintf(result, "%d %s\r\n", 502, "Bad Gateway");
            break;
        case 503:
            sprintf(result, "%d %s\r\n", 503, "Service Unavailable");
            break;
        case 504:
            sprintf(result, "%d %s\r\n", 504, "Gateway Time-out");
            break;
        case 505:
            sprintf(result, "%d %s\r\n", 505, "HTTP Version not supported");
            break;
        default:
            sprintf(result, "%d %s\r\n", status_code, "OK");
            break;
    }
}

void get_headers(char *result, int status_code, const char *mimetype, int clen) {
    result = (char *) malloc(HEADER_S);
    get_status_code(result, status_code);
    append_header(result, "Content-Type", mimetype);
    char slen[33];
    sprintf(slen, "%d", clen);
    append_header(result, "Content-Length", slen);
}

void append_header(char *result, const char *key, const char *value) {
    strcat(result, key);
    strcat(result, ": ");
    strcat(result, value);
    strcat(result, "\r\n");
}

void write_response(int sockfd, char *headers, char *body) {
    strcat(headers, "\r\n");
    int hlen = strlen(headers);
    write(sockfd, headers, hlen);
    free(headers);

    int blen = strlen(body);
    write(sockfd, body, blen);
    close(sockfd);
    free(body);
}

void write_file_response(int sockfd, char *headers, FILE *file) {
    strcat(headers, "\r\n");
    int hlen = strlen(headers);
    write(sockfd, headers, hlen);
    free(headers);

    int fd = fileno(file);
    char buf[BUF_SIZE];

    int bytes_read = read(fd, buf, BUF_SIZE);
    if (bytes_read == -1)
        perror("Error reading file");
    while(bytes_read > 0) {
        write(sockfd, buf, bytes_read);
        bytes_read = read(fd, buf, BUF_SIZE);
    }
    close(fd);
    fclose(file);
    close(sockfd);
}

