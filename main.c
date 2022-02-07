#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "jogabilidade.h"
#include "controlarOJogo.h"

//Integrantes da equipe - 
//Addson Vinicyus - matricula - 512178
//Responsável por:
//    JogadaPc.c
//    verificarDanosDosTiros, DarUmTiro(Jogabilidade.c)

//Rafael Facundo da Costa - matricula - 511798
//Responsável por: 
//    Criartubuleiro.c 
//    Achar a posição de um no, colocarEmbarcação na posição,(jogabilidade.c)

//Carla Suenne Barbosa da Silva - matricula - 508373
//Responsável por: 
//    CotrolarOJogo.c 
//    distribuirBarcosAleatorios, distribuirBarcosAleatoriosComputador(Jogabilidade.c)

int main () {
    list *L;
    list *TabuleiroComputador;
    jogador *player;
    jogador *computador;
    int resposta = 1;
    player = malloc(sizeof(jogador));
    computador = malloc(sizeof(jogador));

    


    L = createList();
    TabuleiroComputador = createList();
    
    player->totalDeEmbarcacoes = 8;
    player->tipoDeJogador = JOGADOR;
    player->submarino1 = NULL;
    player->submarino2 = NULL;

    computador->totalDeEmbarcacoes = 8;
    player->tipoDeJogador = COMPUTADOR;
    computador->submarino1 = NULL;
    computador->submarino2 = NULL;

    L->donoDoTabuleiro = player;
    TabuleiroComputador->donoDoTabuleiro = computador;

    
     

    assembleTheLetterList(L);

    linkVerticalLists(L);

    assembleTheLetterList(TabuleiroComputador);

    linkVerticalLists(TabuleiroComputador);

    distribuirBarcosAleatorios(L);

    distribuirBarcosAleatoriosComputador(TabuleiroComputador);

    while ( resposta == 1 ) {
      resposta =  chamaRodadas(L, TabuleiroComputador);
    };

   
    
   
    

    return 0;
}