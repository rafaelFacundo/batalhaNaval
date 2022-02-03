#ifndef JOGABILIDADELIB
#define JOGABILIDADELIB
#include "matriz.h"




fieldNode *acharPosicaoDeUmNo( list *L, int numeroDaPosicao, int letraDaPosicao);

void colocarEmbarcacaoNaPosicao( list *L, int tipoDaEmbarcacao, int direcao );

void DarUmTiro( list *L );


#endif