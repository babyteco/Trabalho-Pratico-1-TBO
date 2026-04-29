#ifndef PONTO_h
#define PONTO_h
#include <stdio.h>

typedef struct ponto Ponto;

Ponto *cria_ponto(char* nome, int m, double* coordenadas);

char* get_nome_ponto(Ponto *p);

void imprime_ponto(Ponto* p);

void liberaPonto(Ponto *p);

#endif
