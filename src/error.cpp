#include "error.h"
#include <stdio.h>

void Perror(const char *str)
{
    printf(str);
}

void _Perror(const char *str, ...)
{
    printf(str);
}
