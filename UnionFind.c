#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "ponto.h"

typedef struct unionfind{
    Arvore *a;
    int i;
} UnionFind;


UnionFind* UF_init(int n) {
    UnionFind *uf = (UnionFind*) malloc(sizeof(UnionFind) * n);
    return uf;
}

UnionFind* le_entrada(FILE *f, int *qtd){
    int capacidade_inicial = 1024;
    UnionFind *uf = UF_init(capacidade_inicial);

    char *linha = NULL;
    size_t tam = 0;
    *qtd = 0;

    while (getline(&linha, &tam, f) != -1) {

        //ler nome do ponto
        char *token = strtok(linha, ", \n");
        if (!token) continue;
        char *nome_ponto = strdup(token);

        //ler coordenadas e saber dimensao do potno
        int capacidade_coordenadas = 2;
        int m = 0;
        double *coordenadas = (double*) malloc(sizeof(double) * capacidade_coordenadas);

        token = strtok(NULL, ", \n");
        while (token != NULL) {

            if (m >= capacidade_coordenadas) {
                capacidade_coordenadas *= 2;
                coordenadas = realloc(coordenadas, capacidade_coordenadas * sizeof(double));
            }

            coordenadas[m] = atof(token);
            m++;

            token = strtok(NULL, " \n");
        }

        //criacao do ponto e da arvore
        Ponto *p = cria_ponto(nome_ponto, m, coordenadas);
        imprime_ponto(p);
        Arvore *a = arv_cria(p);

        if (*qtd >= capacidade_inicial) {
            capacidade_inicial *= 2;
            uf = (UnionFind*) realloc(uf, capacidade_inicial * sizeof(UnionFind));
        }

        uf[*qtd].a = a;
        uf[*qtd].i = *qtd;
        (*qtd)++;
    }
    free(linha);

    return uf;
} 

// int UF_find(int i) {
//     while (i != id[i]) i = id[i]; // Buscar o pai ate a raiz.
//     return i; // Profundidade de i acessos.
// }

// void UF_union(int p, int q) {
//     int i = UF_find(p); // Pendure a arvore menor sob a maior.
//     int j = UF_find(q); // Profundidade de ? acessos.
//     if (i == j) return;
//     if (sz[i] < sz[j]) { 
//         id[i] = j; sz[j] += sz[i]; 
//     }
//     else { 
//         id[j] = i; sz[i] += sz[j]; 
//     }
// }

void libera_UF(UnionFind *uf, int qtd){
    for (int i = 0; i < qtd; i++){
        arv_libera(uf[i].a);
    }
    free(uf);
}
