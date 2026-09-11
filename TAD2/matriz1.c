#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz1.h"

/*
 * Implementação do TAD Matriz.
 * A estrutura é uma matriz dinâmica de inteiros, organizada em linhas,
 * colunas e ponteiros para as linhas internas. A partir dela são feitas
 * operações de leitura, escrita, soma e conversão para texto.
 */

struct matriz {
    int lin;
    int col;
    int **val;
};

static int dentro(const Matriz* m, int i, int j) {
    return (m && i >= 0 && i < m->lin && j >= 0 && j < m->col);
}

Matriz* criaMatriz(int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0) return NULL;

    Matriz* m = (Matriz*) malloc(sizeof(Matriz));
    if (!m) return NULL;

    m->lin = linhas;
    m->col = colunas;

    m->val = (int**) malloc(linhas * sizeof(int*));
    if (!m->val) { free(m); return NULL; }

    for (int i = 0; i < linhas; i++) {
        m->val[i] = (int*) calloc(colunas, sizeof(int));
        if (!m->val[i]) {
            for (int k = 0; k < i; k++) free(m->val[k]);
            free(m->val);
            free(m);
            return NULL;
        }
    }
    return m;
}

void liberaMatriz(Matriz* m) {
    if (!m) return;
    for (int i = 0; i < m->lin; i++) free(m->val[i]);
    free(m->val);
    free(m);
}

int linhasMatriz(const Matriz* m) { return m ? m->lin : 0; }
int colunasMatriz(const Matriz* m) { return m ? m->col : 0; }

void atribuiMatriz(Matriz* m, int linha, int coluna, int valor) {
    if (dentro(m, linha, coluna)) m->val[linha][coluna] = valor;
}

int acessaMatriz(const Matriz* m, int linha, int coluna) {
    if (dentro(m, linha, coluna)) return m->val[linha][coluna];
    return 0;
}

int acessaMatrizSafe(const Matriz* m, int linha, int coluna, int* out) {
    if (!out) return 0;
    if (!dentro(m, linha, coluna)) return 0;
    *out = m->val[linha][coluna];
    return 1;
}

void imprimeMatriz(const Matriz* m) {
    if (!m) { printf("(matriz nula)\n"); return; }
    for (int i = 0; i < m->lin; i++) {
        for (int j = 0; j < m->col; j++) {
            printf("%4d", m->val[i][j]);
        }
        printf("\n");
    }
}

int somaLinhaMatriz(const Matriz* m, int linha, long long* soma_out) {
    if (!m || !soma_out) return 0;
    if (linha < 0 || linha >= m->lin) return 0;
    long long s = 0;
    for (int j = 0; j < m->col; j++) s += m->val[linha][j];
    *soma_out = s;
    return 1;
}

int somaColunaMatriz(const Matriz* m, int coluna, long long* soma_out) {
    if (!m || !soma_out) return 0;
    if (coluna < 0 || coluna >= m->col) return 0;
    long long s = 0;
    for (int i = 0; i < m->lin; i++) s += m->val[i][coluna];
    *soma_out = s;
    return 1;
}

Matriz* somaMatrizes(const Matriz* A, const Matriz* B) {
    if (!A || !B) return NULL;
    if (A->lin != B->lin || A->col != B->col) return NULL;

    Matriz* R = criaMatriz(A->lin, A->col);
    if (!R) return NULL;

    for (int i = 0; i < A->lin; i++) {
        for (int j = 0; j < A->col; j++) {
            R->val[i][j] = A->val[i][j] + B->val[i][j];
        }
    }
    return R;
}

Matriz* mat_cria(int linhas, int colunas) {
    return criaMatriz(linhas, colunas);
}

void mat_libera(Matriz* m) {
    liberaMatriz(m);
}

void mat_atribui(Matriz* m, int linha, int coluna, double valor) {
    atribuiMatriz(m, linha, coluna, (int) valor);
}

char* mat_paraString(const Matriz* m) {
    if (m == NULL) {
        char *str = (char*) malloc(8 * sizeof(char));
        sprintf(str, "NULL");
        return str;
    }

    size_t cap = (size_t) (m->lin * m->col * 12 + 32);
    char *str = (char*) malloc(cap);
    if (str == NULL) {
        return NULL;
    }

    int offset = 0;
    offset += sprintf(str + offset, "[\n");
    for (int i = 0; i < m->lin; i++) {
        for (int j = 0; j < m->col; j++) {
            offset += sprintf(str + offset, "%s%4d", (j == 0) ? "  " : " ", m->val[i][j]);
        }
        offset += sprintf(str + offset, "\n");
    }
    sprintf(str + offset, "]");
    return str;
}