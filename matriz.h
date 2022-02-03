#ifndef MATRIZLIB
#define MATRIZLIB

#define FieldNumbers 0
#define EdgeSymbols 1
#define BattleFields 2

#define AGUA 0
#define JANGADA 1
#define DESTROYER 2
#define SUBMARINO 3
#define FRAGATAS 4 
#define PORTA_AVIAO 5

typedef struct node_s {
    struct node_s *left, *right, *up, *down;
	void *info;
	int tipo;
	int chave;
} fieldNode;

typedef struct  no_letter {
    struct no_letter *prox; 
    fieldNode *down;
    char information[1];
} letterNode ;


typedef struct list_s {
    letterNode *firstNode;
}list;

typedef struct list_Field {
    fieldNode *firstNode;
}fieldList;

list *createList (); 

fieldList *createFieldList (); 

void assembleTheLetterList ( list *L );

void assembleTheEdgesList ( list *L );

fieldNode *CreateVertical( letterNode *A, fieldList *L, int typeOfInformation );

void linkVerticalLists (list *L); 

void printList(list *L);

void printList(list *L);





#endif