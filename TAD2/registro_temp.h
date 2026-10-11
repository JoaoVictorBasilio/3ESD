#ifndef REGISTRO_TEMP_H
#define REGISTRO_TEMP_H

#include "data.h"
#include "matriz1.h"

typedef struct registro_temp RegistroTemp;

RegistroTemp* reg_cria(Data* data_inicio, int num_dias, int leituras_por_dia);

void reg_libera(RegistroTemp* r);

void reg_adicionarLeitura(RegistroTemp* r, int dia_offset, int leitura_idx, int temp);

char* reg_paraString(const RegistroTemp* r);

#endif