#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "matriz.h"
#include "jogabilidade.h"
#include "controlarOJogo.h"

int pedirPosicaoParaUsuario (list *listaQuemAtaca, list *listaAlvo) {
    char posicoes[12] = {'A', 'B', 'C', 'D', 'E', 'F','G','H','I','J','K','L'};
    char entradaDoUsuario[4];
    int numeroDaPosicao = -1;
    int letraDaPosicao = -1;
    int resultadoDoTiro;
    int x =0;
    int k = 0;
    int j = 0;

    while ( numeroDaPosicao == -1 || letraDaPosicao == -1 ) {
        printf("Vamos lá marujo, diga a posição que você quer atigir: ");
        scanf("%s", entradaDoUsuario);
       
        while ( j < 4 && toupper(entradaDoUsuario[j]) != posicoes[k] ) {

            while ( k < 12 && toupper(entradaDoUsuario[j]) != posicoes[k] ) {
                
                k += 1;
            }
            if ( k == 12 && toupper(entradaDoUsuario[j]) != posicoes[k]) {
                k = 0;
                j += 1;
            }else {
                letraDaPosicao = toupper(posicoes[k]);
            }

        }
        if (j == 4) {
            printf("entrada inválida\n");
            numeroDaPosicao = -1;
            letraDaPosicao = -1;
        }else {
            j = 0;
           
            while ( j < 3 && entradaDoUsuario[j] < 49 || entradaDoUsuario[j] > 57) {
                
                j += 1;
            }
            if ( j < 3) {
                if ( entradaDoUsuario[j+1] >= 49 && entradaDoUsuario[j+1] <= 57 ) {
                    if ( entradaDoUsuario[j+1] >= 48 && entradaDoUsuario[j+1] <= 50 ) {
                     
                        numeroDaPosicao = entradaDoUsuario[j] - '0';
                        numeroDaPosicao *= 10;
                        numeroDaPosicao += entradaDoUsuario[j+1] - '0';
                    }else {
                        printf("entrada inválida\n");
                        numeroDaPosicao = -1;
                        letraDaPosicao = -1;

                    }
                }else {
                   
                    numeroDaPosicao = entradaDoUsuario[j] - '0';
                }
            }
        }
       
        /* if ( numeroDaPosicao == -1 || letraDaPosicao == -1 ) {
            printf("entrada inválida\n");
        } */
    }

   resultadoDoTiro = DarUmTiro( listaAlvo ,listaQuemAtaca, numeroDaPosicao, letraDaPosicao);

   return resultadoDoTiro;

    
}





int chamaRodadas (list *pessoa, list *computador ) {
    int resultadoDoTiro;
    int resposta;
    while ( pessoa->donoDoTabuleiro->totalDeEmbarcacoes > 0 && computador->donoDoTabuleiro->totalDeEmbarcacoes > 0 ) {
        resultadoDoTiro = pedirPosicaoParaUsuario(pessoa, computador);
        printf("SEU TABULEIRO: \n");
        printList(pessoa);
        printf("TABULEIRO DO PC: \n");
        printListPc(computador);
        if (resultadoDoTiro == 0) {
            printf("Jogado do pc\n");
        }
        printf("Você possui: %d embarcações\n",pessoa->donoDoTabuleiro->totalDeEmbarcacoes );
        printf("total de embarcações do pc é: %d\n",computador->donoDoTabuleiro->totalDeEmbarcacoes );
    }
    if (pessoa->donoDoTabuleiro->totalDeEmbarcacoes == 0 || computador->donoDoTabuleiro->totalDeEmbarcacoes == 0) {
        if ( pessoa->donoDoTabuleiro->totalDeEmbarcacoes == 0 ) {
            printf("Droga.. você perdeu, mas um pirata não desiste, vamos lá marujo, VINGANÇAA!!\n");
            while (resposta != 1 || resposta != 2) {
                printf("Você quer continuar jogando? (1 - para continuar || 2 - para parar)\n");
                scanf("%d", &resposta);
            }
            return resposta;
        }else {
            printf("Boa marujo... você venceu!!\n");
            while (resposta != 1 || resposta != 2) {
                printf("Você quer continuar jogando? (1 - para continuar || 2 - para parar)\n");
                scanf("%d", &resposta);
            }
            return resposta;
        }
       
    }
};