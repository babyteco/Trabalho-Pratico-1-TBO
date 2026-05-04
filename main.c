#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UnionFind.h"
#include "ponto.h"
#include "arvore.h"
#include "aresta.h"



int main(int argc, char* argv[]){
    FILE *f1 = fopen(argv[1], "r");
    int qtd_pontos = 0;
    int k = atoi(argv[2]);
    
    if(!f1){
        printf("Erro ao ler o arquivo %s\n", argv[1]);
        return 1;
    }

    UnionFind *uf = le_entrada(f1, &qtd_pontos);
    Aresta *a = arestas_init(qtd_pontos);
    preenche_arestas(uf, a, qtd_pontos);
    ordena_arestas(a, qtd_pontos);
    fclose(f1);

    //algoritmo de Kruskal
    conectar_arvores(uf, a, k, qtd_pontos);

    FILE *f2 = fopen("saida.txt", "w");
    imprime_grupos(uf, qtd_pontos, k, f2);
    fclose(f2);

    libera_arestas(a);
    libera_UF(uf, qtd_pontos);

    return 0;
}