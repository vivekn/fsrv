/*
 * Simple and fast dynamic strings
 * Author: Vivek Narayanan
 */

typedef struct fstring {
    int length;
    int capacity;
    char *data;
} fstring;

fstring * fstring_new(const char *str);

fstring * fstrcat(fstring *str1, const char *str2);

void append(fstring *f1, const fstring *f2);

void fstring_free(fstring *fstr);
