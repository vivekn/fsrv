#include <stdio.h>

void get_basic_headers(char *result);
void get_headers(char *result, const char *mimetype, int clen);
void append_header(char *headers, const char *key, const char *value);

void write_response(int sockfd, char *headers, char *body);
void write_file_response(int sockfd, char *headers, FILE *file);
