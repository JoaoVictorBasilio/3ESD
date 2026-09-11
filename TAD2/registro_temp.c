#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro_temp.h"

/*
 * Implementação do TAD RegistroTemp.
 * Armazena a data inicial do monitoramento e uma matriz com as medições
 * de temperatura ao longo dos dias e leituras de cada dia.
 */

struct registro_temp {
    Data *data_inicio;
    Matriz *medicoes;
};

RegistroTemp* reg_cria(Data *data_inicio, int num_dias, int leituras_por_dia) {
    RegistroTemp *r = (RegistroTemp*) malloc(sizeof(RegistroTemp));
    if (r != NULL) {
        r->data_inicio = data_inicio;
        r->medicoes = mat_cria(num_dias, leituras_por_dia);
    }
    return r;
}

void reg_libera(RegistroTemp *r) {
    if (r != NULL) {
        dta_libera(r->data_inicio);
        mat_libera(r->medicoes);
        free(r);
    }
}

void reg_adicionarLeitura(RegistroTemp *r, int dia_offset, int leitura_idx, double temp) {
    if (r != NULL && r->medicoes != NULL) {
        mat_atribui(r->medicoes, dia_offset, leitura_idx, temp);
    }
}

char* reg_paraString(RegistroTemp *r) {
    char *str_data = dta_paraString(r->data_inicio);
    char *str_mat = mat_paraString(r->medicoes);
    
    char *resultado = (char*) malloc((strlen(str_data) + strlen(str_mat) + 50) * sizeof(char));
    sprintf(resultado, "Data Inicial: %s\nMedicoes:\n%s", str_data, str_mat);
    
    free(str_data);
    free(str_mat);
    return resultado;
}