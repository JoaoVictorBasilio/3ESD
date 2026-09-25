#include <stdlib.h>
typedef struct pilha tPilha;
typedef struct no  tNo;


tPilha* pilha_cria();
    
int pilha_vazia(tPilha *pilha);
    
int push(tPilha *pilha, int id);
    
int pop(tPilha * pilha, int * inf);
    
void pilha_libera(tPilha *pilha);
    
void pilha_exibe(tPilha *pilha);
    
int pilha_consultaTopo(tPilha *pilha, int* id);
    