#include "massa.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct mas {
    int kg,g;
}

Massa* mas_cria(int kg,int g){
    Massa* m = (Massa*) malloc(sizeof(Massa));
    if(m == NULL){
        printf("Memória insuficiente!\n");
        exit(1);
    }
    m->kg = kg;
    m->g = g;
    return m;
}

void mas_libera(Massa* m){
    free(m);
}

char* mas_paraString(Massa* m){
    char* pt;
    int tam = sizeof(*m) + 5;
    pt = (char*)malloc(tam);
    sprintf(pt, "%d,%02dm",m->kg,m->g);
    return pt;
}

int mas_paraGramas(Massa* m){
        return m->kg *1000 + m->g;
}

int mas_soma(Massa *m1,Massa *m2){
    int a1 = mas_paraGramas(m1);
    int a2 = mas_paraGramas(m2);
    int dif = a1-a2;
    return dif;
}