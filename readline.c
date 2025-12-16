#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    char *line;
    size_t size = 0;

    line = NULL;
    printf("$ ");
    getline(&line, &size, stdin);
    free(line);
    return(0);
}