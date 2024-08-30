#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *rl;
    rl = readline("");
    printf("%s\n", rl);
    return (0);
}