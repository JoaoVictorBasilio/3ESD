#ifndef MASSA_H
#define MASSA_H

/*
 * TAD Massa
 * --------
 * Representa uma massa em quilogramas e gramas.
 * Permite criar, somar, converter para texto e transformar em gramas.
 */

typedef struct massa Massa;

Massa* mas_cria(int kg, int g);
void mas_libera(Massa *m);
char* mas_paraString(Massa *m);
int mas_paraGramas(Massa *m);
Massa* mas_soma(Massa *m1, Massa *m2);

#endif