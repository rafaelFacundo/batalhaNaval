#ifndef MATRIZLIB
#define MATRIZLIB


//usado para saber o "tipo da casa" do tabuleiro 
//pois é precisa na hora de contrruir o tabuleiro 
//saber se vamos colocar um numero, uma letra ou uma casa para as embarcações 
#define FieldNumbers 0
#define EdgeSymbols 1
#define BattleFields 2

//usados para saber oque foi atingido na hora de dar o tiro 
// e q tipo de embarcação colocar no tabuleiro na hora de distribuir
#define AGUA 0
#define JANGADA 1
#define DESTROYER 2
#define SUBMARINO 3
#define FRAGATAS 4 
#define PORTA_AVIAO 5

//usados tanto para colocar os barcos na posição 
//quanto para verificar o dano do tiro 
#define VERTICAL 6
#define HORIZONTAL 7


//usado para diferenciar tanto os pontos 
//quem ataca quem é atacado 
#define JOGADOR 8
#define COMPUTADOR 9

typedef struct node_s {
    struct node_s *left, *right, *up, *down;
	void *info;
	int tipo;
    int oqueTemNesseNo;
	int direcao;
    int podeMostrar;
} fieldNode;

typedef struct  no_letter {
    struct no_letter *prox; 
    fieldNode *down;
    char information[1];
} letterNode ;

typedef struct jogador_S {
   
    fieldNode *submarino1;
    fieldNode *submarino2;
    int totalDeEmbarcacoes;
    int tipoDeJogador;
}jogador;

typedef struct list_s {
    letterNode *firstNode;
    jogador *donoDoTabuleiro;
}list;

typedef struct list_Field {
    fieldNode *firstNode;
}fieldList;




list *createList (); 

fieldList *createFieldList (); 

void assembleTheLetterList ( list *L );

void assembleTheEdgesList ( list *L );

fieldNode *CreateVertical( list *ListaDoDono, letterNode *A, fieldList *L, int typeOfInformation );

void linkVerticalLists (list *L); 

void printList(list *L);

void printListPc(list *L);





#endif