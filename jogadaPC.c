#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogabilidade.h"
#include "matriz.h"
#include "jogadaPC.h"
#include "controlarOJogo.h"

int jogadaPC(list *TabuleiroComputador, list *L){
    fieldNode *ponteiroPosicao;
    int numero;
    int letra;
    int NumeroAnterior;
    int LetraAnterior;
    int direcao;
    int aux = 0;

//Gera um número e letra para a jogada aleatória do PC

    do{

        srand(time(NULL));

        numero = 1 + (rand() % 12);
        letra = 'A' + (char)(rand() % ('L' - 'A'));

        ponteiroPosicao = acharPosicaoDeUmNo(TabuleiroComputador, numero, letra);

    }while((NumeroAnterior == numero) && (LetraAnterior == letra));

    
    DarUmTiro(TabuleiroComputador, L, numero, letra);

//Depois do tiro, verifica a casa atingida 

    if(ponteiroPosicao->oqueTemNesseNo == AGUA){
        NumeroAnterior = numero;
        LetraAnterior = letra;

        return 1;
    }

    else if(ponteiroPosicao->oqueTemNesseNo == JANGADA){
        verificarOsDanosDoTiro(TabuleiroComputador, L, ponteiroPosicao);
        NumeroAnterior = numero;
        LetraAnterior = letra;

        return 1;
    }

    else if(ponteiroPosicao->oqueTemNesseNo == SUBMARINO){
        verificarOsDanosDoTiro(TabuleiroComputador, L, ponteiroPosicao);
        NumeroAnterior = numero;
        LetraAnterior = letra;

        return 0;
    }

    else if(ponteiroPosicao->oqueTemNesseNo == FRAGATAS){
        while(aux < 2){
            if(aux == 0 || aux == 1){
                *((char*)ponteiroPosicao->info) = '*';
            }

            ponteiroPosicao->oqueTemNesseNo = FRAGATAS;

            if(*((char*)ponteiroPosicao->up->info) == '^') {
                ponteiroPosicao = ponteiroPosicao->up;

            }else if(*((char*)ponteiroPosicao->down->info) == 'v') {
                ponteiroPosicao = ponteiroPosicao->down;

            }else if(*((char*)ponteiroPosicao->left->info) == '<') {
                ponteiroPosicao = ponteiroPosicao->left;

            }else if(*((char*)ponteiroPosicao->right->info) == '>') {
                ponteiroPosicao = ponteiroPosicao->right;
            }
            aux += 1;
        }
        aux = 0;

        return 0;
    }

    else if ( ponteiroPosicao->oqueTemNesseNo== DESTROYER )  {
        while ( aux < 3 ) {
            if (aux >= 0 || aux < 3 ) {
                *((char*)ponteiroPosicao->info) = '*';
            }

            ponteiroPosicao->oqueTemNesseNo = DESTROYER;

            if(*((char*)ponteiroPosicao->up->info) == '^') {
                ponteiroPosicao = ponteiroPosicao->up;

            }else if(*((char*)ponteiroPosicao->down->info) == 'v') {
                ponteiroPosicao = ponteiroPosicao->down;

            }else if(*((char*)ponteiroPosicao->left->info) == '<') {
                ponteiroPosicao = ponteiroPosicao->left;

            }else if(*((char*)ponteiroPosicao->right->info) == '>') {
                ponteiroPosicao = ponteiroPosicao->right;

            }else if(*((char*)ponteiroPosicao->up->info) == '#') {
                ponteiroPosicao = ponteiroPosicao->up;

            }else if(*((char*)ponteiroPosicao->down->info) == '#') {
                ponteiroPosicao = ponteiroPosicao->down;

            }else if(*((char*)ponteiroPosicao->left->info) == '#') {
                ponteiroPosicao = ponteiroPosicao->left;

            }else if(*((char*)ponteiroPosicao->right->info) == '#') {
                ponteiroPosicao = ponteiroPosicao->right;
            }
            aux += 1;
        }
        aux = 0;

        return 0;
    }
    
    else {
          while ( aux < 5 ) {
            if (aux >= 0 || aux < 5) {
                *((char*)ponteiroPosicao->info) = '*';
            }

            ponteiroPosicao->oqueTemNesseNo = PORTA_AVIAO;

            if(*((char*)ponteiroPosicao->up->info) == '^') {
                ponteiroPosicao = ponteiroPosicao->up;

            }else if(*((char*)ponteiroPosicao->down->info) == 'v') {
                ponteiroPosicao = ponteiroPosicao->down;

            }else if(*((char*)ponteiroPosicao->left->info) == '<') {
                ponteiroPosicao = ponteiroPosicao->left;     

            }else if(*((char*)ponteiroPosicao->right->info) == '>') {
                ponteiroPosicao = ponteiroPosicao->right;

            }else if(*((char*)ponteiroPosicao->up->info) == '#') {
                ponteiroPosicao = ponteiroPosicao->up;

            }else if(*((char*)ponteiroPosicao->down->info) == '#') {
                ponteiroPosicao = ponteiroPosicao->down;

            }else if(*((char*)ponteiroPosicao->left->info) == '#') {
                ponteiroPosicao = ponteiroPosicao->left;

            }else if(*((char*)ponteiroPosicao->right->info) == '#') {
                ponteiroPosicao = ponteiroPosicao->right;
            }

            //Casos extras por conta do bug no tabuleiro
            // else if(*((char*)ponteiroPosicao->up->info) == '<') {
            //     ponteiroPosicao = ponteiroPosicao->up;

            // }else if(*((char*)ponteiroPosicao->down->info) == '>') {
            //     ponteiroPosicao = ponteiroPosicao->down;
            // }
            aux += 1;
        }

        return 0;

    }
    verificarOsDanosDoTiro(TabuleiroComputador, L, ponteiroPosicao);
    printf("Última jogada do computador: %c%d \n", letra, numero);
    //return 1;
}
