#include <stdio.h>
#include <stdlib.h>
#include "matriz1.h"

int main() {
    /* DADOS TESTES FORNECIDOS: Matriz 3 Lojas (linhas) x 4 Meses (colunas) */
    int num_lojas = 3;
    int num_meses = 4;
    
    Matriz *vendas = criaMatriz(num_lojas, num_meses);

    // Loja 0: Centro
    atribuiMatriz(vendas, 0, 0, 45.5); // Jan
    atribuiMatriz(vendas, 0, 1, 50.0); // Fev
    atribuiMatriz(vendas, 0, 2, 52.8); // Mar
    atribuiMatriz(vendas, 0, 3, 60.1); // Abr
    
    // Loja 1: Shopping
    atribuiMatriz(vendas, 1, 0, 80.2); // Jan
    atribuiMatriz(vendas, 1, 1, 75.0); // Fev
    atribuiMatriz(vendas, 1, 2, 90.5); // Mar
    atribuiMatriz(vendas, 1, 3, 88.0); // Abr
    
    // Loja 2: Zona Sul
    atribuiMatriz(vendas, 2, 0, 30.0); // Jan
    atribuiMatriz(vendas, 2, 1, 32.5); // Fev
    atribuiMatriz(vendas, 2, 2, 28.9); // Mar
    atribuiMatriz(vendas, 2, 3, 35.4); // Abr

    printf("=== MATRIZ DE VENDAS (LOJAS x MESES) ===\n");
    char *str_vendas = matriz_paraString(vendas);
    printf("%s\n", str_vendas);
    free(str_vendas);

    printf("--- FATURAMENTO TOTAL POR LOJA ---\n");
    for (int l = 0; l < num_lojas; l++) {
        double total_loja = 0.0;
        
        // Fixamos a linha (loja) e somamos todas as colunas (meses)
        for (int c = 0; c < num_meses; c++) {
            total_loja += acessaMatriz(vendas, l, c);
        }
        printf("Loja %d: R$ %.2fk\n", l + 1, total_loja);
    }

    printf("\n--- MES COM MAIOR FATURAMENTO DA REDE ---\n");
    int melhor_mes = 0;
    double maior_faturamento_mes = -1.0;
    
    // Invertemos os ciclos: Fixamos a coluna (mês) e somamos as linhas (lojas)
    for (int c = 0; c < num_meses; c++) {
        double total_mes = 0.0;
        
        for (int l = 0; l < num_lojas; l++) {
            total_mes += acessaMatriz(vendas, l, c);
        }
        
        printf("Mes %d: Total R$ %.2fk\n", c + 1, total_mes);
        
        if (total_mes > maior_faturamento_mes) {
            maior_faturamento_mes = total_mes;
            melhor_mes = c + 1;
        }
    }
    
    printf("=> O Mes com maior faturamento foi o Mes %d (R$ %.2fk)\n", melhor_mes, maior_faturamento_mes);

    // Desalocação
    liberaMatriz(vendas);
    
    return 0;
}