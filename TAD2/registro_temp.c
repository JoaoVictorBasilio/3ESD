#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro_temp.h"

struct registro_temp
{
    Data *data_inicio;
    Matriz *medicoes;
};

RegistroTemp* reg_cria(Data* data_inicio, int num_dias, int leituras_por_dia){
    if(data_inicio == NULL || num_dias <= 0 || leituras_por_dia <= 0){
        return NULL;
    }

    RegistroTemp* r = (RegistroTemp*) malloc(sizeof(RegistroTemp));

    r->data_inicio = data_inicio;
    r->medicoes = criaMatriz(num_dias,leituras_por_dia);

    if(r->medicoes == NULL){
        free(r);
        return NULL;
    }

    return r;
}

void reg_libera(RegistroTemp* r){
    if(r != NULL){
        dta_libera(r->data_inicio);
        liberaMatriz(r->medicoes);
        free(r);
    }
}

void reg_adicionarLeitura(RegistroTemp* r, int dia_offset, int leitura_idx, int temp){
    if(r == NULL || r->medicoes == NULL){
        return;
    }

    atribuiMatriz(r->medicoes, dia_offset,leitura_idx,temp);
}

char* reg_paraString(const RegistroTemp* r){
    if (r == NULL)
    {
        return NULL;
    }

    char* str_dta = dta_paraString(r->data_inicio);
    if(str_dta == NULL){
        return NULL;
    }

    int linhas = linhasMatriz(r->medicoes);
    int colunas = colunasMatriz(r->medicoes);

    size_t tamanho_seguro = strlen(str_dta) + 50 + (linhas * colunas * 6) + linhas;
    char* relatorio = (char*) calloc(tamanho_seguro, sizeof(char));
    

    if(relatorio != NULL){
        sprintf(relatorio, "Data Base %s\nMedicoes (Dias x Horarios): \n", str_dta);

        char temp_str[16];
        for(int i = 0; i < linhas; i++){
            for(int j = 0; j < colunas; j++){
                int valor_temp = acessaMatriz(r->medicoes, i, j);
                sprintf(temp_str, "%4d", valor_temp);
                strcat(relatorio, temp_str);
            }
            strcat(relatorio, "\n");
        }
    }

    free(str_dta);
}
