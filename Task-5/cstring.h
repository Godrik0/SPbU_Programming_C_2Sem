#ifndef CSTRING_H_
#define CSTRING_H_

typedef struct 
{
    char *data;
    int length;
    int capacity;
} cstring;

cstring * cstring_create(const char *s);
void cstring_delete(cstring * str);
char * cstring_copy_char(const char * s);
void cstring_insert(cstring * to, const char * from, int pos);
void cstring_resize(cstring * str, int new_capacity);
cstring * cstring_substring(cstring * str, int sub_start, int sub_lenght);
#endif