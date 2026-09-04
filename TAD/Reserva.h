#ifndef RESERVA_H
#define RESERVA_H

#include "Data.h"

typedef struct reserva tReserva;

/* Função cria: Aloca dinamicamente uma reserva com hóspede, número do quarto, 
   valor da diária e datas de check-in e check-out */
tReserva* res_cria(const char* hospede, int quarto, float diaria, 
                   tData* dt_checkin, tData* dt_checkout);

/* Função libera: Desaloca a memória da reserva e das datas internas */
void res_libera(tReserva* r);

/* Retorna a quantidade de diárias (diferença em dias entre check-out e check-in) */
int res_calculaDiarias(tReserva* r);

/* Retorna o valor total da hospedagem (diárias * valor da diária) */
float res_calculaValorTotal(tReserva* r);

/* Imprime o resumo da reserva na tela com hóspede, quarto, datas e valor total */
void res_exibe(tReserva* r);

#endif
