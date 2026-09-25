#include "pilhaEncadeada.h"
#include <stdio.h>
#include <stdlib.h>

struct pilha {
    tNo* topo; 
};

struct no {
    int id;
    struct no* prox;
};

// função auxiliar
tNo* criaNo(int id){
    tNo* no = (tNo*)malloc(sizeof(tNo));
    if (no == NULL){
        exit(1); 
    }
    no->id = id;
    no -> prox = NULL;
    return no;
}

tPilha* pilha_cria(){
    tPilha* pilha = (tPilha*)malloc(sizeof(tPilha));
    if (pilha == NULL){
        exit(1);
    }
    pilha->topo = NULL;
    return pilha;
}

int pilha_vazia(tPilha *pilha){
    return (pilha->topo == NULL);
}

int push(tPilha *pilha, int id) {  // retorna 1 se bem sucedida
    tNo* no = criaNo(id);
    no->prox = pilha->topo;
    pilha->topo = no;
    return 1;
}

int pop(tPilha * pilha, int * inf){ // retorna 0 se vazia ou 1 se bem sucedida
    tNo* removido;

    if (pilha_vazia(pilha)){
        return 0;
    }

    removido = pilha->topo;
    *inf = removido->id;
    pilha->topo = removido->prox;
    free(removido);
    return 1;
}

void pilha_libera(tPilha *pilha) {
    tNo *atual = pilha->topo;
    tNo *prox;
    while (atual != NULL) {
        prox = atual->prox;
        free(atual); 
        atual = prox;
    }
    free(pilha);
}

void pilha_exibe(tPilha *pilha){
    tNo *atual = pilha->topo;
    
    printf("\n( ");
    while (atual != NULL) {
        printf(" %d ",atual->id);
        atual = atual->prox;
    }
    printf(" )\n");
}
int pilha_consultaTopo(tPilha *pilha, int* id) {
    if(pilha_vazia(pilha)){ 
        return 0;
    }
    *id = pilha->topo->id;
    return 1;
}
