#include <stdio.h>
#include <stdlib.h>

#include "my_string.h"
#include "cstring.h"

static int max(int first, int second){
    if (first >= second)
        return first;  
    else 
        return second; 
}

static int min(int first, int second){
    if (first < second)
        return first;  
    else 
        return second; 
}

cstring * cstring_create(const char *s)
{
    cstring * str = (cstring *)malloc(sizeof(cstring));
    
    str->length = my_strlen(s);
    str->capacity = str->length << 1;
    str->data = cstring_copy_char(s);

    return str;
}

void cstring_delete(cstring * str)
{
    free(str->data);
    free(str);
}

void cstring_insert(cstring * to, const char * from, int pos)
{
    int from_len, new_len;
    char * tmp;

    if (pos < to->length && to->data != NULL)
    {
        from_len = my_strlen(from);
        new_len = to->length + from_len;

        if (from_len == 0)
        {
            return;
        }
        

        if (new_len < to->capacity)
        {
            my_memcpy(to->data + pos + from_len, to->data + pos, new_len - pos + 1);
            my_memcpy(to->data + pos, from, from_len);

            to->data[new_len] = '\0';
        }
        else
        {
            tmp = (char *)malloc(max(to->capacity, new_len + 1));

            my_memcpy(tmp, to->data, pos);
            my_memcpy(tmp + pos, from, from_len);
            my_memcpy(tmp + pos + from_len, to->data + pos, to->length + 1);
            tmp[new_len] = '\0';

            free(to->data);

            to->length = new_len;
            to->data = tmp;
            
            cstring_resize(to, new_len << 1);
        }
    }
}
//Добавить обработку ошибок при sub_start > lenght
cstring * cstring_substring(cstring * str, int sub_start, int sub_lenght)
{
    if (sub_start < str->length)
    {
        char * tmp = (char *)malloc(sub_lenght << 1);
        
        my_memcpy(tmp, str->data + sub_start, sub_lenght);

        cstring * result = cstring_create(tmp);

        free(tmp);

        return result;
    }

    return NULL;
}

char * cstring_copy_char(const char * s)
{
    int len = my_strlen(s);

    char * tmp = (char *)malloc(len << 1);
    my_memcpy(tmp, s, len + 1);
    tmp[len] = '\0';

    return tmp;
}

void cstring_resize(cstring * str, int new_capacity)
{
    str->data = realloc(str->data, new_capacity + 1);
    str->data[new_capacity] = '\0';

    str->capacity = new_capacity;
}
