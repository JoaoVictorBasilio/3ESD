#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"

/* Retorna a quantidade de elementos presentes simultaneamente em c1 e c2 */
int conj_intersecao_qtd(Conjunto *c1, Conjunto *c2) {
    int qtd = 0;
    
    // Testa IDs de filmes típicos cadastrados (Universo de 100 a 120)
    for (int id = 100; id <= 120; id++) {
        // Se o filme (id) estiver no Histórico A E no Histórico B
        if (conj_Pertence(c1, id) && conj_Pertence(c2, id)) {
            qtd++;
        }
    }
    return qtd;
}

int main() {
    /* DADOS TESTES FORNECIDOS */
    // Nota: Removi o "10" dos parênteses porque o teu conj_Cria() não pede tamanho
    Conjunto *usrA = conj_Cria();
    Conjunto *usrB = conj_Cria();

    // Histórico de filmes assistidos (IDs) pelo Usuário A
    conj_Insere(usrA, 101);
    conj_Insere(usrA, 102);
    conj_Insere(usrA, 105);
    conj_Insere(usrA, 108);

    // Histórico de filmes assistidos (IDs) pelo Usuário B
    conj_Insere(usrB, 102);
    conj_Insere(usrB, 105);
    conj_Insere(usrB, 110);
    conj_Insere(usrB, 112);
    conj_Insere(usrB, 115);

    printf("=== ANALISE DE AFINIDADE DE USUARIOS (STREAMING) ===\n");
    
    char *strA = conj_paraString(usrA);
    char *strB = conj_paraString(usrB);
    
    printf("Usuario A: %s\n", strA);
    printf("Usuario B: %s\n", strB);

    // Cria um novo conjunto que é a união dos dois
    Conjunto *uniao = conj_Uniao(usrA, usrB);
    char *str_uniao = conj_paraString(uniao);
    
    // Chama a nossa função auxiliar
    int qtd_intersecao = conj_intersecao_qtd(usrA, usrB);
    
    printf("Uniao dos Filmes (Catalogo Total): %s\n", str_uniao);
    printf("Filmes em Comum (Afinidade): %d\n", qtd_intersecao);

    // Limpeza de memória obrigatória
    free(strA);
    free(strB);
    free(str_uniao);
    
    // Libera os conjuntos com L maiúsculo (como no teu TAD base)
    conj_Libera(usrA);
    conj_Libera(usrB);
    conj_Libera(uniao);

    return 0;
}