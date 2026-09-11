#ifndef MATRIZ1_H
#define MATRIZ1_H

#include <stddef.h>

/*
 * TAD Matriz
 * ---------
 * Representa uma matriz numérica bidimensional com operações de criação,
 * acesso, soma de linhas/colunas e soma de duas matrizes.
 */

// Tipo opaco
typedef struct matriz Matriz;

// Cria e libera
Matriz* criaMatriz(int linhas, int colunas);
void liberaMatriz(Matriz* m);

// Dimensões
int linhasMatriz(const Matriz* m);
int colunasMatriz(const Matriz* m);

// Atribui e acessa
void atribuiMatriz(Matriz* m, int linha, int coluna, int valor);

// Versão simples: retorna 0 se fora do intervalo
int acessaMatriz(const Matriz* m, int linha, int coluna);

// Versão segura: retorna 1 (ok) ou 0 (falha); valor sai em *out
int acessaMatrizSafe(const Matriz* m, int linha, int coluna, int* out);

// Impressão
void imprimeMatriz(const Matriz* m);

// --------- Operações pedidas ---------
int somaLinhaMatriz(const Matriz* m, int linha, long long* soma_out);
int somaColunaMatriz(const Matriz* m, int coluna, long long* soma_out);
Matriz* somaMatrizes(const Matriz* A, const Matriz* B);

// Funções de compatibilidade com nomes usados em outros módulos
Matriz* mat_cria(int linhas, int colunas);
void mat_libera(Matriz* m);
void mat_atribui(Matriz* m, int linha, int coluna, double valor);
char* mat_paraString(const Matriz* m);

#endif