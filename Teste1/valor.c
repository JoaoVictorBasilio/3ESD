/**
 * ================================================================
 * VALOR.C - IMPLEMENTAÇÃO DO TAD VALOR
 * ================================================================
 * 
 * Implementação das operações do TAD Valor (valores monetários).
 * 
 * Autor: Professor
 * 
 * ================================================================
 */

#include "valor.h"
struct valor {
    int reais;
    int centavos;
};
/**
 * val_cria - Cria um novo Valor
 * 
 * Implementação:
 *   1. Verifica se parâmetros são válidos (reais >= 0 e centavos >= 0)
 *   2. Aloca memória para a estrutura Valor
 *   3. Ajusta centavos >= 100 (ex: 150 centavos -> 1 real e 50 centavos)
 *   4. Inicializa os campos reais e centavos
 *   5. Retorna o ponteiro para o Valor criado
 */
Valor* val_cria(int reais, int centavos) {
    /* Validação dos parâmetros */
    if (reais < 0 || centavos < 0) {
        return NULL;
    }
    
    /* Aloca memória para a estrutura Valor */
    Valor* v = (Valor*)malloc(sizeof(Valor));
    if (v == NULL) {
        return NULL;
    }
    
    /* Ajusta centavos >= 100 */
    if (centavos >= 100) {
        reais += centavos / 100;
        centavos = centavos % 100;
    }
    
    /* Inicializa os campos */
    v->reais = reais;
    v->centavos = centavos;
    
    return v;
}

/**
 * val_libera - Libera a memória de um Valor
 */
void val_libera(Valor* v) {
    if (v != NULL) {
        free(v);
    }
}

/**
 * val_paraCentavos - Converte Valor para centavos
 */
int val_paraCentavos(const Valor* v) {
    if (v == NULL) {
        return 0;
    }
    return (v->reais * 100) + v->centavos;
}

/**
 * val_paraReais - Converte Valor para reais (float)
 */
float val_paraReais(const Valor* v) {
    if (v == NULL) {
        return 0.0f;
    }
    return v->reais + (v->centavos / 100.0f);
}

/**
 * val_paraString - Converte Valor para string
 */
char* val_paraString(const Valor* v) {
    if (v == NULL) {
        char* str = (char*)malloc(10);
        if (str != NULL) {
            sprintf(str, "R$ 0,00");
        }
        return str;
    }
    
    char* str = (char*)malloc(20);
    if (str == NULL) {
        return NULL;
    }
    
    sprintf(str, "R$ %d,%02d", v->reais, v->centavos);
    return str;
}

/**
 * val_soma - Soma dois Valores
 */
Valor* val_soma(const Valor* v1, const Valor* v2) {
    if (v1 == NULL || v2 == NULL) {
        return NULL;
    }
    
    /* Soma em centavos para evitar erros de arredondamento */
    int total_centavos = val_paraCentavos(v1) + val_paraCentavos(v2);
    
    int reais = total_centavos / 100;
    int centavos = total_centavos % 100;
    
    return val_cria(reais, centavos);
}

/**
 * val_multiplica - Multiplica Valor por um fator
 */
Valor* val_multiplica(const Valor* v, int fator) {
    if (v == NULL || fator < 1) {
        return NULL;
    }
    
    /* Multiplica em centavos para evitar erros de arredondamento */
    int total_centavos = val_paraCentavos(v) * fator;
    
    int reais = total_centavos / 100;
    int centavos = total_centavos % 100;
    
    return val_cria(reais, centavos);
}

/**
 * val_aplicaDesconto - Aplica desconto a um Valor
 */
Valor* val_aplicaDesconto(const Valor* v, float percentual) {
    if (v == NULL || percentual < 0 || percentual > 100) {
        return NULL;
    }
    
    int total_centavos = val_paraCentavos(v);
    
    /* Calcula o valor do desconto em centavos */
    float desconto = total_centavos * (percentual / 100.0f);
    
    /* Aplica o desconto e arredonda para o centavo mais próximo */
    int novo_valor = (int)(total_centavos - desconto + 0.5f);
    
    int reais = novo_valor / 100;
    int centavos = novo_valor % 100;
    
    return val_cria(reais, centavos);
}

/**
 * val_compara - Compara dois Valores
 */
int val_compara(const Valor* v1, const Valor* v2) {
    /* Tratamento de NULL */
    if (v1 == NULL && v2 == NULL) return 0;
    if (v1 == NULL) return -1;
    if (v2 == NULL) return 1;
    
    int c1 = val_paraCentavos(v1);
    int c2 = val_paraCentavos(v2);
    
    return c1 - c2;
}