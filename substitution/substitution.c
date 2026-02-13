#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int erro = 0;
char repetidas[26];
char lowalfabeto[26];
char upalfabeto[26];

int contagem(char letras[]);
char cifra(char texto);
char *ler_linha(void);

int main(int argc, char *argv[])
{
    /* Primeiro: Uso ./substitution 26caracteres; OK
    Segundo: validar a chave || tem q ser letras; não pode ter letras repitidas; tem q ter 26; OK
    Terceiro: pedir o texto a ser substituido; OK
    Quarto: substituir as letras do texto pela chave;
    NQXPOMAFTRHLZGECYJIUWSKDVB
    */

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    int x = contagem(argv[1]);
    if (x != 26)
    {
        printf("Key must contain 26 caracteres\n");
        return 1;
    }
    if(erro == -1)
    {
        printf("Must be letters\n");
        return 1;
    }
    if (erro == -2)
    {
        printf("Must contain different letters\n");
        return 1;
    }

    for(int i = 0; i < 26; i++)
    {
        char n = 'a';
        char d = 'A';
        lowalfabeto[i] = n + i;
        upalfabeto[i] = d + i;
    }
    
    printf("Plaintext:  ");
    char *texto = ler_linha();
    int i = strlen(texto);

    char criptografia[i + 1];
    for (int m = 0; m < i; m++)
    {
        criptografia[m] = cifra(texto[m]);
    }
    criptografia[i] = '\0';

    printf("Ciphertext: %s\n", criptografia);
    return 0;
}

int contagem(char letras[])
{
    int num = 0;
    for (int i = 0; letras[i] != '\0'; i++)// loop para verificar cada caracter da chave
    {
        num++;
        if (i >= 1) //pula a primeira letra
        {
            for (int k = 0; repetidas[k] != '\0'; k++) // loop que verifica se cada letra armazenada no repetidas é igual a letra q ta no loop principal
            {
                if(repetidas[k] == letras[i])
                {
                 erro = -2;
                }
            }
        }
        repetidas[i] = letras[i]; // armazena a letra no repetidas
        if (!isalpha(letras[i])) // verifica se é uma letra
        {
            erro = -1;
        }
    }
    return num;
}

char cifra(char texto)
{
    int n = 0;
    if (texto == 'A')
    {
        return texto = repetidas[0];
    }
    if (texto == 'a')
    {
        texto = repetidas[0];
        return texto + 32;
    }
    if(islower(texto))
    {
        do
        {
            n++;
        }
        while(texto != lowalfabeto[n]);

        texto = repetidas[n];
        return texto + 32;
    }
    if(isupper(texto))
    {
        do
        {
            n++;
        }
        while(texto != upalfabeto[n]);

        texto = repetidas[n];
        return texto;
    }
    return texto;
}

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