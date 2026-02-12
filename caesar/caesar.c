#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int command_line(char num[]);
char rotacao(char c, int n);

int main(int argc, char *argv[])
{
    /*
    Pegar a quantidade de criptação
    Pedir o texto a ser criptografado
    fazer a criptografia
    Exibir o texto criptografado
    */
   int erro;
   if(argc == 2)
   {
    erro = command_line(argv[1]);
   }
   if (argc != 2 || erro == 1)
   {
    printf("Usage: ./ceaser key\n");
    return 1;
   }

   printf("Plaintext:  ");
   char *caracteres;
   fgets(caracteres, sizeof(caracteres), stdin);
   caracteres[strcspn(caracteres, "\n")] = '\0';

   int valor = atoi(argv[1]) % 26; // reduz o numero
   int m = 0;
   do
   {
    int n = caracteres[m];
    if(n == 0) // se n digitar nada
    {
        break;
    }
    caracteres[m] = rotacao(caracteres[m], valor);
    m++;
   }
   while(caracteres[m] != '\0');


   printf("Ciphertext: %s", caracteres);
   return 0;
}

int command_line(char num[])
{
    for (int i = 0; num[i] != '\0'; i++)
    {
        if (num[i] < '0' || num[i] > '9')
        {
            return 1;   // erro
        }
    }
    return 0;
}

char rotacao(char letra_prim, int criptografia )
{

    int letra = letra_prim; // a = letra
    char letra_final;

    if(letra >= 97 && letra <= 122)
    {
    letra_final = 97 + ((letra - 97 + criptografia) % 26);
    return letra_final;
    }
    if(letra >= 65 && letra <= 90)
    {
    letra_final = 65 + ((letra - 65 + criptografia) % 26);
    return letra_final;
    }
    else
    {
    return letra;
    }
}