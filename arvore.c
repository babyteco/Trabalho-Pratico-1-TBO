#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include "arvore.h"
#include "ponto.h"

// Definição das structs conforme sua nova estratégia
struct arv {
    Ponto *p;
    struct arv* primeiro_filho;
    struct arv* proximo_irmao;
};

typedef struct arv Arvore;

// Cria uma árvore vazia
Arvore* arv_criavazia (void){
    return NULL;
}

// Cria uma árvore com a informação do ponto p
// Na representação de Kruskal, inicialmente os ponteiros são NULL
Arvore* arv_cria (Ponto *p){
    Arvore *arv = (Arvore*) malloc(sizeof(Arvore));
    if (arv == NULL) return NULL;
    
    arv->p = p;
    arv->primeiro_filho = NULL;
    arv->proximo_irmao = NULL;
    return arv;
}

// Retorna 1 se a árvore estiver vazia
int arv_vazia (Arvore* a){
    return (a == NULL);
}

// Indica a ocorrência (1) ou não (0) do ponto pelo nome
int arv_pertence (Arvore* a, char* nome){
    if (arv_vazia(a)) return 0;
    
    // Verifica o nó atual usando a função de acesso do seu ponto.h
    if (strcmp(get_nome_ponto(a->p), nome) == 0) return 1;
    
    // Busca recursiva no primeiro filho e nos irmãos
    return arv_pertence(a->primeiro_filho, nome) || arv_pertence(a->proximo_irmao, nome);
}

// Retorna a quantidade de folhas da árvore não binária
// Um nó é folha se ele não possui nenhum filho
int folhas (Arvore* a){
    if (a == NULL) return 0;
    
    // Se não tem filho, este nó é uma folha. 
    // Mas ainda precisamos contar as folhas nos seus irmãos.
    if (a->primeiro_filho == NULL){
        return 1 + folhas(a->proximo_irmao);
    }
    
    // Se tem filho, ele não é folha. Contamos apenas nos descendentes e irmãos.
    return folhas(a->primeiro_filho) + folhas(a->proximo_irmao);
}

// Retorna a altura da árvore
int altura(Arvore* a){
    if (a == NULL) return -1;
    
    int max_alt = -1;
    Arvore* q;
    
    // A altura de um nó é 1 + a maior altura entre seus filhos
    for (q = a->primeiro_filho; q != NULL; q = q->proximo_irmao) {
        int h = altura(q);
        if (h > max_alt) max_alt = h;
    }
    
    return max_alt + 1;
}

// Retorna o ponteiro para o ponto armazenado no nó
Ponto *getPonto(Arvore *arvore){
    if (arvore == NULL) return NULL;
    return arvore->p;
}

// Libera o espaço de memória ocupado pela árvore
// Segue a lógica: libera o filho (e toda a subárvore dele) e depois o irmão
Arvore* arv_libera (Arvore* a){
    if (!arv_vazia(a)){
        arv_libera(a->primeiro_filho);
        arv_libera(a->proximo_irmao);
        
        liberaPonto(a->p);
        free(a);
    }
    return NULL;
}