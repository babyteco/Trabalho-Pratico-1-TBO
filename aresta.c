#include <stdio.h>
#include <stdlib.h>
#include "UnionFind.h"
#include "aresta.h"


typedef struct are{
    int p, q;
    double dist;
} Aresta;

int calcula_qtd_arestas(int qtd){
    return (qtd * (qtd - 1)) / 2;
}

Aresta* arestas_init (int qtd){
    int n = calcula_qtd_arestas(qtd);
    Aresta *a = (Aresta*) malloc(n * sizeof(Aresta));

    return a;
}

void atualiza_aresta(Aresta *a, int p, int q, double dist, int k){
    a[k].p = p;
    a[k].q = q;
    a[k].dist = dist;
}

int compara_arestas(const void *a, const void *b) {
    Aresta *arestaA = (Aresta *)a;
    Aresta *arestaB = (Aresta *)b;

    if (arestaA->dist < arestaB->dist) return -1;
    if (arestaA->dist > arestaB->dist) return 1;
    return 0;
}

void ordena_arestas(Aresta *a, int qtd){
    qsort(a, calcula_qtd_arestas(qtd), sizeof(Aresta), compara_arestas);
}

int numero_conexoes(int n, int k){
    //para ligar todos os n pontos de forma a se ter a arvore sao necessarias n-1 conexoes
    //o algoritmo de kruskal pede para retirar k-1 conexoes, restando apenas n-k conexoes
    return n - k;
}

void conectar_arvores(UnionFind *uf, Aresta *a, int k, int qtd){
    int num_conexoes = numero_conexoes(qtd, k);
    int i = 0, j = 0;

    while(i < num_conexoes && j < calcula_qtd_arestas(qtd)){
        if (!verifica_grupo(uf, a[j].p, a[j].q)){
            UF_union(uf, a[j].p, a[j].q);
            i++;
        }
        j++;
    }
}

void libera_arestas (Aresta* a){
    free(a);
}

