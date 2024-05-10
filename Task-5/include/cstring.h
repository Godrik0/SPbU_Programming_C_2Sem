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
void cstring_insert(cstring * to, const char * from, int pos);
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
	return (cs->data == 0 && cs->length == 0);
}

static inline int cstring_rfind(const cstring * text, const char * pat, const int pos)
{
    int result = cstring_find(text, pat, pos) ; 
    return result != -1 ? result + my_strlen(pat) : -1;
}

static inline void cstring_concatenation(cstring * to, const cstring * from)
{
    cstring_append(to, from->data);
}


#endif