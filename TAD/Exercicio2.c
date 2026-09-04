#include <stdio.h>
#include <stdlib.h>
#include "Data.h"

typedef struct {
char descricao[50];
float valor_original;
tData* dt_vencimento;
tData* dt_pagamento;
} tConta;

// Função auxiliar para simplificar a criação das contas nos testes
tConta* criar_conta(const char* desc, float valor, int diaV, int mesV, int anoV, int diaP, int mesP, int anoP) {
tConta* c = (tConta*) malloc(sizeof(tConta));
sprintf(c->descricao, "%s", desc);
c->valor_original = valor;
c->dt_vencimento = dta_cria(diaV, mesV, anoV);
c->dt_pagamento = dta_cria(diaP, mesP, anoP);
return c;
}

int main() {
// Vetor de ponteiros para struct tConta alocado e preenchido
tConta* contas[7];
contas[0] = criar_conta("Conta de Luz", 200.0, 20, 9, 2026, 5, 9, 2026); // 15 dias antes (Desconto 10%)
contas[1] = criar_conta("Internet", 100.0, 15, 9, 2026, 15, 9, 2026); // No dia (Valor normal)
contas[2] = criar_conta("Cartao Credito", 500.0, 10, 9, 2026, 15, 9, 2026); // 5 dias de atraso (Juros)
contas[3] = criar_conta("Condominio", 800.0, 10, 10, 2026, 1, 10, 2026); // 9 dias antes (Sem desconto)
contas[4] = criar_conta("Plano de Saude", 350.0, 30, 9, 2026, 20, 9, 2026); // 10 dias antes (Desconto 10%)
contas[5] = criar_conta("IPVA", 1200.0, 5, 8, 2026, 25, 8, 2026); // 20 dias de atraso (Juros)
contas[6] = criar_conta("Academia", 120.0, 1, 9, 2026, 1, 9, 2026); // No dia (Valor normal)
int total_contas = 7;
int i;
// TODO: Escreva a partir daqui a lógica para calcular o valor final de cada conta
// utilizando as funções do TAD Data (dta_diferenca, dta_exibe/dta_getData, dta_libera, etc.)

for(i = 0; i < total_contas; i++) {
    int status = dta_compara(contas[i]->dt_pagamento, contas[i]->dt_vencimento);
    int dias = dta_diferenca(contas[i]->dt_pagamento, contas[i]->dt_vencimento) -1;
    float valor_final = contas[i]->valor_original;

    if (status == -1 && dias >= 10) {
        valor_final = valor_final - (valor_final * 0.1);
    } else if (status == 1){
        valor_final = valor_final + (valor_final * 0.001 * dias);
    }
    printf("Conta: %s\n", contas[i]->descricao);
        
        printf("Vencimento: ");
        dta_exibe(contas[i]->dt_vencimento); 
        
        printf(" | Pagamento: ");
        dta_exibe(contas[i]->dt_pagamento);
        
        printf("\nValor Original: R$ %.2f\n", contas[i]->valor_original);
        printf("Valor Final:    R$ %.2f\n", valor_final);
        printf("----------------------------------------\n");

        dta_libera(contas[i]->dt_vencimento);
        dta_libera(contas[i]->dt_pagamento);
        free(contas[i]);
}
return 0;
}