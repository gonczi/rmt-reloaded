#include "error.h"
#include <stdio.h>

void Perror(const char *str)
{
    printf("%s", str);
}

void _Perror(const char *str, ...)
{
    printf("%s", str);
}
