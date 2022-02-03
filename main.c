#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "jogabilidade.h"

int main () {
    list *L;


    L = createList();



    assembleTheLetterList(L);

    linkVerticalLists(L);
    
    printList(L);

    
    
    acharPosicaoDeUmNo(L, 4, 'F');

    DarUmTiro(L);

    printf("--------------------------\n");

    

    return 0;
}