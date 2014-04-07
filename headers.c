#include "headers.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define HEADER_S 2048
#define BUF_SIZE 4096


void get_basic_headers(char *result) {}

void get_headers(char *result, const char *mimetype, int clen) {
    result = (char *) malloc(HEADER_S);
    get_basic_headers(result);
    append_header(result, "Content-Type", mimetype);
    char slen[33];
    sprintf(slen, "%d", clen);
    append_header(result, "Content-Length", slen);
}

void append_header(char *result, const char *key, const char *value) {
    strcat(result, key);
    strcat(result, ": ");
    strcat(result, value);
    strcat(result, "\n");
}
    
void write_response(int sockfd, char *headers, char *body) {
    strcat(headers, "\n");
    int hlen = strlen(headers);
    write(sockfd, headers, hlen);
    free(headers);

    int blen = strlen(body);
    write(sockfd, body, blen);
    close(sockfd);
    free(body);
}

void write_file_response(int sockfd, char *headers, FILE *file) {
    strcat(headers, "\n");
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


