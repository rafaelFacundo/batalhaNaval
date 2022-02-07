#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
int DarUmTiro( list *L, list *listaAtirador, int numero, int letra ) {
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

    

    if ( ponteiroComAposicao->oqueTemNesseNo == AGUA) {
        *((char*)ponteiroComAposicao->info) = 'O';
        ponteiroComAposicao->podeMostrar = 1;
    }else {
        *((char*)ponteiroComAposicao->info) = '*';
        ponteiroComAposicao->podeMostrar = 1;
        k = verificarOsDanosDoTiro( L, listaAtirador, ponteiroComAposicao );
    }

    return k;

};



/* essa função basicamente recebe o tipo da embarcação que vai ser colcodo 
a direcão e o numero e a letra da posição 
ela chama a função de achar a posição 
pega o ponteiro que foi retornado por essa função 
e ela sempre coloca da direta pra esquerda ou de cima pra baixo 
além disso ela verifica a direção para mudar os caracteres '^' '>' '<' 'V' 
pra cada embarcação ela entra no while que roda o numero do tamanho da embarcação 
e coloca o tipo de embarcação na direção especificada 
para "colocar" oque ela faz é mudar oque está escrito no nó para a representação da embarcação 
*/

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


/* essa função verifica se o tiro acertou uma embarcação 
se foi JANGADA retorna 0 senão retorna 1
ela pega o ponteiro do no atingido 
e verifica qual o tipo se foi jangada faz oque foi especificado no trabalho 
se foi outro tipo de embarcação ela vai verificar 
se já foi afundado 
se foi ela tira os pontos de quem perdeu a embarcação 
e diz quem afundou 
ela faz isso assim :
para verificar se já foi atingido ela olha se oq tem escrito é o caractere "*"
ela olha qual o tipo de embarcação 
se for submarino já afundou pois só tem uma casa 
se for fragata que tem duas casas 
ele verifica se o no atingido é o da esquerda ou da direita 
se for da esquerda ela olha se o da direita já foi atingido 
    se  atingida foi ela tira os pontos de quem perdeu e diz quem afundou 
se foi da direita ela repete a mesma coisa acima só trocando as posições 
se for destroyer que tem 3 casas 
ela verifica se o no atingido foi das pontas ou do meio 
se foi de uma ponto ela olha se os proximos dois foram atingidos 
se for do meio ela olha se os dois de cada lado foram atingidos 
     se atingida  foi ela tira os pontos de quem perdeu e diz quem afundou
se for um porta aviões
ela olha se o no atingido foi de uma das pontas 
se foi ela "anda" com um while(que roda 5 vezes, o tamanho do barco) até a outra ponto verificando
se todas as outras posições foram atingidas 
se o no for um no do meio 
ela anda até encontrar uma ponta, depois repete o que foi citado acima, anda até a outra ponto verificando 
      se  atingida foi ela tira os pontos de quem perdeu e diz quem afundou */


int verificarOsDanosDoTiro( list *L, list *listaAtidador, fieldNode *noAtingido ) {
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
        
        listaAtidador->donoDoTabuleiro->totalDeEmbarcacoes -= 1;
        if ( listaAtidador->donoDoTabuleiro->submarino1 != NULL ) {
            *((char*)listaAtidador->donoDoTabuleiro->submarino1->info) = '*';
            
            listaAtidador->donoDoTabuleiro->submarino1 = NULL;
        }else if (listaAtidador->donoDoTabuleiro->submarino2 != NULL) {
            *((char*)listaAtidador->donoDoTabuleiro->submarino1->info) = '*';
            
        }
        return 0;
    }else if ( noAtingido->oqueTemNesseNo == SUBMARINO ) {
        
        if ( listaAtidador->donoDoTabuleiro->tipoDeJogador == JOGADOR ) {
            printf("O jogador afundou um submarino do computador.\n");
           
        }else {
            printf("O computador afundou um submarino do jogador.\n");
            
        }
        L->donoDoTabuleiro->totalDeEmbarcacoes -= 1;
        return 1;
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
                return 1;
                break;
            case DESTROYER:
                if ( noAtingido->direcao == VERTICAL ) {
                    
                    if ( noAtingido->up->oqueTemNesseNo == DESTROYER && *((char*)noAtingido->up->info) == '*' ) {
                        if (noAtingido->down->oqueTemNesseNo == DESTROYER && *((char*)noAtingido->down->info) == '*') {
                            
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
                return 1;
                break;
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
                return 1;
                break;
            default:
                return 0;
                break;
        }
       
    }

    
}; 


/* essa função gera as posiçãoes aleatorias dos barcos 
ela usa srand e rand 
e oq ela faz é 
primeiro ela coloca o porta aviões q é o maior logo já limitamos o intervalo para que não bata nas bordas
colocamos na ordem porta aviao, destroyer, fragata, submarino e jangada 
cada um deles limitamos o intervalo em que pode ser gerados as casas para que não bata na borda
assim apos isso geramos um valor para decidir se o barco vai ficar na HORIZONTAL ou VERTICAL
depois geramos um valor para pegar uma letra correspondente na arrays de letras disponiveis 
apos isso chamamos a função de achar posição 
pegamos o ponteiro que ela retorna e entramos em um while para vericar 
se a quandidade de casas necessarias para incluir a embarcação está disponivel ou se ja tem outra embarcação 
o while roda até a variavel j seja igual o numero de vezes do tamanho da embarcação e 
que oque esteja no no seja agua 
ou seja, se o j chegar até o numero igual o tamanho da embarcação signfica que 
apartir da posição que geramos temos o numero de casa necessarias para colocar essa embarcação lá 
verificamos isso em um if e se for verdadeiro chamaos a função de colcoar um barco no tabuleiro */


void distribuirBarcosAleatorios (list *L) {
    char letras[12] = {'A','B', 'C', 'D', 'E', 'F','G','H','I','J','K','L'};
    fieldNode *posicaoQVaiColocar;
    int k = 0;
    int j = 0;
    int p = 0;
    int numeroDeBarcosGerados = 0;
    int letraPosicao;
    int numeroPosicao;
    int direcao;

    srand(time(NULL));

  
 
    while ( numeroDeBarcosGerados < 9 ) {
       
        
        if (numeroDeBarcosGerados == 0) {


            k = (rand() % 9) + 1;
            if ( k >= 1 && k <= 5) {
                direcao = VERTICAL;
            }else {
                direcao = HORIZONTAL;
            }
            
            letraPosicao = (rand() % 6) + 1;
            numeroPosicao = (rand() % 6) + 1;
            letraPosicao = letras[letraPosicao];
            posicaoQVaiColocar = acharPosicaoDeUmNo(L, numeroPosicao, letraPosicao);
            while ( j < 5 && posicaoQVaiColocar->oqueTemNesseNo == AGUA ) {
                
                if ( direcao == VERTICAL ) {
                    posicaoQVaiColocar = posicaoQVaiColocar->down;
                }else {
                    posicaoQVaiColocar = posicaoQVaiColocar->right;
                }
                j += 1;
            }
            if (j == 5) {
                colocarEmbarcacaoNaPosicao(L, PORTA_AVIAO, direcao, numeroPosicao, letraPosicao);
                numeroDeBarcosGerados += 1 ;
                
            }

            
        }else if (numeroDeBarcosGerados == 1) {
            j = 0;
            p = 0;
            while (p < 2) {


                k = (rand() % 9) + 1;
                if ( k >= 1 && k <= 5) {
                    direcao = VERTICAL;
                }else {
                    direcao = HORIZONTAL;
                }
               

                letraPosicao = (rand() % 9) + 1;
                numeroPosicao = (rand() % 9) + 1;
                letraPosicao = letras[letraPosicao];
                posicaoQVaiColocar = acharPosicaoDeUmNo(L, numeroPosicao, letraPosicao);
                while ( j < 3 && posicaoQVaiColocar->oqueTemNesseNo == AGUA ) {
                   
                    if ( direcao == VERTICAL ) {
                        posicaoQVaiColocar = posicaoQVaiColocar->down;
                    }else {
                        posicaoQVaiColocar = posicaoQVaiColocar->right;
                    }
                    j += 1;
                }
                if (j == 3) {
                    colocarEmbarcacaoNaPosicao(L, DESTROYER, direcao, numeroPosicao, letraPosicao);
                    p += 1;
                    numeroDeBarcosGerados +=1;
                }
                j = 0;
            }
        }else if (numeroDeBarcosGerados == 3) {
            j = 0;
            p = 0;
            while (p < 3) {


                k = (rand() % 9) + 1;
                if ( k >= 1 && k <= 5) {
                    direcao = VERTICAL;
                }else {
                    direcao = HORIZONTAL;
                }


               
                letraPosicao = (rand() % 9) + 1;
                numeroPosicao = (rand() % 9) + 1;
                letraPosicao = letras[letraPosicao];
                posicaoQVaiColocar = acharPosicaoDeUmNo(L, numeroPosicao, letraPosicao);
                while ( j < 3 && posicaoQVaiColocar->oqueTemNesseNo == AGUA ) {
                   
                    if ( direcao == VERTICAL ) {
                        posicaoQVaiColocar = posicaoQVaiColocar->down;
                    }else {
                        posicaoQVaiColocar = posicaoQVaiColocar->right;
                    }
                    j += 1;
                }
                if (j == 3) {
                    colocarEmbarcacaoNaPosicao(L, FRAGATAS, direcao, numeroPosicao, letraPosicao);
                    p += 1;
                    numeroDeBarcosGerados +=1;
                }
                j = 0;
            
            }   
            
        } else if (numeroDeBarcosGerados == 6) {
            j = 0;
            p = 0;
            while (p < 2) {

                k = (rand() % 9) + 1;
                if ( k >= 1 && k <= 5) {
                    direcao = VERTICAL;
                }else {
                    direcao = HORIZONTAL;
                }
                
                letraPosicao = (rand() % 9) + 1;
                numeroPosicao = (rand() % 9) + 1;
                letraPosicao = letras[letraPosicao];
                posicaoQVaiColocar = acharPosicaoDeUmNo(L, numeroPosicao, letraPosicao);
              
                if ( posicaoQVaiColocar->oqueTemNesseNo == AGUA ) {
                    colocarEmbarcacaoNaPosicao(L, SUBMARINO, direcao, numeroPosicao, letraPosicao);
                    p += 1;
                    numeroDeBarcosGerados +=1;
                }

            }
        }else {
                k = (rand() % 9) + 1;
                if ( k >= 1 && k <= 5) {
                    direcao = VERTICAL;
                }else {
                    direcao = HORIZONTAL;
                }


                letraPosicao = (rand() % 9) + 1;
                numeroPosicao = (rand() % 9) + 1;
                letraPosicao = letras[letraPosicao];
                posicaoQVaiColocar = acharPosicaoDeUmNo(L, numeroPosicao, letraPosicao);
              
                if ( posicaoQVaiColocar->oqueTemNesseNo == AGUA ) {
                    colocarEmbarcacaoNaPosicao(L, JANGADA, direcao, numeroPosicao, letraPosicao);
                    p += 1;
                    numeroDeBarcosGerados +=1;
                }
        }
       
    }
}; 


/* tem a mesma função da anterior 
e funciona da mesma maneira 
só muda os intervalos 
que são intervalos equivalentes
só para garantir que o pc não esteja gerando os mesmos valores
para o jogador e para o pc  */

void distribuirBarcosAleatoriosComputador (list *L) {
    char letras[12] = {'A','B', 'C', 'D', 'E', 'F','G','H','I','J','K','L'};
    fieldNode *posicaoQVaiColocar;
    int k = 0;
    int j = 0;
    int p = 0;
    int numeroDeBarcosGerados = 0;
    int letraPosicao;
    int numeroPosicao;
    int direcao;

    srand(time(NULL));

  
 
    while ( numeroDeBarcosGerados < 9 ) {
       
        
        if (numeroDeBarcosGerados == 0) {


            k = (rand() % 9) + 1;
            if ( k >= 1 && k <= 5) {
                direcao = VERTICAL;
            }else {
                direcao = HORIZONTAL;
            }
            
            letraPosicao = (rand() % 5) + 2;
            numeroPosicao = (rand() % 5) + 2;
            letraPosicao = letras[letraPosicao];
            posicaoQVaiColocar = acharPosicaoDeUmNo(L, numeroPosicao, letraPosicao);
            while ( j < 5 && posicaoQVaiColocar->oqueTemNesseNo == AGUA ) {
                
                if ( direcao == VERTICAL ) {
                    posicaoQVaiColocar = posicaoQVaiColocar->down;
                }else {
                    posicaoQVaiColocar = posicaoQVaiColocar->right;
                }
                j += 1;
            }
            if (j == 5) {
                colocarEmbarcacaoNaPosicao(L, PORTA_AVIAO, direcao, numeroPosicao, letraPosicao);
                numeroDeBarcosGerados += 1 ;
                
            }

            
        }else if (numeroDeBarcosGerados == 1) {
            j = 0;
            p = 0;
            while (p < 2) {


                k = (rand() % 8) + 2;
                if ( k >= 1 && k <= 5) {
                    direcao = VERTICAL;
                }else {
                    direcao = HORIZONTAL;
                }
               

                letraPosicao = (rand() % 7) + 3;
                numeroPosicao = (rand() % 6) + 3;
                letraPosicao = letras[letraPosicao];
                posicaoQVaiColocar = acharPosicaoDeUmNo(L, numeroPosicao, letraPosicao);
                while ( j < 3 && posicaoQVaiColocar->oqueTemNesseNo == AGUA ) {
                   
                    if ( direcao == VERTICAL ) {
                        posicaoQVaiColocar = posicaoQVaiColocar->down;
                    }else {
                        posicaoQVaiColocar = posicaoQVaiColocar->right;
                    }
                    j += 1;
                }
                if (j == 3) {
                    colocarEmbarcacaoNaPosicao(L, DESTROYER, direcao, numeroPosicao, letraPosicao);
                    p += 1;
                    numeroDeBarcosGerados +=1;
                }
                j = 0;
            }
        }else if (numeroDeBarcosGerados == 3) {
            j = 0;
            p = 0;
            while (p < 3) {


                k = (rand() % 9) + 1;
                if ( k >= 1 && k <= 5) {
                    direcao = VERTICAL;
                }else {
                    direcao = HORIZONTAL;
                }


               
                letraPosicao = (rand() % 8) + 2;
                numeroPosicao = (rand() % 8) + 2;
                letraPosicao = letras[letraPosicao];
                posicaoQVaiColocar = acharPosicaoDeUmNo(L, numeroPosicao, letraPosicao);
                while ( j < 4 && posicaoQVaiColocar->oqueTemNesseNo == AGUA ) {
                   
                    if ( direcao == VERTICAL ) {
                        posicaoQVaiColocar = posicaoQVaiColocar->down;
                    }else {
                        posicaoQVaiColocar = posicaoQVaiColocar->right;
                    }
                    j += 1;
                }
                if (j == 4) {
                    colocarEmbarcacaoNaPosicao(L, FRAGATAS, direcao, numeroPosicao, letraPosicao);
                    p += 1;
                    numeroDeBarcosGerados +=1;
                }
                j = 0;
            
            }   
            
        } else if (numeroDeBarcosGerados == 6) {
            j = 0;
            p = 0;
            while (p < 2) {

                k = (rand() % 8) + 2;
                if ( k >= 1 && k <= 5) {
                    direcao = VERTICAL;
                }else {
                    direcao = HORIZONTAL;
                }
                
                letraPosicao = (rand() % 8) + 2;
                numeroPosicao = (rand() % 8) + 2;
                letraPosicao = letras[letraPosicao];
                posicaoQVaiColocar = acharPosicaoDeUmNo(L, numeroPosicao, letraPosicao);
              
                if ( posicaoQVaiColocar->oqueTemNesseNo == AGUA ) {
                    colocarEmbarcacaoNaPosicao(L, SUBMARINO, direcao, numeroPosicao, letraPosicao);
                    p += 1;
                    numeroDeBarcosGerados +=1;
                }
            }
        }else {
                k = (rand() % 9) + 1;
                if ( k >= 1 && k <= 5) {
                    direcao = VERTICAL;
                }else {
                    direcao = HORIZONTAL;
                }


                letraPosicao = (rand() % 8) + 2;
                numeroPosicao = (rand() % 8) + 2;
                letraPosicao = letras[letraPosicao];
                posicaoQVaiColocar = acharPosicaoDeUmNo(L, numeroPosicao, letraPosicao);
              
                if ( posicaoQVaiColocar->oqueTemNesseNo == AGUA ) {
                    colocarEmbarcacaoNaPosicao(L, JANGADA, direcao, numeroPosicao, letraPosicao);
                    p += 1;
                    numeroDeBarcosGerados +=1;
                }
        }
       
    }
}; 