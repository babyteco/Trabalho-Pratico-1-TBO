#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UnionFind.h"
#include "arvore.h"
#include "ponto.h"
#include "aresta.h"

typedef struct unionfind{
    Arvore *a;
    int i;  //representa o pai (logica do union find)
    int sz; //armazena o numero de nos da arvore enraizada aqui
} UnionFind;

typedef struct {
    char **nomes;
    int tamanho;
} Grupo;

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
        //imprime_ponto(p);
        Arvore *a = arv_cria(p);

        if (*qtd >= capacidade_inicial) {
            capacidade_inicial *= 2;
            uf = (UnionFind*) realloc(uf, capacidade_inicial * sizeof(UnionFind));
        }

        uf[*qtd].a = a;
        uf[*qtd].i = *qtd;
        uf[*qtd].sz = 1;
        (*qtd)++;
    }
    free(linha);

    return uf;
} 

//retorno o nome do ponto armazenada na posicao i da uf
char *get_nome_uf(UnionFind *uf, int i){
    return get_nome_ponto(get_ponto_arvore(uf[i].a));
}

//retorna o indice da componente complexa de i esta (raiz da arvore i)
//path halving
int UF_find(UnionFind *uf, int i) {
    while (i != uf[i].i){
        uf[i].i = uf[uf[i].i].i; //faz cada nó visitado apontar para seu avo
        i = uf[i].i; // Buscar o pai ate a raiz.
    
    }
    return i; // Profundidade de i acessos.
}

void UF_union(UnionFind *uf, int p, int q) {
    //pendura a arvore raiz de uma na raiz da outra
    int i = UF_find(uf, p); // Pendure a arvore menor sob a maior.
    int j = UF_find(uf, q); // Profundidade de ? acessos.
    if (i == j) return;
    if (uf[i].sz < uf[j].sz) { 
        //concexao logica
        uf[i].i = j; 
        uf[j].sz += uf[i].sz; 

        //conexao fisica
        arv_conecta(uf[i].a, uf[j].a);
    }
    else { 
        //concexao logica
        uf[j].i = i;
        uf[i].sz += uf[j].sz;

        //conexao fisica
        arv_conecta(uf[j].a, uf[i].a);
    }
}

void preenche_arestas(UnionFind *uf, Aresta *a, int n){
    int k = 0;
    
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            Ponto *p1 = get_ponto_arvore(uf[i].a);
            Ponto *p2 = get_ponto_arvore(uf[j].a);
            double d = calcula_distancia(p1, p2);

            atualiza_aresta(a, i, j, d, k);
            k++;
        }
    }
    
}

//verifica se as arvores de indice p e q estão no mesmo grupo
int verifica_grupo(UnionFind *uf, int p, int q){
    if (UF_find(uf, p) == UF_find(uf, q)){
        return 1;
    } else return 0;
    
}

int compara_nomes(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int compara_grupos_entre_si(const void *a, const void *b) {
    Grupo *gA = (Grupo *)a;
    Grupo *gB = (Grupo *)b;

    return strcmp(gA->nomes[0], gB->nomes[0]);
}

void coletar_nomes(Arvore* a, char** nomes, int* index) {
    if (a == NULL) return;

    char *nome_origem = get_nome_ponto(get_ponto_arvore(a));
    
    nomes[*index] = (char*) malloc((strlen(nome_origem) + 1) * sizeof(char));
    strcpy(nomes[*index], nome_origem);

    (*index)++;

    coletar_nomes(get_primeiro_filho(a), nomes, index);
    coletar_nomes(get_proximo_irmao(a), nomes, index);
}

void imprime_grupos(UnionFind *uf, int qtd, int k, FILE *f){
    //cria uma lista contendo os k grupos e seus respectivos nomes dos pontos
    Grupo *lista_grupos = (Grupo*) malloc(k * sizeof(Grupo));
    int grupo_atual = 0;

    //percorre o union find procurando as raízes das componentes conexas
    for (int i = 0; i < qtd; i++){
        
        //se aquela arvore é a raiz armazena os nomes de todos os pontos filhos dela para posterior impressao
        if (uf[i].i == i){
            int tamanho_grupo = uf[i].sz;
            int contador = 0;
            
            //cria um vetor de nomes e chama a funcao recursiva para percorrer a arvore e completar os nomes
            char **nomes = (char**) malloc(tamanho_grupo * sizeof(char*));
            coletar_nomes(uf[i].a, nomes, &contador);
            qsort(nomes, tamanho_grupo, sizeof(char*), compara_nomes);
            
            //adiciona os nomes do grupo na lista de grupo
            lista_grupos[grupo_atual].nomes = nomes;
            lista_grupos[grupo_atual].tamanho = tamanho_grupo;
            grupo_atual++;
        }
    }

    //ordena a lista de grupos com base no nome do primeiro ponto
    qsort(lista_grupos, k, sizeof(Grupo), compara_grupos_entre_si);
    
    //imprime e libera a lista de grupos e nomes
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < lista_grupos[i].tamanho; j++){
            if (j == 0){
                fprintf(f, "%s", lista_grupos[i].nomes[j]);
            }else fprintf(f, ", %s", lista_grupos[i].nomes[j]); 
            free(lista_grupos[i].nomes[j]); // Libera o vetor de ponteiros do grupo
        }
        fprintf(f, "\n");
        free(lista_grupos[i].nomes);
    }

    free(lista_grupos);
}

void libera_UF(UnionFind *uf, int qtd){
    for (int i = 0; i < qtd; i++){
        //so libera as arvores raizes das componentes conexas, pois estas sao recursivas e liberam as outras
        if (uf[i].i == i) {
            arv_libera(uf[i].a);
        }
    }
    free(uf);
}
