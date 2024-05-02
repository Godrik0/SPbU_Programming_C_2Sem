#include <stdio.h>
#include <stdlib.h>

#include "my_string.h"
#include "private_cstring.h"
#include "include/cstring.h"

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
    if (to == NULL || from == NULL || to->data == NULL) {
        return;
    }

    if (pos < 0 || pos > to->length) {
        return;
    }

    int from_len, new_len;
    char * tmp;

    from_len = my_strlen(from);
    new_len = to->length + from_len;

    if (from_len == 0) {
        return;
    }
    
    if (new_len < to->capacity) {
        my_memcpy(to->data + pos + from_len, to->data + pos, new_len - pos);
        my_memcpy(to->data + pos, from, from_len);

        to->data[new_len] = '\0';
    }
    else 
    {
        tmp = (char *)malloc(new_len + 1);

        my_memcpy(tmp, to->data, pos);
        my_memcpy(tmp + pos, from, from_len);
        my_memcpy(tmp + pos + from_len, to->data + pos, to->length - pos);
        tmp[new_len] = '\0';

        free(to->data);

        to->length = new_len;
        to->data = tmp;
        
        cstring_resize(to, new_len << 1);
    }
}

cstring * cstring_substring(cstring * str, int sub_start, int sub_lenght)
{
    if (sub_start < str->length)
    {
        char * tmp = (char *)malloc(sub_lenght + 1);
        
        my_memcpy(tmp, str->data + sub_start, sub_lenght);

        tmp[sub_lenght] = '\0';

        cstring * result = cstring_create(tmp);

        free(tmp);

        return result;
    }

    return NULL;
}

static void bad_character_heuristic(const char * str, int * bad_char)
{
    for (int i = 0; i < 256; i++)
    {
        bad_char[i] = -1;
    }

    for (int i = 0; i < my_strlen(str); i++)
    {
        bad_char[(int)str[i]] = i;
    }
    
}

int cstring_find(const cstring * text, const char * pat, const int pos)
{
    int bad_char[256];

    bad_character_heuristic(pat, bad_char);

    int i = pos;
    int last = my_strlen(pat) - 1;

    while (i <= text->length - last)
    {
        int j = last;

        while (j >= 0 && pat[j] == text->data[i + j])
        {
            j--;    
        }
        
        if (j == -1)
        {
            return i;
        }

        i += max(last - bad_char[(int)text->data[last + i]], 1);
    }
    
    return -1;
}

cstring ** cstring_split(const cstring * str, const char * separator)
{
    cstring ** result = 0;
    int count_token = 2;
    int pos = 0;
    int sep_length = my_strlen(separator);

    while ((pos = cstring_find(str, separator, pos)) != -1)
    {
        pos += sep_length;
        count_token++;   
    }

    result = (cstring **)malloc(sizeof(cstring *) * (count_token));
    
    char * start = str->data;
    pos = 0;
    int index = 0;
    int token_length = 0;
    while ((pos = cstring_find(str, separator, pos)) != -1)
    {
        token_length = pos - (start - str->data);
        char *buffer = (char *)malloc(token_length + 1);

        my_memcpy(buffer, start, token_length);
        buffer[token_length] = '\0';

        result[index++] = cstring_create(buffer);
        
        free(buffer);

        start += token_length + sep_length;
        pos += sep_length;
    }
    
    int length = my_strlen(start);
    char *last_buffer = (char *)malloc(length + 1);
    my_memcpy(last_buffer, start, length);
    last_buffer[length] = '\0';
    
    result[index] = cstring_create(last_buffer);
    
    free(last_buffer);
    
    result[index + 1] = NULL;

    return result;
}

int cstring_compare(const cstring * str1, const cstring * str2)
{
    if (str1->length != str2->length)
    {
        return str1->length - str2->length;
    }
    
    const char *ptr1 = str1->data;
    const char *ptr2 = str2->data;
    
    while (*ptr1 && (*ptr1 == *ptr2))
    {
        ptr1++;
        ptr2++;
    }
    
    return *(unsigned char *)ptr1 - *(unsigned char *)ptr2;
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
