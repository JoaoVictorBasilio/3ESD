/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
/**
 * ================================================================
 * MAIN.C - PROGRAMA PRINCIPAL DO SISTEMA DE BIBLIOTECA
 * ================================================================
 * 
 * Programa que demonstra o uso do TAD Livro e seus TADs
 * auxiliares (Valor e Dias).
 * 
 * Autor: [João Victor Ferreira Basilio Dourado]
 *  
 * ================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

/**
 * criar_livro - Função auxiliar para criar livros com dados pré-definidos
 * 
 * @param titulo:   Título do livro
 * @param val_r:    Reais da multa diária
 * @param val_c:    Centavos da multa diária
 * @param dias_sem: Semanas de atraso
 * @param dias_dia: Dias adicionais de atraso
 * 
 * @return: Ponteiro para o Livro criado, ou NULL em erro
 */
Livro* criar_livro(const char* titulo, int val_r, int val_c, int dias_sem, int dias_dia) {
    Valor* v = val_cria(val_r, val_c);
    Dias* d = dias_cria(dias_sem, dias_dia);
    Livro* liv = liv_cria(titulo, v, d);
    return liv;
}

/**
 * main - Função principal do programa
 */
int main() {
    /* ============================================================
     * LIVROS EM ATRASO
     * ============================================================ */
    
    Livro* biblioteca[6];
    
    /* Livro 1: Dom Quixote - R$ 2,50/dia - 0 semanas, 3 dias */
    biblioteca[0] = criar_livro("Dom Quixote", 2, 50, 0, 3);
    
    /* Livro 2: 1984 - R$ 3,00/dia - 1 semana, 2 dias */
    biblioteca[1] = criar_livro("1984", 3, 0, 1, 2);
    
    /* Livro 3: O Pequeno Príncipe - R$ 1,50/dia - 0 semanas, 5 dias */
    biblioteca[2] = criar_livro("O Pequeno Príncipe", 1, 50, 0, 5);
    
    /* Livro 4: A Arte da Guerra - R$ 4,00/dia - 2 semanas, 0 dias */
    biblioteca[3] = criar_livro("A Arte da Guerra", 4, 0, 2, 0);
    
    /* Livro 5: Harry Potter - R$ 2,00/dia - 0 semanas, 1 dia */
    biblioteca[4] = criar_livro("Harry Potter", 2, 0, 0, 1);
    
    /* Livro 6: O Hobbit - R$ 3,50/dia - 1 semana, 6 dias */
    biblioteca[5] = criar_livro("O Hobbit", 3, 50, 1, 6);
    
    float desconto_vip = 15.0f;    /* 15% de desconto para VIP */
    float limite_multa = 50.0f;    /* R$ 50,00 limite para notificação */
    
    printf("============================================================\n");
    printf("    SISTEMA DE BIBLIOTECA - MULTAS POR ATRASO\n");
    printf("============================================================\n\n");
    
    printf("Limite para notificação: R$ %.2f\n", limite_multa);
    printf("Desconto VIP: %.1f%%\n\n", desconto_vip);
    
    /* ============================================================
     * PARTE 1: EXIBIÇÃO DOS LIVROS
     * ============================================================ */
    
    printf("--- LIVROS EM ATRASO ---\n\n");
    
    for (int i = 0; i < 6; i++) {
        char* info = liv_paraString(biblioteca[i]);
        if (info != NULL) {
            printf("%d. %s\n\n", i + 1, info);
            
        }
    }
    
    /* ============================================================
     * PARTE 2: CÁLCULO DO TOTAL DAS MULTAS
     * ============================================================ */
    
    printf("--- CÁLCULO DO TOTAL DAS MULTAS ---\n\n");
    
    /* Inicializa o total com R$ 0,00 */
    Valor* total_multas = val_cria(0, 0);
    
    for (int i = 0; i < 6; i++) {
        Valor* m = liv_calculaMulta(biblioteca[i]);
        Valor* aux = val_soma(total_multas, m);
        
        val_libera(m);
        val_libera(total_multas);
        total_multas = aux;
    }
    
    char* str_total = val_paraString(total_multas);
    printf("Multa total acumulada de todos os livros: %s\n", str_total);
    free(str_total);
    
    /* ============================================================
     * PARTE 3: DESCONTO VIP E NOTIFICAÇÃO
     * ============================================================ */
    
    printf("\n--- DESCONTO VIP E NOTIFICAÇÃO ---\n\n");
    
    Valor* limite_valor = val_cria((int)limite_multa, 0);
    
    for (int i = 0; i < 6; i++) {
        Valor* m_total = liv_calculaMulta(biblioteca[i]);
        Valor* m_vip = liv_aplicaDescontoVIP(biblioteca[i], desconto_vip);
        
        char* str_m_total = val_paraString(m_total);
        char* str_m_vip = val_paraString(m_vip);
        
        printf("%s:\n", liv_getTitulo(biblioteca[i]));
        printf("  - Multa sem desconto: %s\n", str_m_total);
        printf("  - Multa VIP (%.1f%% desc.): %s\n", desconto_vip, str_m_vip);
        
        if (val_compara(m_total, limite_valor) > 0) {
            printf("  -> NOTIFICAÇÃO ENVIADA: Multa excede o limite de R$ %.2f!\n", limite_multa);
        }
        
        printf("\n");
        
        free(str_m_total);
        free(str_m_vip);
        val_libera(m_total);
        val_libera(m_vip);
    }
    
    val_libera(limite_valor);
    
    /* ============================================================
     * PARTE 4: LIVRO COM MAIOR MULTA DIÁRIA
     * ============================================================ */
    
    printf("\n--- LIVRO COM MAIOR MULTA DIÁRIA ---\n\n");
    
    /* Encontra o livro com maior multa diária */
    Livro* maior_multa_livro = biblioteca[0];
    for (int i = 1; i < 6; i++) {
        Valor* v_atual = liv_getMultaDiaria(biblioteca[i]);
        Valor* v_maior = liv_getMultaDiaria(maior_multa_livro);
        
        if (val_compara(v_atual, v_maior) > 0) {
            maior_multa_livro = biblioteca[i];
        }
    }
    
    char* str_maior_diaria = val_paraString(liv_getMultaDiaria(maior_multa_livro));
    printf("O livro com maior multa diária é '%s' com %s/dia.\n", 
           liv_getTitulo(maior_multa_livro), str_maior_diaria);
    free(str_maior_diaria);    
   
    /* ============================================================
     * PARTE 5: LIMPEZA DE MEMÓRIA
     * ============================================================ */
    
    printf("\n--- LIBERANDO MEMÓRIA ---\n\n");
    
   
    /* Libera cada livro (em cascata: título, multa diária, atraso e estrutura) */
    for (int i = 0; i < 6; i++) {
        printf("Liberando livro %d...\n", i + 1);
        liv_libera(biblioteca[i]);
    }
    
    printf("\nMemória liberada com sucesso!\n");
    
    return 0;
}