#include <stdio.h>
#include <stdlib.h>
#include "data.h"

typedef struct {
    char descricao[40];
    double valor_original;
    Data *vencimento;
    Data *pagamento;
} Titulo;

int main() {
    /* DADOS TESTES FORNECIDOS (Corrigidos os zeros à esquerda) */
    Titulo contas[3] = {
        {"Aluguel do Galpao", 5000.00, dta_cria(20, 10, 2026), dta_cria(5, 10, 2026)},   // 15 dias antecedência (10% desc)
        {"Fornecedor Materia-Prima", 2500.00, dta_cria(15, 10, 2026), dta_cria(15, 10, 2026)}, // No dia exato
        {"Servico de Manutencao", 1200.00, dta_cria(10, 10, 2026), dta_cria(15, 10, 2026)} // 5 dias atraso (Juros)
    };
    
    printf("=== LIQUIDACAO DE TITULOS FINANCEIROS ===\n\n");
    
    for (int i = 0; i < 3; i++) {
        // A função dta_diferenca faz d1 - d2 (Vencimento - Pagamento)
        // - Se for POSITIVO: Pagou antes do vencimento (adiantado)
        // - Se for NEGATIVO: Pagou depois do vencimento (atrasado)
        int dias_diff = dta_diferenca(contas[i].vencimento, contas[i].pagamento);
        
        double valor_final = contas[i].valor_original;
        
        if (dias_diff >= 10) {
            // Regra 1: Pagou com 10 ou mais dias de antecedência ganha 10% de desconto
            valor_final *= 0.90; 
        } else if (dias_diff < 0) {
            // Regra 2: Pagou atrasado. -dias_diff converte o número negativo para positivo.
            int dias_atraso = -dias_diff;
            // Multa de 0.1% (0.001) por cada dia de atraso
            valor_final += contas[i].valor_original * (0.001 * dias_atraso); 
        }
        
        char *str_venc = dta_paraString(contas[i].vencimento);
        char *str_pag = dta_paraString(contas[i].pagamento);
        
        printf("Titulo: %s\n", contas[i].descricao);
        printf("Vencimento: %s | Pagamento: %s\n", str_venc, str_pag);
        printf("Valor Original: R$ %.2f | Valor Pago: R$ %.2f\n\n", contas[i].valor_original, valor_final);
        
        // Limpeza de memória
        free(str_venc);
        free(str_pag);
        dta_libera(contas[i].vencimento);
        dta_libera(contas[i].pagamento);
    }
    
    return 0;
}