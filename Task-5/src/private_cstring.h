#ifndef PRIVATE_CSTRING_H_
#define PRIVATE_CSTRING_H_

#include "include/cstring.h"

char * cstring_copy_char(const char * s);

void cstring_resize(cstring * str, int new_capacity);

#endif