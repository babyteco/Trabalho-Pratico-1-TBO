#include <stdio.h>
#include <stdlib.h>
#include "ponto.h"

typedef struct ponto{
    char *nome;
    int m;
    double *pontos;
} Ponto;

Ponto* lerPontos(char *nome_arquivo, int *qtd){
    FILE *f = fopen(nome_arquivo, "r");

    if(!f){
        printf("Erro ao ler o arquivo %s\n", nome_arquivo);
        return NULL;
    }

    char *linha = NULL;
    int tam = 0;

    int capacidade = 1024;
    Ponto *pontos = malloc(capacidade * sizeof(Ponto));
    *qtd = 0;

    while (getline(&linha, &tam, f) != -1) {

        char *copia = strdup(linha);

        char *token = strtok(copia, " \n");
        if (!token) {
            free(copia);
            continue;
        }

        Ponto p;
        p.nome = strdup(token);

        int capacidade_coords = 2;
        int m = 0;
        p.coords = malloc(cap_coords * sizeof(double));

        token = strtok(NULL, ", \n");
        while (token != NULL) {

            if (m >= cap_coords) {
                cap_coords *= 2;
                p.coords = realloc(p.coords, cap_coords * sizeof(double));
            }

            p.coords[m++] = atof(token);

            token = strtok(NULL, " \n");
        }

        p.m = m;

        if (*qtd >= capacidade) {
            capacidade *= 2;
            pontos = realloc(pontos, capacidade * sizeof(Ponto));
        }

        pontos[(*qtd)++] = p;

        free(copia);
    }

    free(linha);
    fclose(f);

    return pontos;
}


