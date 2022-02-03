#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"


//aqui eu crio a função que retorna o ponteiro para a lista de letras que fica na parte de cima do tabuleiro 
list *createList () {
  
    list *L;

    L = malloc(sizeof(list));

    return L;
} 

//aqui eu crio a função que retorna o ponteiro para uma lista que irá ficar na parte dentro do tabuleiro  
fieldList *createFieldList () {
  
    fieldList *L;

    L = malloc(sizeof(fieldList));

    return L;
} 

//essa função ela via printar o tabuleiro na tela
void printList(list *L) {
    letterNode *aux;
    fieldNode *aux2;
    fieldNode *aux3;
    int k = 0;
    aux = L->firstNode;
    
    /* eu fiz dois whiles pra cade tipo de lista, pq os nós são de tipos diferentes
    ai não pensei em outro jeito de printar tudo 
    aqui nesse while ele vai printar a lista de cima, que é a lista de letra  */
    while (aux->prox != NULL) {
        if ( k == 0 ) {
            printf("%s  ", aux->information);
            k += 1;
        }else {
            printf("%s ", aux->information);
        }
       
        aux = aux->prox;
    };
    printf("%s ", aux->information);
    printf("\n");

    /* aqui após printar a lista de letras ele vai pegar o nó de baixo 
    do primeiro nó da lista de letras  */
    aux2 = L->firstNode->down;

    /* aqui printa cada lista horizontal
    funciona assim: 
    eu pego um nó da primeira lista vertical, no caso a que tem os números, 
    printo esse nó 
    após isso, usando o encadeamento pelas laterais 
    eu ando uma casa pro lado, printo esse nó que eu cheguei, 
    depois ando mais uma casa pro lado, printo, depois ando....
    isso se repete até que eu chegue no nulo, isso é para uma lista na horizontal 
    eu repito esse mesmo processo para cada nó da primeira lista de números*/
    while (aux2 != NULL) {
        if ( aux2->tipo == 0 ) {
            printf("%c  ", *(char*)aux2->info);
        }else {
            if ( *(int*)aux2->info < 10 ) {
                printf("%d  ", *(int*)aux2->info);
            }else {
                printf("%d ", *(int*)aux2->info);
            }
            
        };
        /* após printar o nó da lista de números
        eu ando uma casa para a direita */
        aux3 = aux2->right;
        
        /* Aqui é a parte que eu ando até o fim de cada lista horizontal 
        e printo cada elemento */
        while (aux3 != NULL) {
            
            if ( aux3->tipo == 0 ) {
            printf("%c ", *(char*)aux3->info);
            }else {
                printf("%d ", *(int*)aux3->info);
            };
            aux3 = aux3->right;
           
        };
        printf("\n");
        aux2 = aux2->down;
        
    };


}

/* nessa função eu crio a lista de letras e as listas na vertical
Após criar cada nó da lista de letras, eu já crio a lista na vertical e encadeio ela com o nó  da lista 
de palavras que acabei de criar */
void assembleTheLetterList ( list *L ) {
    char fieldLetters[13] = {'A','B', 'C', 'D', 'E', 'F','G','H','I','J','K','L', ' '};
    int k;
    char *letter;
    fieldList *l;
    letterNode *aux;
    letterNode *NewNode;
   

   /*  aqui eu preferia fazer um if para o k = 0 e k = 1,
    pois as 3 ultimas linha mudam de um para o outro  */

    for (k = 0; k < 3; k++ ) {
        
        if (k == 0 ) {
            aux = (letterNode*)malloc(sizeof(letterNode));
            aux->information[0] = ' ';
            aux->prox = NULL;
            L->firstNode = aux;
            l = createFieldList();
            CreateVertical ( aux, l, FieldNumbers);
            //printList(L);
        }else if (k == 1) {
         
            aux = malloc(sizeof(letterNode));
            aux->information[0] = ' ';
            aux->prox = NULL;
            L->firstNode->prox = aux;
            l = createFieldList();
            CreateVertical ( aux, l, EdgeSymbols);
            //printList(L);
        }else { 
          
            k = 0;
            while ( k <= 12 ) {
               
                NewNode = malloc(sizeof(letterNode));
               
              
                NewNode->information[0] =  fieldLetters[k];
               
                NewNode->prox = NULL;
                aux->prox = NewNode;
                l = createFieldList();
                if (k == 12) {
                    
                    CreateVertical ( NewNode, l, EdgeSymbols);
                }else {
                    CreateVertical ( NewNode, l, BattleFields);
                }
               
                aux = aux->prox;
                k += 1;
                 
                //printList(L);
            }
        }
      


    }
};

/* essa função cria as lista verticais 
ela recebe o nó da lista de letras que ela vai encadear a lista que ela acabou de criar
e ele recebe tbm o tipo de lista que ela tem q criar
pois no tabuleiro tem as bordas com aqueles simbolos, os numeros e o espaços das embarcações 
assim ela verifica qual o tipo de lista e ai coloca o caractere que é pra ter naquela lista

funciona mais ou menos assim:
ela cria o primeiro nó da lista vertical
e verifica qual o tipo de lista que foi passado para ela 
dependendo do tipo o o caractere desse nó muda 
depois ela entra no while e vai criando cada nó e encadeando com os anterioes 
pra formar a lista vertical */

fieldNode *CreateVertical (letterNode *A,  fieldList *L, int typeOfTheList ) {
    int numbers[13] = {1,2,3,4,5,6,7,8,9,10,11,12,0};
    char symbols = '|';
    int k = 0;
    fieldNode *aux;
    fieldNode *newNode;

    aux = malloc(sizeof(fieldNode)); 
    aux->info = malloc(sizeof(char));  
    if (typeOfTheList == FieldNumbers) {
        *((char*)aux->info) = ' ';
    }else if (typeOfTheList == EdgeSymbols){
        *((char*)aux->info) = '+';
    }else {
        *((char*)aux->info) = '-';
    }
    aux->tipo = 0;
    A->down = aux;
    aux->down = NULL;
    aux->left = NULL;
    aux->right = NULL;
    aux->up = NULL; 
    L->firstNode = aux;


    while( k < 13) {
        newNode = malloc(sizeof(fieldNode));
        newNode->tipo = AGUA;
        newNode->down = NULL;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->up = NULL; 
        if (numbers[k] == 0 && typeOfTheList == FieldNumbers) {
            newNode->info = malloc(sizeof(char));
            *((char*)newNode->info) = ' ';
            newNode->tipo = 0;
        }else if (numbers[k] == 0 && typeOfTheList == EdgeSymbols) {
            newNode->info = malloc(sizeof(char));
            *((char*)newNode->info) = '+';
            newNode->tipo = 0;
        }else if (numbers[k] == 0 && typeOfTheList == BattleFields) {
            newNode->info = malloc(sizeof(char));
            *((char*)newNode->info) = '-';
            newNode->tipo = 0;
        }else if (typeOfTheList == FieldNumbers) {
            newNode->info = malloc(sizeof(char));
            *((int*)newNode->info) = numbers[k];
            newNode->tipo = 1;
        }else if (typeOfTheList == EdgeSymbols){
            newNode->info = malloc(sizeof(char));  
            *((char*)newNode->info) = symbols;
            newNode->tipo = 0;
        }else {
            newNode->info = malloc(sizeof(char));
            *((char*)newNode->info) = ' ';
            newNode->tipo = 0;
        }

        aux->down = newNode;
        newNode->up = aux;
        aux = aux->down;

        k += 1;
    }
};

/* Essa função vai encadear as listas verticais pelas laterais
ela pega os dois primeiros nós da lista de letras 
desce uma posição 
encadeaia esses nós, depois desce um posição denovo, ecadeia....
ela repete isso até chegar o fim da lista vertical 
depois ela anda um posição pro lado na lista de letras e repete o mesmo processo 
desce uma posição 
encadeaia esses nós, depois desce um posição denovo, ecadeia....
ela repete isso até q a lista das letras chegue ao fim 
 */
void linkVerticalLists (list *L) {
    letterNode *letter1;
    letterNode *letter2;
    fieldNode *aux1;
    fieldNode *aux2;
    int k = 0;
   

    letter1 = L->firstNode;
    letter2 = L->firstNode->prox;
   

    while (k < 14) {
        aux1 = letter1->down;
        aux2 = letter2->down;
       
        while ( aux1 != NULL && aux2 != NULL ) {
            aux1->right = aux2;
            aux2->left = aux1;
            aux1 = aux1->down;
            aux2 = aux2->down;
            
        };
        letter1 = letter1->prox;
        letter2 = letter2->prox;
        k += 1;        
    }

}; 
