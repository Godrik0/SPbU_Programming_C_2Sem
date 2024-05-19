#ifndef CSTRING_H_
#define CSTRING_H_

typedef struct _cstring
{
    char *data;
    int length;
    int size_allocated_memory;
} cstring;

cstring * cstring_create(const char *s);
cstring * cstring_init(char *s, int length);
void cstring_delete(cstring * str);
void cstring_insert(cstring * to, const char * from, int pos, int from_len);
cstring * cstring_substring(cstring * str, int sub_start, int sub_lenght);
int cstring_find(const cstring * text, const char * pat, const int pos);
cstring ** cstring_split(const cstring * str, const char * separator);
cstring ** cstring_split_char(const cstring * str, const char separator);
int cstring_compare(const cstring * str1, const cstring * str2);
int cstring_rfind(const cstring * text, const char pat);


static inline int cstring_empty(const cstring *cs)
{
	return (cs->data == 0 && cs->length == 0);
}

static inline void cstring_insert_char(cstring * to, const char * from, int pos)
{
    cstring_insert(to, from, pos, my_strlen(from));
}

static inline void cstring_insert_cstring(cstring * to, const cstring * from, int pos)
{
    cstring_insert(to, from->data, pos, from->length);
}

static inline void cstring_append(cstring *cs, const char *s)
{
	cstring_insert_char(cs, s, cs->length);
}

static inline void cstring_concatenation(cstring * to, const cstring * from)
{
    cstring_append(to, from->data);
}


#endif