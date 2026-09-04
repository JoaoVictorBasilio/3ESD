
#include <stdio.h>
#include <stdlib.h>
#include "Data.h"
#include "Reserva.h"

int main() {
    tReserva* reservas[3];

    // Criação de reservas utilizando o TAD Data para as datas
    reservas[0] = res_cria("Carlos Silva", 101, 150.0, dta_cria(10, 10, 2026), dta_cria(15, 10, 2026));
    reservas[1] = res_cria("Ana Souza",    204, 220.0, dta_cria(01, 11, 2026), dta_cria(8, 11, 2026));
    reservas[2] = res_cria("Marcos Lima",   305, 300.0, dta_cria(20, 12, 2026), dta_cria(25, 12, 2026));

    printf("=== RELATÓRIO DE RESERVAS ===\n\n");
    float faturamento_total = 0.0;

    for (int i = 0; i < 3; i++) {
        res_exibe(reservas[i]);
        faturamento_total += res_calculaValorTotal(reservas[i]);
        printf("-----------------------------------\n");
    }

    printf("Faturamento Total Previsto: R$ %.2f\n", faturamento_total);

    // Liberação de memória
    for (int i = 0; i < 3; i++) {
        res_libera(reservas[i]);
    }

    return 0;
}
