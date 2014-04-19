void hello_handler(int);
void file_handler(int);
int extract_request(int, char**);
int check_method(int, const char*);

enum {GET, HEAD};
