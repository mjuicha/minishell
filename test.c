#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
    // char *str = malloc(sizeof(char) * 10);
    // str = NULL;
    // (void)str;
    by();
    while (1)
    {}
    return 0;
}
