#include "altura.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Implementação do TAD Altura.
 * A estrutura guarda os valores em metros e centímetros,
 * converte para centímetros e fornece operações de leitura,
 * comparação e conversão para string.
 */

/* Tipo exportado */
/* cria uma medida de comprimento como em m e cm */
struct alt {
    int m, cm;
};

static int converteParacm(const Altura *p) {
    return p->m * 100 + p->cm;
}

/* Funções exportadas */
/* Função cria - Aloca e retorna uma altura (m e cm) */
Altura* alt_cria(int m, int cm) {
    Altura* p = (Altura*) malloc(sizeof(Altura));
    if (p == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    p->m = m;
    p->cm = cm;
    return p;
}

/* Função libera - Libera a memória de uma altura previamente criada */
void alt_libera(Altura* p) {
    free(p);
}

/* Função acessa - Retorna os valores de uma altura */
void alt_acessa(Altura* p, int* m, int* cm) {
    *m = p->m;
    *cm = p->cm;
}

/* Função atribui - Atribui novos valores às partes de uma altura */
void alt_atribui(Altura* p, int m, int cm) {
    p->m = m;
    p->cm = cm;
}

/* Função exibe - Escreve na tela a altura no formato m,cm */
void alt_exibe(Altura* p) {
    printf("\n %d,%02dm", p->m, p->cm);
}

/* Função getAltura - Retorna uma string com os valores da altura no formato m,cm */
char* alt_getAltura(Altura* p) {
    char *pt = (char*) malloc(20 * sizeof(char));
    if (pt == NULL) {
        return NULL;
    }
    sprintf(pt, "%d,%02dm", p->m, p->cm);
    return pt;
}

/* Retorna a altura em centímetros */
double alt_paraCentimetros(const Altura* p) {
    return (double) (p->m * 100 + p->cm);
}

/* Retorna uma string no formato m,cm */
char* alt_paraString(const Altura* p) {
    return alt_getAltura((Altura*) p);
}

/*função compara negativo:se o al1 < alt2, 0 se alt1 == alt2, positivo se o alt1 > alt2 */
int alt_compara(Altura *p1, Altura *p2) {
    int a1 = converteParacm(p1);
    int a2 = converteParacm(p2);
    return a1 - a2;
}