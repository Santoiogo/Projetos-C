#include "llinha.h"
#include <stdlib.h>
#include <stdio.h>

char *ler_linha(void)
{
    int tamanho = 64;
    int i = 0;
    char *buffer = malloc(tamanho);

    if (!buffer) return NULL;

    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        buffer[i++] = c;

        if (i >= tamanho - 1)
        {
            tamanho *= 2;
            buffer = realloc(buffer, tamanho);

            if (!buffer) return NULL;
        }
    }
    buffer[i] = '\0';
    return buffer;
}