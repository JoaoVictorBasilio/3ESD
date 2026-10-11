#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bagagem.h"

struct bagagem {
    Altura *altura;
    Altura *largura;
    Altura *comprimento;
    Massa *peso;
};

Bagagem* bag_cria(Altura* alt, Altura* larg, Altura* comp, Massa* peso){
    if(alt == NULL || larg == NULL || comp == NULL || peso == NULL){
        return NULL;
    }

    Bagagem* b = (Bagagem*) malloc(sizeof(Bagagem));
    if(b == NULL){
        return NULL;
    }

    b->altura = alt;
    b->largura = larg;
    b->comprimento = comp;
    b->peso = peso;

    return b;
}

void bag_libera(Bagagem* b){
    if(b != NULL){
        alt_libera(b->altura);
        alt_libera(b->largura);
        alt_libera(b->comprimento);
        mas_libera(b->peso);
        free(b);
    }
}

char* bag_paraString(const Bagagem* b){
    if (b == NULL) return NULL;

    // Usando as funções originais do TAD da professora
    char* str_alt = alt_getAltura(b->altura);
    char* str_larg = alt_getAltura(b->largura);
    char* str_comp = alt_getAltura(b->comprimento);
    char* str_peso = mas_paraString(b->peso); 

    if(str_alt == NULL || str_larg == NULL || str_comp == NULL || str_peso == NULL){
        free(str_alt); free(str_larg); free(str_comp); free(str_peso);
        return NULL;
    }

    size_t tamanho = strlen(str_alt) + strlen(str_larg) + strlen(str_comp) + strlen(str_peso) + 40;
    char* str_total = (char*) malloc(tamanho * sizeof(char));

    if (str_total != NULL) {
        sprintf(str_total, "Dimensoes: [%s x %s x %s] - Peso: %s", str_alt, str_larg, str_comp, str_peso);
    }

    free(str_alt);
    free(str_larg);
    free(str_comp);
    free(str_peso);
 
    return str_total;
}

float bag_calculaVolumeM3(const Bagagem* b){
    if(b == NULL){
        return 0.0f;
    }

    // Usamos os getters em vez de tentar furar o bloqueio da estrutura
    float alt_cm = (float) alt_paraCentimetros(b->altura);
    float larg_cm = (float) alt_paraCentimetros(b->largura);
    float comp_cm = (float) alt_paraCentimetros(b->comprimento);

    // Calcula o volume em cm cúbicos
    float volume_cm3 = alt_cm * larg_cm * comp_cm;

    // Converte para metros cúbicos
    return volume_cm3 / 1000000.0f;
}

Massa* bag_getMassa(const Bagagem* b) {
    if (b == NULL) return NULL;
    return b->peso;
}