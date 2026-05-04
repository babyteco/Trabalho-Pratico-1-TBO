#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

double calcula_distancia(Ponto *p1, Ponto *p2){
    double sum = 0;

    for (int i = 0; i < p1->m; i++){
        sum += pow(p1->coordenadas[i] - p2->coordenadas[i], (double)2);    
    }
    
    return sqrt(sum);
}

void liberaPonto(Ponto *p){
    free(p->coordenadas);
    free(p->nome);
    free(p);
}
