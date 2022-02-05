#include <stdio.h>
#include <stdlib.h>
#include "jogabilidade.h"


// essa função acha uma posição no tabuleiro e retorna o ponteiro para ela 
// basicamente ela recebe o numero e a letra
//entra na lista de letras que fica na parte de cima do tabuleiro
//"anda" até chegar no nó que a letra é igual a passada no parâmetro 
// depois desce numeroDaPosicao vezes até chegar na posição do número

fieldNode *acharPosicaoDeUmNo( list *L, int numeroDaPosicao, int letraDaPosicao) {
    letterNode *auxParaAcharLetra;
    fieldNode *auxParaDescerAteAPosicao;
    int k = 0;

    auxParaAcharLetra = L->firstNode;

    while ( auxParaAcharLetra->information[0] != letraDaPosicao ) { 
        auxParaAcharLetra = auxParaAcharLetra->prox;
    }

    auxParaDescerAteAPosicao = auxParaAcharLetra->down;
    
    while (k < numeroDaPosicao ) {
        auxParaDescerAteAPosicao = auxParaDescerAteAPosicao->down;
        k += 1;
    };

    //(*(char*)auxParaDescerAteAPosicao->info) = 'x';

    return auxParaDescerAteAPosicao;

};


//essa função dar o tiro 
// ela pergunta qual a casa que o jogador quer acertar 
// depois chama a função de achar a casa
// após isso ela verifica se a casa escolhida 
//tem alguma embarcação ou só tem água 
void DarUmTiro( list *L, list *listaAtirador, int numero, int letra ) {
    fieldNode *ponteiroComAposicao;
    int numeroDaPosicaoDesejada;
    int letraDaPosicaoDesejada;
    int k = 0;
    char jogadaDoJogador[4];

    //printf("Vamos lá marujo, diga a posição que você quer atigir: ");
    //scanf("%s", jogadaDoJogador);
    
   /*  while ( k < 4 ) {
    
        k += 1;
    } */

    ponteiroComAposicao = acharPosicaoDeUmNo(L, numero, letra);

    printf("o tipo do barco é %d\n", ponteiroComAposicao->oqueTemNesseNo);
    printf("a direção do barco é %d\n", ponteiroComAposicao->direcao);

    if ( ponteiroComAposicao->oqueTemNesseNo == AGUA) {
        *((char*)ponteiroComAposicao->info) = 'O';
    }else {
        *((char*)ponteiroComAposicao->info) = '*';
        verificarOsDanosDoTiro( L, listaAtirador, ponteiroComAposicao );
    }

     

};


 /* DESTROYER 2
 SUBMARINO 3
 FRAGATAS 4 
 PORTA_AVIAO  */



void colocarEmbarcacaoNaPosicao( list *L, int tipoDaEmbarcacao, int direcao,  int numeroDaPosicao, int letraDaPosicao ) {
    fieldNode *posicaoOndeColocarOBarco;

    
    posicaoOndeColocarOBarco = acharPosicaoDeUmNo( L, numeroDaPosicao, letraDaPosicao );
    int k =0;

  
    posicaoOndeColocarOBarco->direcao = direcao;

    if ( tipoDaEmbarcacao == JANGADA ) {
        *((char*)posicaoOndeColocarOBarco->info) = '&';
        posicaoOndeColocarOBarco->oqueTemNesseNo = JANGADA;
    }else if ( tipoDaEmbarcacao == SUBMARINO ) {
        *((char*)posicaoOndeColocarOBarco->info) = '@';
        posicaoOndeColocarOBarco->oqueTemNesseNo = SUBMARINO;

        if (L->donoDoTabuleiro->submarino1 != NULL) {
            L->donoDoTabuleiro->submarino2 = posicaoOndeColocarOBarco;
        }else {
            L->donoDoTabuleiro->submarino1 = posicaoOndeColocarOBarco;
        }
        
    }else if (tipoDaEmbarcacao == FRAGATAS) {
        while ( k < 2 ) {
            if (k == 0) {
                
                if (direcao == VERTICAL) {
                    *((char*)posicaoOndeColocarOBarco->info) = '^';
                }else {
                    *((char*)posicaoOndeColocarOBarco->info) = '<';
                }
                
            }else {
                *((char*)posicaoOndeColocarOBarco->info) = '>';
                 if (direcao == VERTICAL) {
                    *((char*)posicaoOndeColocarOBarco->info) = 'v';
                }else {
                    *((char*)posicaoOndeColocarOBarco->info) = '>';
                }
            }
            posicaoOndeColocarOBarco->direcao = direcao;
            posicaoOndeColocarOBarco->oqueTemNesseNo = FRAGATAS;
            if(direcao == VERTICAL) {
                posicaoOndeColocarOBarco = posicaoOndeColocarOBarco->down;
            }else {
                posicaoOndeColocarOBarco = posicaoOndeColocarOBarco->right;
            }
            k += 1;
        }
        k = 0;
    }else if ( tipoDaEmbarcacao == DESTROYER )  {
        while ( k < 3 ) {
            if (k == 0) {
                
                if (direcao == VERTICAL) {
                    *((char*)posicaoOndeColocarOBarco->info) = '^';
                }else {
                    *((char*)posicaoOndeColocarOBarco->info) = '<';
                }
                
            }else if (k == 1) {
                *((char*)posicaoOndeColocarOBarco->info) = '#';
            }else {
                *((char*)posicaoOndeColocarOBarco->info) = '>';
                 if (direcao == VERTICAL) {
                    *((char*)posicaoOndeColocarOBarco->info) = 'v';
                }else {
                    *((char*)posicaoOndeColocarOBarco->info) = '>';
                }
            }
            posicaoOndeColocarOBarco->direcao = direcao;
            posicaoOndeColocarOBarco->oqueTemNesseNo = DESTROYER;
            if(direcao == VERTICAL) {
                posicaoOndeColocarOBarco = posicaoOndeColocarOBarco->down;
            }else {
                posicaoOndeColocarOBarco = posicaoOndeColocarOBarco->right;
            }
            k += 1;
        }
        k = 0;
    }else {
          while ( k < 5 ) {
            if (k == 0) {
                *((char*)posicaoOndeColocarOBarco->info) = '<';
            }else if (k >= 1 && k <= 3 ) {
                *((char*)posicaoOndeColocarOBarco->info) = '#';
            }else {
                *((char*)posicaoOndeColocarOBarco->info) = '>';
            }
            posicaoOndeColocarOBarco->direcao = direcao;
            posicaoOndeColocarOBarco->oqueTemNesseNo = PORTA_AVIAO;
            if(direcao == VERTICAL) {
                posicaoOndeColocarOBarco = posicaoOndeColocarOBarco->down;
            }else {
                posicaoOndeColocarOBarco = posicaoOndeColocarOBarco->right;
            }
            k += 1;
        }
    }

};


void verificarOsDanosDoTiro( list *L, list *listaAtidador, fieldNode *noAtingido ) {
    int k = 0;

    if ( noAtingido->oqueTemNesseNo == JANGADA ) {
        if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
            printf("O jogador afundou uma jaganda do computador.\n");
            printf("Como penalidade perderá um submarino, caso ainda tenha um.\n");
        }else {
            printf("O computador afundou uma jaganda do jogador.\n");
            printf("Como penalidade perderá um submarino, caso ainda tenha um.\n");
        }
        L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;
        listaAtidador->donoDoTabuleiro->submarino -= 1;
        listaAtidador->donoDoTabuleiro->totalDeEmbarcacoes -= 1;
        if ( listaAtidador->donoDoTabuleiro->submarino1 != NULL ) {
            *((char*)listaAtidador->donoDoTabuleiro->submarino1->info) = '*';
            listaAtidador->donoDoTabuleiro->submarino -= 1;
            listaAtidador->donoDoTabuleiro->submarino1 = NULL;
        }else if (listaAtidador->donoDoTabuleiro->submarino2 != NULL) {
            *((char*)listaAtidador->donoDoTabuleiro->submarino1->info) = '*';
            
        }

    }else if ( noAtingido->oqueTemNesseNo == SUBMARINO ) {
        if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
            printf("O jogador afundou um submarino do computador.\n");
           
        }else {
            printf("O computador afundou um submarino do jogador.\n");
            
        }
         L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;
    }else {
        switch (noAtingido->oqueTemNesseNo) {
            case FRAGATAS:
                if ( noAtingido->direcao == VERTICAL ){
                    if ( noAtingido->up->oqueTemNesseNo != FRAGATAS && *((char*)noAtingido->down->info) == '*' ) {
                        L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                        if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                            printf("O jogador afundou uma Fragata do computador.\n");
                        }else {
                            printf("O computador afundou uma Fragata do jogador.\n");
                        }
                    }else if (noAtingido->down->oqueTemNesseNo != FRAGATAS && *((char*)noAtingido->up->info) == '*' ) {
                        L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                        if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                            printf("O jogador afundou uma Fragata do computador.\n");
                        }else {
                            printf("O computador afundou uma Fragata do jogador.\n");
                        }
                    }
                }else {

                     if ( noAtingido->left->oqueTemNesseNo != FRAGATAS && *((char*)noAtingido->right->info) == '*' ) {
                        L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                        if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                            printf("O jogador afundou uma Fragata do computador.\n");
                        }else {
                            printf("O computador afundou uma Fragata do jogador.\n");
                        }
                    }else if (noAtingido->right->oqueTemNesseNo != FRAGATAS && *((char*)noAtingido->left->info) == '*' ) {
                        L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                        if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                            printf("O jogador afundou uma Fragata do computador.\n");
                        }else {
                            printf("O computador afundou uma Fragata do jogador.\n");
                        }
                    }
                }
                break;
            case DESTROYER:
                if ( noAtingido->direcao == VERTICAL ) {
                    
                    if ( noAtingido->up->oqueTemNesseNo == DESTROYER && *((char*)noAtingido->up->info) == '*' ) {
                        if (noAtingido->down->oqueTemNesseNo == DESTROYER && *((char*)noAtingido->down->info) == '*') {
                            printf("aaa\n");
                            L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um destroyer do computador.\n");
                            }else {
                                printf("O computador afundou um destroyer do jogador.\n");
                            }
                        }
                    }else if ( noAtingido->up->oqueTemNesseNo == DESTROYER && noAtingido->up->up->oqueTemNesseNo == DESTROYER ) {
                       
                        if ( *((char*)noAtingido->up->info) == '*' && *((char*)noAtingido->up->up->info) == '*') {
                             L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um destroyer do computador.\n");
                            }else {
                                printf("O computador afundou um destroyer do jogador.\n");
                            }
                        }
                    }else {
                        if ( *((char*)noAtingido->down->info) == '*' && *((char*)noAtingido->down->down->info) == '*') {
                             L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um destroyer do computador.\n");
                            }else {
                                printf("O computador afundou um destroyer do jogador.\n");
                            }
                        }
                    }

                }else {
                    printf("afddfddfdf\n");
                    if ( noAtingido->right->oqueTemNesseNo == DESTROYER && *((char*)noAtingido->right->info) == '*' ) {
                        if (noAtingido->left->oqueTemNesseNo == DESTROYER && *((char*)noAtingido->left->info) == '*') {
                            L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um destroyer do computador.\n");
                            }else {
                                printf("O computador afundou um destroyer do jogador.\n");
                            }
                        }
                    }else if ( noAtingido->right->oqueTemNesseNo == DESTROYER && noAtingido->right->right->oqueTemNesseNo == DESTROYER ) {
                        if ( *((char*)noAtingido->right->info) == '*' && *((char*)noAtingido->right->right->info) == '*') {
                             L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um destroyer do computador.\n");
                            }else {
                                printf("O computador afundou um destroyer do jogador.\n");
                            }
                        }
                    }else {
                        if ( *((char*)noAtingido->left->info) == '*' && *((char*)noAtingido->left->left->info) == '*') {
                             L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um destroyer do computador.\n");
                            }else {
                                printf("O computador afundou um destroyer do jogador.\n");
                            }
                        }
                    }
                }
            case PORTA_AVIAO:
                if ( noAtingido->direcao == VERTICAL ) {
                    if ( noAtingido->up->oqueTemNesseNo != PORTA_AVIAO ) {
                        while ( *((char*)noAtingido->info) == '*' && noAtingido->oqueTemNesseNo == PORTA_AVIAO && k < 4) {
                            noAtingido = noAtingido->down;
                            k += 1;
                        }

                        if ( k == 4) {
                            L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um Porta aviões do computador.\n");
                            }else {
                                printf("O computador afundou um Porta aviões do jogador.\n");
                            }
                        }
                    }else if (noAtingido->down->oqueTemNesseNo != PORTA_AVIAO) {

                        while ( *((char*)noAtingido->info) == '*' && noAtingido->oqueTemNesseNo == PORTA_AVIAO && k < 4) {
                            noAtingido = noAtingido->up;
                            k += 1;
                        }

                        if ( k == 4 ) {
                            L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um Porta aviões do computador.\n");
                            }else {
                                printf("O computador afundou um Porta aviões do jogador.\n");
                            }
                        }
                    }else if ( noAtingido->up->oqueTemNesseNo == PORTA_AVIAO && noAtingido->up->up->oqueTemNesseNo != PORTA_AVIAO ) {
                        noAtingido = noAtingido->up;
                        while ( *((char*)noAtingido->info) == '*' && noAtingido->oqueTemNesseNo == PORTA_AVIAO && k < 4) {
                            noAtingido = noAtingido->down;
                            k += 1;
                        }

                        if ( k == 4) {
                            L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um Porta aviões do computador.\n");
                            }else {
                                printf("O computador afundou um Porta aviões do jogador.\n");
                            }
                        }
                    }else if ( noAtingido->down->oqueTemNesseNo == PORTA_AVIAO && noAtingido->down->down->oqueTemNesseNo != PORTA_AVIAO ) {
                        noAtingido = noAtingido->down;
                        while ( *((char*)noAtingido->info) == '*' && noAtingido->oqueTemNesseNo == PORTA_AVIAO && k < 4) {
                            noAtingido = noAtingido->up;
                        }

                        if ( k == 4 ) {
                            L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um Porta aviões do computador.\n");
                            }else {
                                printf("O computador afundou um Porta aviões do jogador.\n");
                            }
                        }
                    }else {
                        noAtingido = noAtingido->up->up;
                        while ( *((char*)noAtingido->info) == '*' && noAtingido->oqueTemNesseNo == PORTA_AVIAO && k < 4) {
                            noAtingido = noAtingido->down;
                        }

                        if ( k == 4 ) {
                            L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um Porta aviões do computador.\n");
                            }else {
                                printf("O computador afundou um Porta aviões do jogador.\n");
                            }
                        }
                    }
                }else {
                    if ( noAtingido->right->oqueTemNesseNo != PORTA_AVIAO ) {
                        while ( *((char*)noAtingido->info) == '*' && noAtingido->oqueTemNesseNo == PORTA_AVIAO && k < 4) {
                            noAtingido = noAtingido->left;
                            k += 1;
                        }

                        if ( k == 4) {
                            L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um Porta aviões do computador.\n");
                            }else {
                                printf("O computador afundou um Porta aviões do jogador.\n");
                            }
                        }
                    }else if (noAtingido->left->oqueTemNesseNo != PORTA_AVIAO) {

                        while ( *((char*)noAtingido->info) == '*' && noAtingido->oqueTemNesseNo == PORTA_AVIAO && k < 4) {
                            noAtingido = noAtingido->right;
                            k += 1;
                        }

                        if ( k == 4 ) {
                            L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um Porta aviões do computador.\n");
                            }else {
                                printf("O computador afundou um Porta aviões do jogador.\n");
                            }
                        }
                    }else if ( noAtingido->left->oqueTemNesseNo == PORTA_AVIAO && noAtingido->left->left->oqueTemNesseNo != PORTA_AVIAO ) {
                        noAtingido = noAtingido->left;
                        while ( *((char*)noAtingido->info) == '*' && noAtingido->oqueTemNesseNo == PORTA_AVIAO && k < 4) {
                            noAtingido = noAtingido->right;
                            k += 1;
                        }

                        if ( k == 4) {
                            L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um Porta aviões do computador.\n");
                            }else {
                                printf("O computador afundou um Porta aviões do jogador.\n");
                            }
                        }
                    }else if ( noAtingido->right->oqueTemNesseNo == PORTA_AVIAO && noAtingido->right->right->oqueTemNesseNo != PORTA_AVIAO ) {
                        noAtingido = noAtingido->right;
                        while ( *((char*)noAtingido->info) == '*' && noAtingido->oqueTemNesseNo == PORTA_AVIAO && k < 4) {
                            noAtingido = noAtingido->left;
                        }

                        if ( k == 4 ) {
                            L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um Porta aviões do computador.\n");
                            }else {
                                printf("O computador afundou um Porta aviões do jogador.\n");
                            }
                        }
                    }else {
                        noAtingido = noAtingido->right->right;
                        while ( *((char*)noAtingido->info) == '*' && noAtingido->oqueTemNesseNo == PORTA_AVIAO && k < 4) {
                            noAtingido = noAtingido->left;
                        }

                        if ( k == 4 ) {
                            L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;

                            if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
                                printf("O jogador afundou um Porta aviões do computador.\n");
                            }else {
                                printf("O computador afundou um Porta aviões do jogador.\n");
                            }
                        }
                    }
                }
                
            default:
                break;
        }
       
    }

    
}; 