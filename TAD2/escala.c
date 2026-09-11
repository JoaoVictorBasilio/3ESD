#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escala.h"

/*
 * Implementação do TAD Escala.
 * A escala guarda os dias da semana em um conjunto, além do horário
 * de entrada e saída da jornada de trabalho.
 */

struct escala {
    Conjunto *dias_semana;
    Horario *entrada;
    Horario *saida;
};

EscalaTrabalho* esc_cria(Horario *entrada, Horario *saida) {
    EscalaTrabalho *e = (EscalaTrabalho*) malloc(sizeof(EscalaTrabalho));
    if (e != NULL) {
        e->dias_semana = conj_cria();
        e->entrada = entrada;
        e->saida = saida;
    }
    return e;
}

void esc_libera(EscalaTrabalho *e) {
    if (e != NULL) {
        conj_libera(e->dias_semana);
        hor_libera(e->entrada);
        hor_libera(e->saida);
        free(e);
    }
}

void esc_adicionarDia(EscalaTrabalho *e, int dia_semana) {
    if (e != NULL && e->dias_semana != NULL) {
        conj_insere(e->dias_semana, dia_semana);
    }
}

char* esc_paraString(EscalaTrabalho *e) {
    char *str_dias = conj_paraString(e->dias_semana);
    char *str_ent = hor_paraString(e->entrada);
    char *str_sai = hor_paraString(e->saida);
    
    char *resultado = (char*) malloc((strlen(str_dias) + strlen(str_ent) + strlen(str_sai) + 50) * sizeof(char));
    sprintf(resultado, "Dias: %s | Entrada: %s | Saida: %s", str_dias, str_ent, str_sai);
    
    free(str_dias);
    free(str_ent);
    free(str_sai);
    
    return resultado;
}