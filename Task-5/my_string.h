#ifndef MY_STRING_H_
#define MY_STRING_H_

#if USE_STRING
    #include <string.h>

    #define my_strlen strlen
    #define my_strcpy strcpy
    #define my_strcat strcat
    #define my_strcmp strcmp
    #define my_memcpy memcpy

#else

    void my_strcpy(char *s, const char *t);

    int my_strlen(const char *str);

    void my_strcat(char *to, const char *from);

    int my_strcmp(const char *s, const char *t);

    void my_memcpy(void * to, const void * from, int bytes);

#endif

#endif