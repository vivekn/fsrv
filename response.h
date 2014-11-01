#include <stdio.h>

void get_status_code(char *result, int status_code);
void get_mime_type(const char *filename, char *mime_type);
char * get_date();

void get_headers(char **restrict result, int status_code, const char *restrict mimetype, long clen);
void append_header(char *restrict headers, const char *restrict key, const char *restrict value);

void flush_client(int sockfd);
void write_response(int sockfd, char *restrict headers, char *restrict body);
void write_file_response(int sockfd, char *restrict headers, FILE *restrict file);
void write_error_response(int socket_fd, int status_code, const char *message);
