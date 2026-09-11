#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "conj.h"

/*
 * Implementação do conjunto.
 * A estrutura guarda um vetor de inteiros e um contador de tamanho.
 * Cada operação valida se o elemento já existe antes de inserir ou remover.
 */

#define MAX_ELEM 20

struct tconjunto {
    int elementos[MAX_ELEM];
    int size;
};

static int busca_posicao(const TConjunto *c, int x) {
    if (c == NULL) {
        return -1;
    }
    for (int i = 0; i < c->size; i++) {
        if (c->elementos[i] == x) {
            return i;
        }
    }
    return -1;
}

TConjunto* conj_cria(void) {
    TConjunto *c = (TConjunto*) malloc(sizeof(TConjunto));
    if (c == NULL) {
        return NULL;
    }
    c->size = 0;
    return c;
}

void conj_libera(TConjunto *c) {
    free(c);
}

TConjunto* conj_insere(TConjunto *c, int x) {
    if (c == NULL || c->size >= MAX_ELEM || busca_posicao(c, x) >= 0) {
        return c;
    }
    c->elementos[c->size++] = x;
    return c;
}

int conj_ehMembro(const TConjunto *c, int x) {
    return busca_posicao(c, x) >= 0;
}

TConjunto* conj_remove(TConjunto *c, int x) {
    if (c == NULL) {
        return NULL;
    }

    int pos = busca_posicao(c, x);
    if (pos < 0) {
        return c;
    }

    for (int i = pos; i < c->size - 1; i++) {
        c->elementos[i] = c->elementos[i + 1];
    }
    c->size--;
    return c;
}

TConjunto* conj_uniao(const TConjunto *a, const TConjunto *b) {
    TConjunto *r = conj_cria();
    if (r == NULL) {
        return NULL;
    }

    for (int i = 0; a != NULL && i < a->size; i++) {
        conj_insere(r, a->elementos[i]);
    }
    for (int i = 0; b != NULL && i < b->size; i++) {
        conj_insere(r, b->elementos[i]);
    }
    return r;
}

TConjunto* conj_intersecao(const TConjunto *a, const TConjunto *b) {
    TConjunto *r = conj_cria();
    if (r == NULL) {
        return NULL;
    }

    if (a == NULL || b == NULL) {
        return r;
    }

    for (int i = 0; i < a->size; i++) {
        if (conj_ehMembro(b, a->elementos[i])) {
            conj_insere(r, a->elementos[i]);
        }
    }
    return r;
}

TConjunto* conj_diferenca(const TConjunto *a, const TConjunto *b) {
    TConjunto *r = conj_cria();
    if (r == NULL) {
        return NULL;
    }

    if (a == NULL) {
        return r;
    }

    for (int i = 0; i < a->size; i++) {
        if (!conj_ehMembro(b, a->elementos[i])) {
            conj_insere(r, a->elementos[i]);
        }
    }
    return r;
}

void conj_exibe(const TConjunto *c) {
    if (c == NULL) {
        printf("{}\n");
        return;
    }

    printf("{ ");
    for (int i = 0; i < c->size; i++) {
        printf("%d%s", c->elementos[i], (i + 1 < c->size) ? ", " : "");
    }
    printf(" }\n");
}

char* conj_paraString(const TConjunto *c) {
    char *str = (char*) malloc(200 * sizeof(char));
    if (str == NULL) {
        return NULL;
    }
    if (c == NULL || c->size == 0) {
        sprintf(str, "{}");
        return str;
    }

    int offset = 0;
    offset += sprintf(str + offset, "{");
    for (int i = 0; i < c->size; i++) {
        offset += sprintf(str + offset, "%s%d", (i == 0) ? "" : ", ", c->elementos[i]);
    }
    sprintf(str + offset, "}");
    return str;
}
