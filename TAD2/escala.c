#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escala.h"

struct escala {
    Conjunto *dias_semana;
    Horario *entrada;
    Horario *saida;
};

Escala* esc_cria(Horario* entrada, Horario* saida){
    if(entrada == NULL || saida == NULL){
        return NULL;
    }

    Escala* e = (Escala*) malloc(sizeof(Escala));
    if(e == NULL){
        return NULL;
    }

    e->dias_semana = conj_Cria();
    e->entrada = entrada;
    e->saida = saida;

    return e;
}

void esc_libera(Escala* e){
    if(e != NULL){
        conj_Libera(e->dias_semana);
        hor_libera(e->entrada);
        hor_libera(e->saida);
        free(e);
    }
}

void esc_adicionarDia(Escala* e, int dia_semana){
    if(e == NULL || dia_semana < 1 || dia_semana > 7){
        return;
    }

    conj_Insere(e->dias_semana, dia_semana);
}

char* esc_paraString(const Escala* e){
    if(e == NULL){
        return NULL;
    }

    char* str_entrada = hor_paraString(e->entrada);
    char* str_saida = hor_paraString(e->saida);
    if(str_entrada == NULL || str_saida == NULL){
        free(str_entrada);
        free(str_saida);
        return NULL;
    }

    char* str_dias = conj_paraString(e->dias_semana);
    if(str_dias == NULL){
        free(str_entrada);
        free(str_saida);
        free(str_dias);
        return NULL;
    }

    size_t tamanho_seguro = strlen(str_entrada) + strlen(str_saida) + strlen(str_dias) + 50;
    char* relatorio = (char*) calloc(tamanho_seguro, sizeof(char));

    if(relatorio != NULL){
        sprintf(relatorio, "Dias da semana: %s\nEntrada: %s\nSaída: %s\n", str_dias, str_entrada, str_saida);
    }

    free(str_entrada);
    free(str_saida);
    free(str_dias);

    return relatorio;
}