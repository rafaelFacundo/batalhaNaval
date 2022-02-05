#ifndef JOGABILIDADELIB
#define JOGABILIDADELIB
#include "matriz.h"




fieldNode *acharPosicaoDeUmNo( list *L, int numeroDaPosicao, int letraDaPosicao);

void colocarEmbarcacaoNaPosicao( list *L, int tipoDaEmbarcacao, int direcao,  int numeroDaPosicao, int letraDaPosicao);

int DarUmTiro( list *L, list *listaAtirador, int numero, int letra);

int verificarOsDanosDoTiro( list *L, list *listaAtidador,fieldNode *noAtingido );

void distribuirBarcosAleatorios (list *L);

void distribuirBarcosAleatoriosComputador (list *L);

#endif