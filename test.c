#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *rl;
    rl[0] = '\0';
    if (rl && strlen(rl) == 0)
        printf("ss\n");
    return (0);
}