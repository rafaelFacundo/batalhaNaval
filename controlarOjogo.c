#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "matriz.h"
#include "jogabilidade.h"
#include "controlarOJogo.h"
#include "jogadaPC.h"


/* essa função pede a posição que o usuario quer atacar 
funciona asssim:
primeiro o numero e letra sao definidos como -1 
assim o while vai rodar até q a entrada seja valida
dentro do while ele pede a posição ao usuario 
depois entra em um segundo while, para buscar a letra 
ele roda dentro do while até que j(usado para percorrer a array que guarda a entrada do usuario)
seja 3, ou seja, que já passou por todas as posições da entrada do usuario 
quando ele entra no while de buscar a letra ele entra em um segundo while 
que anda pela array de letras permitidas até que ele encontre uma letra igual 
ou que k chegue ao fim (usado para andar na array de letras)
se k chega ao fim ele olha se ainda é diferente se for ele seta k = 0 e j += 1 para continuar procurando 
se n ele armazena a letra da posição 
ao sair do while mais externo ele olha se j == 4, pois assim significa que andamos por toda a respos do usuario 
e não encontramos nenhuma letra válida, então repetimos todo o processo.

Caso a letra seja válida, vamos procurar os numeros 
assim andamos na resposta do usuario denovo para procurar os numeros
procuramos por algum caractere que esteja entre 49 e 57 
pois esses são os códigos ascii que correspondem os números de 1 a 9
    (foi necessario usar tabela ascii porque a entrada é em formato de texto e para converter apenas um caractere 
    de número em int não foi possivel, além disso economiza memória, suponho)
se acharmos um caractere que conrresponde a esse intervalo 
    se não é entrada inválida e pedimos denovo
verificamos duas coisas primeiro se o proximo caratere também é um numero, 
mas que só pode está no intervalo de 48 e 50, pois assim formariam os numeros 10,11,12 
se estiver então, nós transformamos o primeiro caractere do numero em int, multiplicamos por 10 e somamos com o segundo 
Mas se o proximo caractere for um numero também mas fora desse intervalo significa que a entra é invalida 
e vamos pedir denovo 

Isso se repete até que a entrada seja valida

após isso chamamos a função de dar o tiro   */

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

/*  */

int trocaJogador(list *pessoa, list *computador){
    int resultadoDoTiro;

    resultadoDoTiro = pedirPosicaoParaUsuario(pessoa, computador);

    if(resultadoDoTiro == 0){
        resultadoDoTiro = jogadaPC(pessoa, computador);

    }
    return resultadoDoTiro;

}


/* aqui controlamos as chamaRodadas
o while roda até que uma dos dois jogadores percam todas as embarcações 
    preferimos usar um while pq assim ele chama a função e dependendo do retorno 
    ele chama ou não denovo, pensamos que fosse melhor q recursividade 
    pois dependendo da quantidade de jogadas, a recursividade poderia encher a memória 
a função funciona assim 
ela chama a função de pedir a posição (q por sua vez já chama a de dar o tiro )
apos dar o tiro a função de dar o tiro chama a função de avaliar o estrago (que retorna 1 se atingiu barco ou 0 se foi agua)
logo a função de dar o tiro também retorna a mesma coisa 
e a de pedir posição também retorna a mesma coisa 
assim dependendo do retorno a função de chamar rodadas decide 
se o retorno foi 1 então quem acertou joga novamente
se for 0 é a vez do outro 
 */


int chamaRodadas (list *pessoa, list *computador ) {
    int resultadoDoTiro;
    int resposta;


    while ( pessoa->donoDoTabuleiro->totalDeEmbarcacoes > 0 && computador->donoDoTabuleiro->totalDeEmbarcacoes > 0 ) {
        resultadoDoTiro = trocaJogador(pessoa,computador);
        //resultadoDoTiro = pedirPosicaoParaUsuario(pessoa, computador);
        printf("SEU TABULEIRO: \n");
        printList(pessoa);
        printf("TABULEIRO DO PC: \n");
        printListPc(computador);
        if (resultadoDoTiro == 0) {
            
            trocaJogador(pessoa, computador);

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