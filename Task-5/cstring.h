#ifndef CSTRING_H_
#define CSTRING_H_

typedef struct _cstring
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
int cstring_find(const cstring * text, const char * pat, const int pos);
cstring ** cstring_split(const cstring * str, const char * sepator);
int cstring_compare(const cstring * str1, const cstring * str2);


static inline void cstring_append(cstring *cs, const char *s)
{
	cstring_insert(cs, s, cs->length);
}

static inline int cstring_empty(const cstring *cs)
{
	return (cs->data == NULL && cs->length == 0);
}

#endif