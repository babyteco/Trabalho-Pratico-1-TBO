#ifndef PONTO_h
#define PONTO_h
#include <stdio.h>

typedef struct ponto Ponto;

Ponto* lerPontos(char *nomeArquivo, int *qtd);

void liberaPonto(Ponto *p);

#endif
