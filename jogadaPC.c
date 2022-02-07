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

//Gera um número e letra para a jogada aleatória do PC e também verifica se a posição já foi jogada anteriormente 

    do{

        srand(time(NULL));

        numero = 1 + (rand() % 12);
        letra = 'A' + (char)(rand() % ('L' - 'A'));

        ponteiroPosicao = acharPosicaoDeUmNo(TabuleiroComputador, numero, letra);

    }while((NumeroAnterior == numero) && (LetraAnterior == letra));

    
    DarUmTiro(TabuleiroComputador, L, numero, letra);

//Depois do tiro, verifica a casa atingida e o tipo que tem lá

    if(ponteiroPosicao->oqueTemNesseNo == AGUA){
        NumeroAnterior = numero;
        LetraAnterior = letra;
    }

    else if(ponteiroPosicao->oqueTemNesseNo == JANGADA){
        NumeroAnterior = numero;
        LetraAnterior = letra;
    }

    else if(ponteiroPosicao->oqueTemNesseNo == SUBMARINO){
        NumeroAnterior = numero;
        LetraAnterior = letra;

    }

//A partir daqui é feita a jogada para as embarcações com mais de 1 casa ocupada

//A cada iteração é feito o tiro até aux ser o tamanho da embarcação, quando o barco é afundado

//Quando o computador acertar uma dessas embarcações tem que prosseguir até afundá-la e depois disso é feita a troca de jogador

    else if(ponteiroPosicao->oqueTemNesseNo == FRAGATAS){
        while(aux < 2){

            
            if(aux == 0 || aux == 1){
                *((char*)ponteiroPosicao->info) = '*';
            }

            ponteiroPosicao->oqueTemNesseNo = FRAGATAS;

//O computador completa sua jogada afundando a embarcação completa, para isso, verifica as casas ao redor para prosseguir destruindo a embarcação do jogador

//O computador verifica a info das casas ao redor, se estiver ocupada com uma parte da embarcação é feita a troca de ponteiroPosicao para retornar ao inicio e fazer um novo tiro

//ponteiroPosicao rebebe uma nova posição do tabuleiro que é a próxima a ser jogada e é retornado para o inicio do laço

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
        
        NumeroAnterior = numero;
        LetraAnterior = letra;

        printf("Última jogada do computador: %c%d \n", letra, numero);
    }

    else if ( ponteiroPosicao->oqueTemNesseNo== DESTROYER )  {
        while ( aux < 3 ) {
            if (aux >= 0 || aux < 3 ) {
                *((char*)ponteiroPosicao->info) = '*';
            }

            ponteiroPosicao->oqueTemNesseNo = DESTROYER;

//O computador completa sua jogada afundando a embarcação completa, para isso, verifica as casas ao redor para prosseguir destruindo a embarcação do jogador

//O computador verifica a info das casas ao redor, se estiver ocupada com uma parte da embarcação é feita a troca de ponteiroPosicao para retornar ao inicio e fazer um novo tiro

//ponteiroPosicao rebebe uma nova posição do tabuleiro que é a próxima a ser jogada e é retornado para o inicio do laço

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

        NumeroAnterior = numero;
        LetraAnterior = letra;

        printf("Última jogada do computador: %c%d \n", letra, numero);
    }
    
    else {
          while ( aux < 5 ) {
            if (aux >= 0 || aux < 5) {
                *((char*)ponteiroPosicao->info) = '*';
            }

            ponteiroPosicao->oqueTemNesseNo = PORTA_AVIAO;

//O computador completa sua jogada afundando a embarcação completa, para isso, verifica as casas ao redor para prosseguir destruindo a embarcação do jogador

//O computador verifica a info das casas ao redor, se estiver ocupada com uma parte da embarcação é feita a troca de ponteiroPosicao para retornar ao inicio e fazer um novo tiro

//ponteiroPosicao rebebe uma nova posição do tabuleiro que é a próxima a ser jogada e é retornado para o inicio do laço

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

            }else if(*((char*)ponteiroPosicao->up->info) == '<') {
                ponteiroPosicao = ponteiroPosicao->up;

            }else if(*((char*)ponteiroPosicao->down->info) == '>') {
                ponteiroPosicao = ponteiroPosicao->down;
            }
            aux += 1;

        }
        
        NumeroAnterior = numero;
        LetraAnterior = letra;

        printf("Última jogada do computador: %c%d \n", letra, numero);


    }

//Depois do tiro chama a função de verificar os danos do tiro

    verificarOsDanosDoTiro(TabuleiroComputador, L,  ponteiroPosicao);
    printf("\nÚltima jogada do computador: %c%d \n", letra, numero);


//Retorna 1 para a função trocaJogador() em controlarOjogo.c, significa que é a vez do jogador

    return 1;
}
