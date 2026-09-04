#include <stdio.h>
#include <stdlib.h>
#include "Data.h"

typedef struct {
    int dia;
    int mes;
    int ano;
} DataSimples;

typedef struct {
    char descricao[50];
    float valor_original;
    DataSimples dt_vencimento;
    DataSimples dt_pagamento;
} tConta;

int main() {
    // Declaração das 7 contas
    tConta c1 = {"Conta de Luz",      200.0, {20, 9, 2026}, {5, 9, 2026}};   // 15 dias antes (Desconto 10%)
    tConta c2 = {"Internet",          100.0, {15, 9, 2026}, {15, 9, 2026}};  // No dia (Valor normal)
    tConta c3 = {"Cartao Credito",    500.0, {10, 9, 2026}, {15, 9, 2026}};  // 5 dias de atraso (Juros)
    tConta c4 = {"Condominio",       800.0, {10, 10, 2026}, {1, 10, 2026}};  // 9 dias antes (Sem desconto)
    tConta c5 = {"Plano de Saude",    350.0, {30, 9, 2026}, {20, 9, 2026}};  // 10 dias antes (Desconto 10%)
    tConta c6 = {"IPVA",             1200.0, {05, 8, 2026}, {25, 8, 2026}};  // 20 dias de atraso (Juros)
    tConta c7 = {"Academia",         120.0, {01, 9, 2026}, {01, 9, 2026}};  // No dia (Valor normal)

    // Vetor de ponteiros para struct tConta preenchido
    tConta* contas[7] = {&c1, &c2, &c3, &c4, &c5, &c6, &c7};
    int total_contas = 7;
    int i;

    // TODO: Escreva a partir daqui a lógica para calcular o valor final de cada conta
    // utilizando as funções do TAD Data (dta_cria, dta_diferenca, dta_exibe, dta_libera, etc.)

    for (i = 0; i < total_contas; i++) {
        tData* tad_venc = dta_cria(contas[i]->dt_vencimento.dia, contas[i]->dt_vencimento.mes, contas[i]->dt_vencimento.ano);
                                   
        tData* tad_pag = dta_cria(contas[i]->dt_pagamento.dia, contas[i]->dt_pagamento.mes, contas[i]->dt_pagamento.ano);

        int status = dta_compara(tad_pag, tad_venc);
        int dias = dta_diferenca(tad_pag, tad_venc) - 1;
        float valor_final = contas[i]->valor_original;

        if (status == -1 && dias >= 10) {
            valor_final = valor_final - (valor_final * 0.10);
        } else if (status == 1) {
            valor_final = valor_final + (valor_final * 0.001 * dias);
        }

        printf("Conta: %s\n", contas[i]->descricao);
        
        printf("Vencimento: ");
        dta_exibe(tad_venc); 
        
        printf(" | Pagamento: ");
        dta_exibe(tad_pag);
        
        printf("\nValor Original: R$ %.2f\n", contas[i]->valor_original);
        printf("Valor Final:    R$ %.2f\n", valor_final);
        printf("----------------------------------------\n");

        dta_libera(tad_venc);
        dta_libera(tad_pag);
    }

    return 0;
}
