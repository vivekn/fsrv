#include <stdio.h>

void get_status_code(char *result, int status_code);
void get_mime_type(char *filename, char *mime_type);

void get_headers(char **result, int status_code, const char *mimetype, int clen);
void append_header(char *headers, const char *key, const char *value);

void write_response(int sockfd, char *headers, char *body);
void write_file_response(int sockfd, char *headers, FILE *file);
