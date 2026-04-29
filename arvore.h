#ifndef ARVORE_H
#define ARVORE_H
#include "ponto.h"

typedef struct arv Arvore;

//Cria uma árvore vazia
Arvore* arv_criavazia (void);

// Cria uma árvore com a informação do ponto p
Arvore* arv_cria (Ponto *p);

// Retorna 1 se a árvore estiver vazia
int arv_vazia (Arvore* a);

// Indica a ocorrência (1) ou não (0) do ponto pelo nome
int arv_pertence (Arvore* a, char* nome);

//retorna a quantidade de folhas de uma arvore nao binaria
// Um nó é folha se ele não possui nenhum filho
int folhas (Arvore* a);

//retorna a altura da árvore a
int altura(Arvore* a);

// Retorna o ponteiro para o ponto armazenado no nó
Ponto *getPonto(Arvore *arvore);

// Libera o espaço de memória ocupado pela árvore
// Segue a lógica: libera o filho (e toda a subárvore dele) e depois o irmão
Arvore* arv_libera (Arvore* a);


#endif 