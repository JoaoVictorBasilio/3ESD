#ifndef BAGAGEM_H
#define BAGAGEM_H

#include "altura.h"
#include "massa.h"

typedef struct bagagem Bagagem;

Bagagem* bag_cria(Altura* alt, Altura* larg, Altura* comp, Massa* peso);

void bag_libera(Bagagem* b);

char* bag_paraString(const Bagagem* b);

float bag_calculaVolumeM3(const Bagagem* b);

/* Retorna o ponteiro para a massa da bagagem */
Massa* bag_getMassa(const Bagagem* b);

#endif