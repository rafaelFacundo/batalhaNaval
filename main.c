#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "jogabilidade.h"

int main () {
    list *L;
    list *TabuleiroComputador;
    jogador *player;
    jogador *computador;
    player = malloc(sizeof(jogador));
    computador = malloc(sizeof(jogador));

    player->totalDeEmbarcacoes = 9;
    player->submarino = 2;
    player->jangada = 1;
    player->fragata = 3;
    player->portaAviao = 1;
    player->destroyer = 2;
    player->tipoDeJogador = JOGADOR;
    player->submarino1 = NULL;
    player->submarino2 = NULL;

    computador->totalDeEmbarcacoes = 9;
    computador->submarino = 2;
    computador->jangada = 1;
    computador->fragata = 3;
    computador->portaAviao = 1;
    computador->destroyer = 2;
    player->tipoDeJogador = COMPUTADOR;
    computador->submarino1 = NULL;
    computador->submarino2 = NULL;


    L = createList();
    TabuleiroComputador = createList();
    L->donoDoTabuleiro = player;
    TabuleiroComputador->donoDoTabuleiro = computador;

    

    assembleTheLetterList(L);

    linkVerticalLists(L);

    assembleTheLetterList(TabuleiroComputador);

    linkVerticalLists(TabuleiroComputador);
    


    
    
    //acharPosicaoDeUmNo(L, 4, 'F');

    colocarEmbarcacaoNaPosicao( TabuleiroComputador, PORTA_AVIAO , HORIZONTAL,  2, 'C');

    colocarEmbarcacaoNaPosicao( TabuleiroComputador, DESTROYER, VERTICAL,  4, 'K');

    colocarEmbarcacaoNaPosicao( TabuleiroComputador, FRAGATAS , HORIZONTAL,  10, 'G');

    colocarEmbarcacaoNaPosicao( TabuleiroComputador, JANGADA , HORIZONTAL,  12, 'A');

    colocarEmbarcacaoNaPosicao( TabuleiroComputador, SUBMARINO , HORIZONTAL,  11, 'J');

    //-----------------------------------------------------------------------------------------

    colocarEmbarcacaoNaPosicao( L, PORTA_AVIAO , HORIZONTAL,  2, 'C');

    colocarEmbarcacaoNaPosicao( L, DESTROYER, VERTICAL,  4, 'K');

    colocarEmbarcacaoNaPosicao( L, FRAGATAS , HORIZONTAL,  10, 'G');

    colocarEmbarcacaoNaPosicao( L, JANGADA , HORIZONTAL,  12, 'A');

    colocarEmbarcacaoNaPosicao( L, SUBMARINO , HORIZONTAL,  11, 'J');

    printList(TabuleiroComputador);

    printList(L);

    printf("-------------------------------------------------------------------\n");

    //---------------------------------------------------------------------------------------------

  /*   DarUmTiro( TabuleiroComputador, L, 5, 'K');

    DarUmTiro( TabuleiroComputador, L, 4, 'C');

    DarUmTiro( TabuleiroComputador, L, 5, 'F'); */

    DarUmTiro( TabuleiroComputador, L, 2, 'C');

    DarUmTiro( TabuleiroComputador, L, 2, 'D');

    DarUmTiro( TabuleiroComputador, L, 2, 'E');

    DarUmTiro( TabuleiroComputador, L, 2, 'F');

    DarUmTiro( TabuleiroComputador, L, 2, 'G');


    printList(TabuleiroComputador);

    printList(L);

    //DarUmTiro(L);

    
    

    return 0;
}