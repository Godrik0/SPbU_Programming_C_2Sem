#include "cstring.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    cstring * s = cstring_create("I code for 2 hours everyday");
    
    cstring * sub = cstring_create("I code for 3 hours everyday");

    printf("%d\n", cstring_compare(s, sub));
    
    cstring_delete(s);
    cstring_delete(sub);

    return 0;
}
