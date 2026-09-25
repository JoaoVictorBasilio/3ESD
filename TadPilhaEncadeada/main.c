/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "pilhaEncadeada.h"

int main()
{
    tPilha* p1=pilha_cria();
    push(p1,1);
    push(p1,2);
    push(p1,3);
    push(p1,4);
    pilha_exibe(p1);

    return 0;
}