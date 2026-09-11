#ifndef ESCALA_H
#define ESCALA_H

#include "conj.h"
#include "horario.h"

/*
 * TAD Escala
 * ---------
 * Representa uma escala de trabalho com dias da semana, horário de entrada
 * e horário de saída.
 */
typedef struct escala EscalaTrabalho;

EscalaTrabalho* esc_cria(Horario *entrada, Horario *saida);
void esc_libera(EscalaTrabalho *e);
void esc_adicionarDia(EscalaTrabalho *e, int dia_semana);
char* esc_paraString(EscalaTrabalho *e);

#endif