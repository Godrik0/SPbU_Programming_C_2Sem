#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "my_string.h"
#include "private_cstring.h"
#include "../include/cstring.h"

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
    str->size_allocated_memory = str->length << 1;
    str->data = cstring_copy_char(s);

    return str;
}

cstring * cstring_allocate(int length)
{
    cstring * result = (cstring *)malloc(sizeof(cstring));
    int size_allocated_memory = (length << 1) + 1;

    result->data = (char *)malloc(sizeof(char) * size_allocated_memory);
    result->length = length;
    result->size_allocated_memory = size_allocated_memory;

    return result;
}

void cstring_delete(cstring * str)
{
    free(str->data);
    free(str);
}

void cstring_insert(cstring * to, const char * from, int pos)
{
    assert(to->data != NULL && to != NULL);

    if (from == NULL) {
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
    
    if (new_len < to->size_allocated_memory) 
    {
        //Сдвигаем вправо данные исходной строки, после помещаем в освободившееся место pos
        my_memcpy(to->data + pos + from_len, to->data + pos, new_len - pos);
        my_memcpy(to->data + pos, from, from_len);

        to->data[new_len] = '\0';
        to->length = new_len; //Добавить тесты (если отсутвует эта строка)
    }
    else 
    {
        tmp = (char *)malloc(new_len << 1);

        my_memcpy(tmp, to->data, pos);
        my_memcpy(tmp + pos, from, from_len);
        my_memcpy(tmp + pos + from_len, to->data + pos, to->length - pos);
        tmp[new_len] = '\0';

        free(to->data);

        to->length = new_len;
        to->data = tmp;
        to->size_allocated_memory = new_len << 1;
    }
}


cstring * cstring_substring(cstring * str, int sub_start, int sub_length)
{
    if ((sub_start + sub_length) < str->length)
    {
        cstring * result = cstring_allocate(sub_length);
        
        my_memcpy(result->data, str->data + sub_start, sub_length);

        result->data[sub_length] = '\0';

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
    // название (один из элементов массива - нул) 
    int count_substring_and_NULL = 2;
    int pos = 0;
    int sep_length = my_strlen(separator);

    while ((pos = cstring_find(str, separator, pos)) != -1)
    {
        pos += sep_length;
        count_substring_and_NULL++;
    }

    cstring ** result = (cstring **)malloc(sizeof(cstring *) * (count_substring_and_NULL));
    
    char * start = str->data;
    pos = 0;
    int index = 0;

    while ((pos = cstring_find(str, separator, pos)) != -1)
    {
        int token_length = pos - (start - str->data);

        cstring * tmp = cstring_allocate(token_length);

        my_memcpy(tmp->data, start, token_length);
        tmp->data[token_length] = '\0';

        result[index++] = tmp;

        start += token_length + sep_length;
        pos += sep_length;
    }
    
    // линейный проход не нужен ok
    int length = str->length - (start - str->data);
    cstring * tmp = cstring_allocate(length);
    my_memcpy(tmp->data, start, length);
    tmp->data[length] = '\0';
    
    result[index] = tmp;
    
    result[index + 1] = NULL;

    return result;
}

int cstring_compare(const cstring * str1, const cstring * str2)
{
    if (str1->length != str2->length)
    {
        return str1->length - str2->length;
    }
    
    return my_strcmp(str1->data, str2->data);
}

int cstring_compare_char(const cstring * str1, const char str2[])
{
    return my_strcmp(str1->data, str2);
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

    str->size_allocated_memory = new_capacity;
}
