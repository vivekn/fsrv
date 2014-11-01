/*
 * Simple and fast dynamic strings
 */
#include <fstring.h>
#include <string.h>
#include <stdlib.h>

#define PADDING 16

fstring * fstring_new(const char *str) {
    int len = strlen(str);
    fstring * result = (fstring *) malloc(sizeof(fstring));
    memset(result, 0, sizeof(*result));
    result->length = len;
    result->capacity = len + PADDING;
    result->data = (char *) malloc(result->capacity);
    memcpy(result->data, str, len);
    return result;
}

fstring * fstrcat(fstring *str1, const char *str2) {
    fstring *second = fstring_new(str2);
    append(str1, second);
    fstring_free(second);
    return str1;
}

void expand(fstring *str) {
    str->capacity *= 2;
    char *new_data = (char *) malloc(str->capacity);
    memcpy(new_data, str->data, str->length);
    free(str->data);
    str->data = new_data;
}

void append(fstring *f1, const fstring *f2) {
    int reqd_cap = f1->length + f2->length;
    while (f1->capacity < reqd_cap) expand(f1);
    memcpy(f1->data + f1->length, f2->data, f2->length);
}

void fstring_free(fstring *fstr) {
    free(fstr->data);
    free(fstr);
}
