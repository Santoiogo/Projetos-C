#include "llinha.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 9

typedef struct
{
    char *name;
    int votes;
} candidate;
candidate candidates[MAX];
int candidate_count;

bool vote(char *name);
void print_winner(void);

int main(int argc, char *argv[])
{
    /*  1º Receber os candidatos pelo comando da linha
        2º Pedir a quantidade de votadores
        3º Pedir qual candidato votar
    */
    candidate_count = argc - 1;
    // segurança
    if (argc <= 1)
    {
        printf("Usage: ./plurality Candidates\n");
        return 1;
    }
    // segurança
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; argv[i][j] != '\0'; j++)
        {
            if (!isalpha(argv[i][j]))
            {
                printf("Invalid caracter\n");
                return 3;
            }
        }
    }
    // segurança
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates\n");
        return 2;
    }

    // registra os candidatos
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // pede o número de votantes
    printf("Number of voters: ");
    char *end;
    char *k = ler_linha();
    int l = strtoll(k, &end, 10);
    // verifica em qm votou e adiciona o voto
    for (int i = 0; i < l; i++)
    {
        printf("Vote: ");
        char *s;
        s = ler_linha();

        bool valid = vote(s);
        if (!valid)
            printf("Voto Invalido.\n");
    }
    print_winner();
    return 0;
}

void print_winner()
{
    int maior = candidates[0].votes;
    // descobrir o maior número de votos
    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[i].votes > maior)
        {
            maior = candidates[i].votes;
        }
    }
    // imprimir todos que têm esse número
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == maior)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}

bool vote(char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}
