#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"

void l(void)
{
    system("leaks a.out");
}

void by()
{
    char *str = malloc(sizeof(char) * 10);
    str = NULL;
    atexit(l);
    return;
}
int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    printf("%s\n", strdup(NULL));
    // char *str = malloc(sizeof(char) * 10);
    // str = NULL;
    // (void)str;
    printf("%lu\n", strlen("$="));
    // by();
    while (1)
    {}
    return 0;
}
