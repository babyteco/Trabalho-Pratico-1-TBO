#include <stdio.h>
#include <stdlib.h>
#include "ponto.h"

typedef struct ponto{
    char *nome;
    int m;
    double *coordenadas;
} Ponto;

Ponto *cria_ponto(char* nome, int m, double* coordenadas){
    Ponto *p = (Ponto*) malloc(sizeof(Ponto));
    p->nome = nome;
    p->m = m;
    p->coordenadas = coordenadas;
    return p; 
}

void imprime_ponto(Ponto* p){
    printf("PONTO %s: ", p->nome);
    for (int i = 0; i < p->m; i++){
        printf("%.2f, ", p->coordenadas[i]);
    }
    printf("\n");
}

char* get_nome_ponto(Ponto *p){
    return p->nome;
}

void liberaPonto(Ponto *p){
    free(p->coordenadas);
    free(p->nome);
    free(p);
}
