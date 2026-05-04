#ifndef UNION_FIND
#define UNION_FIND
#include <stdio.h>
#include "arvore.h"
#include "aresta.h"

typedef struct unionfind UnionFind;

UnionFind* UF_init(int n);

UnionFind* le_entrada(FILE *f, int *qtd);

void UF_union(UnionFind *uf, int p, int q);

void preenche_arestas(UnionFind *uf, Aresta *a, int n);

int verifica_grupo(UnionFind *uf, int p, int q);

void imprime_grupos(UnionFind *uf, int qtd, int k, FILE *f);

void libera_UF(UnionFind *uf, int qtd);

#endif
