#ifndef MY_STRING_H_
#define MY_STRING_H_

void my_strcpy(char *s, const char *t);

int my_strlen(const char *str);

void my_strcat(char *to, const char *from);

int my_strcmp(const char *s, const char *t);

void my_memcpy(void * to, const void * from, int bytes);

void my_memset(void * memptr, int val, int num);

#endif