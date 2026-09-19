/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include "lista.h"
int main()
{
    tLista * lista;
    lista=lista_cria_vazia(15,1,1); //  classif , com repet
    lista_inclui(lista,2);
    printf("\n 2");
    lista_percorre(lista);
    printf("\n 1 2");
    lista_inclui(lista,1);
    lista_percorre(lista);
    printf("\n 1 2 2 ");
    lista_inclui(lista,2);
    lista_percorre(lista);
    printf("\n 1 1 2 2 ");
    lista_inclui(lista,1);
    lista_percorre(lista);
    printf("\n 1 1 2 2 5");
    lista_inclui(lista,5);
    lista_percorre(lista);
    printf("\n1 1 2 2 5 5 ");
    lista_inclui(lista,5);
    lista_percorre(lista);
    printf("\n1 1 2 2 5 5 5");
    lista_inclui(lista,5);
    lista_percorre(lista);

    
     printf("\n1 1 2 2 ");
     lista_exclui(lista,5);
     lista_percorre(lista);
    
    return 0;
}
