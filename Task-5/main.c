#include "cstring.h"
#include <stdio.h>

int main()
{
    cstring * s = cstring_create("qwerty");

    cstring_insert(s, "qazwsx", 4);

    cstring * sub = cstring_substring(s, 3, 6);

    printf("%s\n", sub->data);

    cstring_delete(s);
    cstring_delete(sub);
    return 0;

}