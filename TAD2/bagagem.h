#ifndef BAGAGEM_H
#define BAGAGEM_H

#include "altura.h"
#include "massa.h"

/*
 * TAD Bagagem
 * -----------
 * Representa uma bagagem com altura, largura, comprimento e peso.
 * Permite calcular as dimensões, converter para texto e obter o volume.
 */
typedef struct bagagem Bagagem;

Bagagem* bag_cria(Altura *alt, Altura *larg, Altura *comp, Massa *peso);
void bag_libera(Bagagem *b);
char* bag_paraString(Bagagem *b);
double bag_calculaVolumeM3(Bagagem *b);

#endif