#include <stdio.h>
#include <stdlib.h>
#include "ponto.h"

typedef struct ponto{
    char *nome;
    int m;
    double *coordenadas;
} Ponto;

Ponto* lerPontos(char *nome_arquivo, int *qtd){
    FILE *f = fopen(nome_arquivo, "r");

    if(!f){
        printf("Erro ao ler o arquivo %s\n", nome_arquivo);
        return NULL;
    }

    char *linha = NULL;
    int tam = 0;

    //inicialmente o vetor tem tamanho 1024, sendo realizado realloc se houverem mais que 1024 pontos
    int capacidade = 1024;
    Ponto *pontos = malloc(capacidade * sizeof(Ponto));
    *qtd = 0;

    while (getline(&linha, &tam, f) != -1) {

        char *token = strtok(copia, ", \n");
        if (!token) {
            continue;
        }

        Ponto p;
        p.nome = strdup(token);

        int capacidade_coordenadas = 2;
        int m = 0;
        p.coordenadas = malloc(capacidade_coordenadas * sizeof(double));

        token = strtok(NULL, ", \n");
        while (token != NULL) {

            if (m >= capacidade_coordenadas) {
                capacidade_coordenadas *= 2;
                p.coords = realloc(p.coords, capacidade_coordenadas * sizeof(double));
            }

            p.coordenadas[m] = atof(token);
            m++;

            token = strtok(NULL, " \n");
        }

        p.m = m;

        if (*qtd >= capacidade) {
            capacidade *= 2;
            pontos = realloc(pontos, capacidade * sizeof(Ponto));
        }

        pontos[(*qtd)] = p;
        (*qtd)++;
    }

    free(linha);
    fclose(f);

    return pontos;
}


