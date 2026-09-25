

/**
 * ================================================================
 * DIAS.C - IMPLEMENTAÇÃO DO TAD DIAS
 * ================================================================
 * 
 * Implementação das operações do TAD Dias (períodos de tempo).
 * 
 * Autor: Professor
 *  
 * ================================================================
 */

#include "dias.h"
struct dias{
    int semanas;
    int dias;
} ;
/**
 * dias_cria - Cria um novo período de Dias
 * 
 * Implementação:
 *   1. Verifica se parâmetros são válidos (>= 0)
 *   2. Aloca memória para a estrutura Dias
 *   3. Ajusta dias >= 7 (ex: 10 dias -> 1 semana e 3 dias)
 *   4. Inicializa os campos semanas e dias
 *   5. Retorna o ponteiro para Dias criado
 */
Dias* dias_cria(int semanas, int dias) {
    /* Validação dos parâmetros */
    if (semanas < 0 || dias < 0) {
        return NULL;
    }
    
    /* Aloca memória para a estrutura Dias */
    Dias* d = (Dias*)malloc(sizeof(Dias));
    if (d == NULL) {
        return NULL;
    }
    
    /* Ajusta dias >= 7 */
    if (dias >= 7) {
        semanas += dias / 7;
        dias = dias % 7;
    }
    
    /* Inicializa os campos */
    d->semanas = semanas;
    d->dias = dias;
    
    return d;
}

/**
 * dias_libera - Libera a memória de Dias
 */
void dias_libera(Dias* d) {
    if (d != NULL) {
        free(d);
    }
}

/**
 * dias_paraTotalDias - Converte Dias para total de dias
 */
int dias_paraTotalDias(const Dias* d) {
    if (d == NULL) {
        return 0;
    }
    return (d->semanas * 7) + d->dias;
}

/**
 * dias_paraSemanas - Converte Dias para semanas (float)
 */
float dias_paraSemanas(const Dias* d) {
    if (d == NULL) {
        return 0.0f;
    }
    return d->semanas + (d->dias / 7.0f);
}

/**
 * dias_paraString - Converte Dias para string
 */
char* dias_paraString(const Dias* d) {
    if (d == NULL) {
        char* str = (char*)malloc(20);
        if (str != NULL) {
            sprintf(str, "0 sem, 0 dias");
        }
        return str;
    }
    
    char* str = (char*)malloc(30);
    if (str == NULL) {
        return NULL;
    }
    
    sprintf(str, "%d sem, %d dias", d->semanas, d->dias);
    return str;
}

/**
 * dias_compara - Compara dois períodos de Dias
 */
int dias_compara(const Dias* d1, const Dias* d2) {
    /* Tratamento de NULL */
    if (d1 == NULL && d2 == NULL) return 0;
    if (d1 == NULL) return -1;
    if (d2 == NULL) return 1;
    
    int t1 = dias_paraTotalDias(d1);
    int t2 = dias_paraTotalDias(d2);
    
    return t1 - t2;
}

/**
 * dias_soma - Soma dois períodos de Dias
 */
Dias* dias_soma(const Dias* d1, const Dias* d2) {
    if (d1 == NULL || d2 == NULL) {
        return NULL;
    }
    
    /* Soma o total de dias */
    int total_dias = dias_paraTotalDias(d1) + dias_paraTotalDias(d2);
    
    /* Converte dias para semanas e dias */
    int semanas = total_dias / 7;
    int dias = total_dias % 7;
    
    return dias_cria(semanas, dias);
}

/**
 * dias_multiplica - Multiplica Dias por um fator
 */
Dias* dias_multiplica(const Dias* d, int fator) {
    if (d == NULL || fator < 1) {
        return NULL;
    }
    
    /* Multiplica o total de dias */
    int total_dias = dias_paraTotalDias(d) * fator;
    
    /* Converte dias para semanas e dias */
    int semanas = total_dias / 7;
    int dias = total_dias % 7;
    
    return dias_cria(semanas, dias);
}