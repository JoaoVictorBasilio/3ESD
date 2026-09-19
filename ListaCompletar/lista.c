#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////
// FUNÇÕES AUXILARES
//Retira vários
int retira_varios(tLista * pl, int no);
    
//Busca DESORDENADA sem repetição 
int busca_des_srep(tLista *pl,int chave,int *pos);
//Busca BINÁRIA 
int busca_bin(tLista *pl, int chave, int *pos);

void encontra_posInicEqt(tLista*pl,int * posRet, int *qt, int valor);

//CHEGA PARA CÁ  ==> TRANSFORMAR PARA  memmove
void chegaparaca(tLista *pl, int pos, int qt);
void chegaparacaMC(tLista *pl, int posRet, int qt);

// CHEGA PARA LÁ ==> TRANSFORMAR PARA  memcpy
void chegaparala(tLista *pl, int pos);
void chegaparalaMC(tLista *pl, int pos, int qt);
//////////////////////////////////////////////////////////////////////////




/* Em seguida, um tipo para a lista */ 
struct tipo_lista 
{ 
    int* vnos; 
    int qtnos; 
    int maximo; 
    int ehclassificada; // 1: classificada 0: não classificada 
    int temrepeticao; // 1: com repetição 0: sem repetição 
}; 

/*cria lista vazia*/ 
tLista * lista_cria_vazia(int maximo,int classif, int repet) {
    tLista *pl = (tLista*) malloc(sizeof(tLista));
	pl->vnos=(int*)malloc (sizeof(int)* maximo);
	pl->qtnos = 0; 
    pl->maximo= maximo; 
    pl->ehclassificada=classif; 
    pl->temrepeticao=repet; 
    return pl;
} 
//lista está vazia? 
int lista_vazia( const tLista *pl){ 
    return ( pl->qtnos == 0); 
}
//lista está cheia? 
int lista_cheia( const tLista *pl){ 
    return ( pl->qtnos == pl->maximo); 
} 
//lista com repetição? 
int lista_repet( const tLista *pl){ 
    return ( pl->temrepeticao == 1); 
} 
//lista classificada? 
int lista_classif( const tLista *pl){ 
    return ( pl->ehclassificada == 1); 
} 
//percorre a lista 
void lista_percorre(const tLista *pl) { 
    int i; 
    printf("\n (");
    for(i = 0; i < pl->qtnos-1; i++) 
        printf(" %d , ", pl->vnos[i]); 
    printf("%d )\n", pl->vnos[i]); 
} 

int lista_inclui(tLista *pl, int novo) {
    int posNovo, achou;

    // 1. Verifica se tem espaço
    if (lista_cheia(pl))
        return 0; 

    // 2. Verifica se já existe (caso a lista NÃO permita repetição)
    if (!lista_repet(pl)) {
        if (lista_classif(pl))
            achou = busca_bin(pl, novo, &posNovo);
        else
            achou = busca_des_srep(pl, novo, &posNovo);
            
        if (achou)
            return -1; // Retorna -1 indicando que o elemento já existe
    }


    if (lista_classif(pl)) {
     
        if (lista_repet(pl)) {
            busca_bin(pl, novo, &posNovo); 
        }
        
        // Abre um buraco tamanho 1 na posição correta
        chegaparalaMC(pl, posNovo, 1);
        
        // Insere no buraco
        pl->vnos[posNovo] = novo;
    } else {
        // Se for desordenada, é só colocar no primeiro espaço livre do final
        pl->vnos[pl->qtnos] = novo;
    }

 
    pl->qtnos++;
    
    return 1; // Sucesso
}

int lista_exclui(tLista*pl,int no){
    int posRet,achou,qt=1;
    if (lista_vazia(pl))
        return 0;

    if (lista_repet(pl) && ! lista_classif(pl))
        //return 1;
        return retira_varios(pl,no);
        
    if(lista_classif(pl))
        achou=busca_bin(pl,no, &posRet);
    else
        achou=busca_des_srep(pl,no,&posRet);
        
    if (!achou)
        return -1; // exclusão de inexistente
    
    if (lista_repet(pl)){
       
        //printf("\nantes %d %d", posRet,qt);
        encontra_posInicEqt(pl,&posRet, &qt,no);
        //printf("\ndepois %d %d", posRet,qt);
        }
    
    chegaparacaMC(pl, posRet, qt);
    //printf("\n\n%d %d ",qt, pl->qtnos);
    pl->qtnos-=qt;
    //printf("\n%d %d ",qt, pl->qtnos);
    return 1;
}
    

    
    

// FUNÇÕES AUXILARES
//Retira vários
int retira_varios(tLista * pl, int no){ // -1 se no não existe, ou 1
    
    int i;
    int achou = 0;
    i=0;
    while (i<pl->qtnos){
        if (pl->vnos[i]== no){
            chegaparacaMC(pl, i, 1);
            pl->qtnos--;
            achou = 1;
        }
        else{
            i++;
        }
        
    }
    return achou;
}
    
//Busca DESORDENADA sem repetição 
int busca_des_srep(tLista *pl,int chave,int *pos){ 
    int i; 
    for(i=0; (i<pl->qtnos)&&(pl->vnos[i]!=chave); i++); 
    (*pos) = i; 
    return(i < pl->qtnos); 
    } 
//Busca BINÁRIA 
int busca_bin(tLista *pl, int chave, int *pos) {
    int inicio = 0, meio, fim = pl->qtnos-1, achou = 0; 
    while((inicio <= fim) && (!achou)) { 
        meio = (inicio + fim) /2;
        if(pl->vnos[meio] == chave) 
            achou = 1; 
        else if(pl->vnos[meio] > chave) 
            fim = meio-1; 
        else 
            inicio = meio+1; 
    } 
    if(achou) 
        (*pos) = meio; 
    
    else 
        (*pos) = inicio; 
    return achou; 
} 

void encontra_posInicEqt(tLista*pl,int * posRet, int *qt, int valor){
    int inic, fim;
    
    (*qt)=1;
    inic=*posRet-1;
    fim=*posRet+1;
    while (inic >=0 && pl->vnos[inic]==valor){
        (*qt)++;
        inic--;
        (*posRet)--;
    }
    while (fim < pl->qtnos && pl->vnos[fim]==valor){
        (*qt)++;
        fim++;
    }
    
}
    

//CHEGA PARA CÁ  ==> TRANSFORMAR PARA  memcpy
void chegaparaca(tLista *pl, int pos, int qt) { 
    int i; 
    for(i = pos; i <= pl->qtnos - qt; i++) 
        pl->vnos[i] = pl->vnos[i+qt]; 
} 


// CHEGA PARA LÁ ==> TRANSFORMAR PARA  memcpy

void chegaparala(tLista *pl, int pos){ 
    int i; 
    for(i = pl->qtnos; i > pos; i--) 
        pl->vnos[i] = pl->vnos[i-1]; 
}

void chegaparacaMC(tLista *pl, int posRet, int qt){ 
    int qtd = pl->qtnos - (posRet+qt);

    if(qtd >0){
        memmove(&pl->vnos[posRet], &pl->vnos[posRet + qt], qtd *sizeof(int));
    }

}
   

void chegaparalaMC(tLista *pl, int pos, int qt){ 
    int qtd = pl->qtnos - pos;
    
    if (qtd > 0) {
        memcpy(&pl->vnos[pos + qt], &pl->vnos[pos], qtd * sizeof(int));
    }
}
