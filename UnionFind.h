#ifndef UNION_FIND
#define UNION_FIND
#include <stdio.h>
#include "arvore.h"

typedef struct unionfind UnionFind;

UnionFind* UF_init(int n);

UnionFind* le_entrada(FILE *f, int *qtd);

void libera_UF(UnionFind *uf, int qtd);

#endif
