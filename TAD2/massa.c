#include <stdio.h>
#include <stdlib.h>
#include "massa.h"

/*
 * Implementação do TAD Massa.
 * A massa é armazenada em quilogramas e gramas, com ajuste automático
 * de transbordo quando os gramas passam de 999.
 */

struct massa {
    int kg;
    int g;
};

Massa* mas_cria(int kg, int g) {
    Massa *m = (Massa*) malloc(sizeof(Massa));
    if (m != NULL) {
        // Ajuste automático de transbordo (1000g = 1kg)
        m->kg = kg + (g / 1000);
        m->g = g % 1000;
    }
    return m;
}

void mas_libera(Massa *m) {
    free(m);
}

char* mas_paraString(Massa *m) {
    char *str = (char*) malloc(30 * sizeof(char));
    if (str != NULL) {
        sprintf(str, "%d,%03dkg", m->kg, m->g);
    }
    return str;
}

int mas_paraGramas(Massa *m) {
    return (m->kg * 1000) + m->g;
}

Massa* mas_soma(Massa *m1, Massa *m2) {
    int total_g1 = mas_paraGramas(m1);
    int total_g2 = mas_paraGramas(m2);
    return mas_cria(0, total_g1 + total_g2);
}