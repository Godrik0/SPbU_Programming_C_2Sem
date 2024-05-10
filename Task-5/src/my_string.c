#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>

int my_strlen(const char *str)
{
    int i = 0;
    while(str[i] != '\0')
        i++;
    return i;
}

void my_strcat(char *to, const char *from)
{
    while(*to)
        to++;
    while(*to++ = *from++);
}

void my_strcpy(char *s, const char *t)
{
    while (*s++ = *t++);
}

int my_strcmp(const char *s,const char *t)
{
    for ( ; *s == *t; s++, t++){
        if (*s == '\0')
            return 0;}
    return *s - *t;
}

void my_memcpy(void *to, const void *from, int bytes) {
    char *chto = (char *)to;
    const char *chfrom = (const char *)from;

    char *temp_buffer = (char *)malloc(bytes);
   
    for (int i = 0; i < bytes; i++) {
        temp_buffer[i] = chfrom[i];
    }

    for (int i = 0; i < bytes; i++) {
        chto[i] = temp_buffer[i];
    }
    free(temp_buffer);
}

void my_memset(void * memptr, int val, int num)
{
    char * charmemptr = (char *)memptr;

    for (int i = 0; i < num; i++)
    {
        charmemptr[i] = val; 
    }

}