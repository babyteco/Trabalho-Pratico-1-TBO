#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UnionFind.h"
#include "ponto.h"
#include "arvore.h"



int main(int argc, char* argv[]){
    FILE *f = fopen(argv[1], "r");
    int qtd_pontos = 0;
    
    if(!f){
        printf("Erro ao ler o arquivo %s\n", argv[1]);
        return 1;
    }

    UnionFind *uf = le_entrada(f, &qtd_pontos);
    

    libera_UF(uf, qtd_pontos);
    fclose(f);

    return 0;
}