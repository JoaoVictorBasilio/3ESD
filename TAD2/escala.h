#ifndef ESCALA_H
#define ESCALA_H

#include "horario.h"
#include "conjunto.h"

typedef struct escala Escala;

Escala* esc_cria(Horario* entrada, Horario* saida);

void esc_libera(Escala* e);

void esc_adicionarDia(Escala* e, int dia_semana);

char* esc_paraString(const Escala* e);

#endif