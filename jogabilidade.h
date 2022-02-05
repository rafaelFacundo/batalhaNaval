#ifndef JOGABILIDADELIB
#define JOGABILIDADELIB
#include "matriz.h"




fieldNode *acharPosicaoDeUmNo( list *L, int numeroDaPosicao, int letraDaPosicao);

void colocarEmbarcacaoNaPosicao( list *L, int tipoDaEmbarcacao, int direcao,  int numeroDaPosicao, int letraDaPosicao);

void DarUmTiro( list *L, list *listaAtirador, int numero, int letra);

void verificarOsDanosDoTiro( list *L, list *listaAtidador,fieldNode *noAtingido );


#endif