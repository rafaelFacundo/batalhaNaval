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
void DarUmTiro( list *L ) {
    letterNode *ponteiroParaAcharPosicao;
    fieldNode *ponteiroComAposicao;
    int numeroDaPosicaoDesejada;
    int letraDaPosicaoDesejada;
    int k = 0;
    char jogadaDoJogador[4];

    printf("Vamos lá marujo, diga a posição que você quer atigir: ");
    scanf("%s", jogadaDoJogador);
    
    while ( k < 4 ) {
        if ( jogadaDoJogador[k] >= '0' ||   jogadaDoJogador[k] <= '9') {
            
        }

        k += 1;
    }

};

