#include "cstring.h"
#include <stdio.h>

int main()
{
    cstring * s = cstring_create("qwerty");

    cstring_insert(s, "svosvosvosvosvo", 4);

    cstring_insert(s, "zzzzzzzzz", 19);

    printf("%s\n", s->data);

    cstring_delete(s);
    return 0;

}