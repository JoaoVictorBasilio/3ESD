#include <stdio.h>
#include <stdlib.h>
#include "matriz1.h" // Atualizado para o nome real do seu TAD
#include "conjunto.h"

int main() {
    /* DADOS TESTES FORNECIDOS: Pátio 4x5 */
    
    // 1. Tradução para as funções reais dos seus TADs
    Matriz *patio = criaMatriz(4, 5);
    
    // Assumindo que o seu conj_Cria() não recebe tamanho fixo, como vimos no Ex 5
    Conjunto *zonas_interditadas = conj_Cria(); 

    // Bloqueia as zonas (linhas) 1 e 3 para manutenção (Atenção ao 'I' maiúsculo)
    conj_Insere(zonas_interditadas, 1);
    conj_Insere(zonas_interditadas, 3);

    // Ocupa algumas vagas nas zonas liberadas (0: livre, 1: ocupada)
    atribuiMatriz(patio, 0, 1, 1.0);
    atribuiMatriz(patio, 0, 3, 1.0);
    atribuiMatriz(patio, 2, 0, 1.0);

    printf("=== MAPA DE OCUPACAO DO PATIO ===\n");
    
    // Como o matriz1.c não tem mat_paraString, imprimimos de forma limpa aqui:
    printf("Matriz do Patio:\n");
    for (int l = 0; l < 4; l++) {
        for (int c = 0; c < 5; c++) {
            // Imprime os valores com 1 casa decimal
            printf("%.1f  ", acessaMatriz(patio, l, c));
        }
        printf("\n");
    }

    char *str_conj = conj_paraString(zonas_interditadas);
    printf("\nZonas Interditadas (Linhas bloqueadas): %s\n\n", str_conj);

    // --- CONTAGEM DE VAGAS LIVRES ---
    int vagas_livres = 0;
    
    for (int l = 0; l < 4; l++) {
        // A lógica de ouro: Se a linha atual (l) NÃO (!) pertencer ao conjunto das interditadas
        if (!conj_Pertence(zonas_interditadas, l)) {
            
            // Só então vasculhamos as colunas dessa linha
            for (int c = 0; c < 5; c++) {
                if (acessaMatriz(patio, l, c) == 0.0) {
                    vagas_livres++; // Vaga encontrada!
                }
            }
            
        }
    }

    printf("Total de Vagas Disponiveis para Uso: %d\n", vagas_livres);

    // Desalocação (L maiúsculo no conjunto)
    free(str_conj);
    liberaMatriz(patio);
    conj_Libera(zonas_interditadas);

    return 0;
}