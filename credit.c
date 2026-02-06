#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long seguranca();

int main(void)
{
    long long cartao = seguranca();
    long long numero = cartao;
    long long copia = cartao;

    //VERIFICAÇÃO DO PRIMEIRO DIGITO E SEGUNDO
    char digitos[20]; // tamanho suficiente para armazenar um número long long int
    sprintf(digitos, "%lli", copia); // sprintf converte o numero em string, e armazena na variavel digitos, o %lli indica que o numero é do tipo long long int
    char p_digito = digitos[0];
    char s_digito = digitos[1];
    digitos[2] = '\0'; // limpa a variavel digitos para evitar problemas futuros

    int soma = 0;
    int contador = 0;

    // verifica quantos numeros tem no cartao
    int comprimento = 0;

    while (numero > 0)
    {
        int digito = numero % 10;

        if (contador % 2 == 1)
        {
            digito *= 2;
            if (digito > 9)
            {
                digito = (digito % 10) + ( digito / 10);
            }
        }
        soma += digito;
        numero /= 10;
        contador++;
        comprimento++;
    }
    
    if(soma % 10 == 0)
    {
        char verificacao[3];
        verificacao[0] = p_digito;
        verificacao[1] = s_digito;
        verificacao[2] = '\0'; // limpa a variavel verificacao para evitar problemas futuros, mostra a onde a string termina pra ler melhor

        char VISA[2];
        VISA[0] = p_digito;
        VISA[1] = '\0';

        if((strcmp(verificacao, "34") == 0 || strcmp(verificacao, "37") == 0) && comprimento == 15)
        {
            printf("AMEX\n");
            return 0;
        }
        if((strcmp(verificacao, "51") == 0 || strcmp(verificacao, "52") == 0 || strcmp(verificacao, "53") == 0 || strcmp(verificacao, "54") == 0 || strcmp(verificacao, "55") == 0) && comprimento == 16)
        {
            printf("MASTERCARD\n");
            return 0;
        }
        if(strcmp(VISA, "4") == 0 && (comprimento == 13 || comprimento == 16))
        {
            printf("VISA\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }   
    else
    {
        printf("INVALID\n");
        return 0;
    }
}

long long seguranca()
{
    char caracteres[100];
    long long cartao;

    while(1)
    {
        printf("Number: ");

        if(!fgets(caracteres, sizeof(caracteres), stdin)) // fgets le tudo q foi digitado ateo \n e verifica se tem alguma coisa la, oq faz isso é !
        {
            return -1;
        }

        caracteres[strcspn(caracteres, "\n")] = '\0'; // strcspn encontra o indice do \n e substitui por \0, ele tambem conta quantos caracteres ate o \n

        char *end; // uma função sem função no momento mas que é necessária para o strtoll, e serve para indicar onde a conversão parou
        errno = 0; //  quantidade de erros
        cartao = strtoll(caracteres, &end, 10); // O strtoll converte texto em numero, aq é caracter, onde termina, e tipo de numero, q no caso é base 10

        if (end == caracteres || errno != 0 || cartao < 0 || *end != '\0') // end == caracteres verifica se nao foi digitado nada, errno != 0 verifica se houve erro na conversao, cartao < 0 verifica se o numero é negativo, *end != '\0' verifica se tem algo depois do numero
        {
            continue;
        }
        else
        {
            return cartao;
        }
    }
}