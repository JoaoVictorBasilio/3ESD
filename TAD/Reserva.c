#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reserva.h"

struct reserva {
    char hospede[50];
    int quarto;
    float diaria;
    tData* dt_checkin;
    tData* dt_checkout;
};


tReserva* res_cria(const char* hospede, int quarto, float diaria, tData* dt_checkin, tData* dt_checkout) {

    tReserva* r = (tReserva*) malloc(sizeof(struct reserva));
    
    strcpy(r->hospede, hospede);
    
    r->quarto = quarto;
    r->diaria = diaria;
    r->dt_checkin = dt_checkin;
    r->dt_checkout = dt_checkout;
    
    return r;
}

void res_libera(tReserva* r) {

    dta_libera(r->dt_checkin);
    dta_libera(r->dt_checkout);
    free(r);
}

int res_calculaDiarias(tReserva* r) {

    return dta_diferenca(r->dt_checkout, r->dt_checkin) - 1;
}

float res_calculaValorTotal(tReserva* r) {

    int dias = res_calculaDiarias(r);
    return dias * r->diaria;
}

void res_exibe(tReserva* r) {
    printf("Hospede: %s\n", r->hospede);
    printf("Quarto: %d\n", r->quarto);
    printf("Valor da Diaria: R$ %.2f\n", r->diaria);
    
    printf("Check-in: ");
    dta_exibe(r->dt_checkin);
    
    printf("\nCheck-out: ");
    dta_exibe(r->dt_checkout);
    
    printf("\nQtd. de Diarias: %d\n", res_calculaDiarias(r));
    printf("Valor Total: R$ %.2f\n", res_calculaValorTotal(r));
}