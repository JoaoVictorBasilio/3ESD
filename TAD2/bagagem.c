#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bagagem.h"

/*
 * Implementação do TAD Bagagem.
 * Cada bagagem contém quatro dimensões internas (altura, largura,
 * comprimento e peso), que são usadas para montar uma descrição visual
 * e calcular o volume em metros cúbicos.
 */

struct bagagem {
    Altura *altura;
    Altura *largura;
    Altura *comprimento;
    Massa *peso;
};

Bagagem* bag_cria(Altura *alt, Altura *larg, Altura *comp, Massa *peso) {
    Bagagem *b = (Bagagem*) malloc(sizeof(Bagagem));
    if (b != NULL) {
        b->altura = alt;
        b->largura = larg;
        b->comprimento = comp;
        b->peso = peso;
    }
    return b;
}

void bag_libera(Bagagem *b) {
    if (b != NULL) {
        alt_libera(b->altura);
        alt_libera(b->largura);
        alt_libera(b->comprimento);
        mas_libera(b->peso);
        free(b);
    }
}

char* bag_paraString(Bagagem *b) {
    if (b == NULL) {
        return NULL;
    }

    char *s_alt = alt_paraString(b->altura);
    char *s_lar = alt_paraString(b->largura);
    char *s_comp = alt_paraString(b->comprimento);
    char *s_peso = mas_paraString(b->peso);

    char *resultado = (char*) malloc(200 * sizeof(char));
    if (resultado != NULL) {
        sprintf(resultado, "Dimensoes: [%s x %s x %s] - Peso: %s", s_alt, s_lar, s_comp, s_peso);
    }

    free(s_alt);
    free(s_lar);
    free(s_comp);
    free(s_peso);

    return resultado;
}

double bag_calculaVolumeM3(Bagagem *b) {
    if (b == NULL) {
        return 0.0;
    }

    double m_alt = alt_paraCentimetros(b->altura) / 100.0;
    double m_lar = alt_paraCentimetros(b->largura) / 100.0;
    double m_comp = alt_paraCentimetros(b->comprimento) / 100.0;

    return m_alt * m_lar * m_comp;
}