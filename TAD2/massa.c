#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "massa.h"

struct massa
{
    int kg;
    int g;
};

Massa* mas_cria(int kg, int g){
    Massa* m = (Massa*) malloc(sizeof(Massa));

    if(m == NULL){
        return NULL;
    }

    int kg_extra = g / 1000;
    int g_restantes = g % 1000;

    m->kg = kg + kg_extra;
    m->g = g_restantes;

    return m;
}

void mas_libera(Massa* m){
    if (m != NULL){
        free(m);
    }
}

char* mas_paraString(const Massa* m){
    if(m == NULL) {
        return NULL;
    }

    char* str = (char*) malloc(30 * sizeof(char));

    if(str != NULL){
        sprintf(str, "%d,%03dkg", m->kg, m->g);
    }

    return str;
}

long mas_paraGramas(const Massa* m){
    if(m== NULL) {
        return 0;
    }

    return ((long)m->kg * 1000) + m->g;
}

Massa* mas_soma(const Massa* m1, const Massa* m2){
    if(m1 == NULL || m2 == NULL){
        return NULL;
    }

    int soma_kg = m1->kg + m2->kg;
    int soma_g = m1->g + m2->g;

    return mas_cria(soma_kg, soma_g);
}