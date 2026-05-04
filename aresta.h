#ifndef ARESTA_H
#define ARESTA_H
#include "UnionFind.h"
#include "arvore.h"
#include "ponto.h"
typedef struct unionfind UnionFind;

typedef struct are Aresta;

int calcula_qtd_arestas(int qtd);

Aresta* arestas_init (int qtd);

void atualiza_aresta(Aresta *a, int p, int q, double dist, int k);

void ordena_arestas(Aresta *a, int qtd);

void conectar_arvores(UnionFind *uf, Aresta *a, int k, int qtd);

void libera_arestas(Aresta* a);

#endif 