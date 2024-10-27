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
    atexit(l);
    return;
}
void bg()
{
    char *s = malloc(sizeof(char) * 10);
    sleep(10);
}

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    bg();
    // char *str = malloc(sizeof(char) * 10);
    // str = NULL;
    // (void)str;
    // by();

    return 0;
}
