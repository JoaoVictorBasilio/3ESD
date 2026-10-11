#ifndef MASSA_H
#define MASSA_H

typedef struct massa Massa;

Massa* mas_cria(int kg, int g);

void mas_libera(Massa* m);

char* mas_paraString(const Massa* m);

long mas_paraGramas(const Massa* m);

Massa* mas_soma(const Massa* m1, const Massa* m2);

#endif