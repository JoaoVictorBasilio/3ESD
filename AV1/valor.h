/**
 * ================================================================
 * VALOR.H - TAD VALOR (Valores Monetários)
 * ================================================================
 * 
 * Este arquivo contém a definição do TAD Valor, que representa
 * valores monetários em reais e centavos (R$ X,XX).
 * 
 * Operações disponíveis:
 *   - Criação e liberação
 *   - Conversão para centavos, reais e string
 *   - Soma, multiplicação e desconto
 *   - Comparação
 * 
 * Autor: Professor
 *  
 * ================================================================
 */

#ifndef VALOR_H
#define VALOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Estrutura que armazena um valor monetário
 * 
 * Campos:
 *   @reais:    Parte inteira do valor (ex: 25 em R$ 25,50)
 *   @centavos: Parte decimal do valor (ex: 50 em R$ 25,50)
 * 
 * Invariantes:
 *   - reais >= 0
 *   - centavos >= 0 e centavos < 100
 */
typedef struct valor Valor;

/**
 * val_cria - Cria um novo Valor
 * 
 * @param reais:    Parte inteira do valor (deve ser >= 0)
 * @param centavos: Parte decimal do valor (deve ser >= 0)
 * 
 * @return: Ponteiro para o novo Valor criado, ou NULL em caso de erro
 * 
 * Comportamento:
 *   - Se centavos >= 100, ajusta automaticamente (ex: 150 centavos = 1 real e 50 centavos)
 *   - Se reais < 0 ou centavos < 0, retorna NULL
 *   - Se falha na alocação de memória, retorna NULL
 * 
 * Exemplo:
 *   Valor* v = val_cria(2, 150); // Cria R$ 3,50 (2 + 150/100)
 */
Valor* val_cria(int reais, int centavos);

/**
 * val_libera - Libera a memória alocada para um Valor
 * 
 * @param v: Ponteiro para o Valor a ser liberado
 * 
 * Comportamento:
 *   - Se v == NULL, não faz nada (seguro)
 *   - Libera a memória alocada para o Valor
 */
void val_libera(Valor* v);

/**
 * val_paraCentavos - Converte Valor para centavos
 * 
 * @param v: Ponteiro para o Valor a ser convertido
 * 
 * @return: Valor total em centavos (int)
 * 
 * Comportamento:
 *   - Se v == NULL, retorna 0
 *   - Calcula: (reais * 100) + centavos
 * 
 * Exemplo:
 *   Valor* v = val_cria(25, 50);
 *   int centavos = val_paraCentavos(v); // Retorna 2550
 */
int val_paraCentavos(const Valor* v);

/**
 * val_paraReais - Converte Valor para reais (float)
 * 
 * @param v: Ponteiro para o Valor a ser convertido
 * 
 * @return: Valor em reais (float)
 * 
 * Comportamento:
 *   - Se v == NULL, retorna 0.0
 *   - Calcula: reais + (centavos / 100.0)
 * 
 * Exemplo:
 *   Valor* v = val_cria(25, 50);
 *   float reais = val_paraReais(v); // Retorna 25.50
 */
float val_paraReais(const Valor* v);

/**
 * val_paraString - Converte Valor para string formatada
 * 
 * @param v: Ponteiro para o Valor a ser convertido
 * 
 * @return: String formatada "R$ X,XX" (alocada dinamicamente)
 * 
 * Comportamento:
 *   - Se v == NULL, retorna "R$ 0,00"
 *   - A string deve ser liberada com free() após o uso
 *   - Formato: "R$ %d,%02d"
 * 
 * Exemplo:
 *   Valor* v = val_cria(25, 50);
 *   char* str = val_paraString(v); // "R$ 25,50"
 *   printf("%s", str);
 *   free(str); // IMPORTANTE: liberar a string
 */
char* val_paraString(const Valor* v);

/**
 * val_soma - Soma dois Valores
 * 
 * @param v1: Primeiro Valor (operando 1)
 * @param v2: Segundo Valor (operando 2)
 * 
 * @return: Novo Valor com o resultado da soma (v1 + v2), ou NULL em erro
 * 
 * Comportamento:
 *   - Se v1 == NULL ou v2 == NULL, retorna NULL
 *   - Soma os valores em centavos para evitar erros de arredondamento
 *   - Retorna um novo Valor (memória alocada)
 * 
 * Exemplo:
 *   Valor* v1 = val_cria(10, 50);
 *   Valor* v2 = val_cria(15, 75);
 *   Valor* soma = val_soma(v1, v2); // R$ 26,25
 */
Valor* val_soma(const Valor* v1, const Valor* v2);

/**
 * val_multiplica - Multiplica Valor por um fator inteiro
 * 
 * @param v:     Valor a ser multiplicado
 * @param fator: Fator inteiro (deve ser >= 1)
 * 
 * @return: Novo Valor multiplicado, ou NULL em erro
 * 
 * Comportamento:
 *   - Se v == NULL ou fator < 1, retorna NULL
 *   - Multiplica o valor em centavos para evitar erros de arredondamento
 *   - Retorna um novo Valor (memória alocada)
 * 
 * Exemplo:
 *   Valor* v = val_cria(10, 50);
 *   Valor* mult = val_multiplica(v, 3); // R$ 31,50 (10,50 * 3)
 */
Valor* val_multiplica(const Valor* v, int fator);

/**
 * val_aplicaDesconto - Aplica desconto percentual a um Valor
 * 
 * @param v:          Valor a ter desconto aplicado
 * @param percentual: Percentual de desconto (0 a 100%)
 * 
 * @return: Novo Valor com desconto aplicado, ou NULL em erro
 * 
 * Comportamento:
 *   - Se v == NULL ou percentual < 0 ou percentual > 100, retorna NULL
 *   - Calcula: valor - (valor * percentual / 100)
 *   - Arredonda para o centavo mais próximo (usando +0.5)
 *   - Retorna um novo Valor (memória alocada)
 * 
 * Exemplo:
 *   Valor* v = val_cria(100, 0);
 *   Valor* desc = val_aplicaDesconto(v, 10.0); // R$ 90,00 (10% de desconto)
 */
Valor* val_aplicaDesconto(const Valor* v, float percentual);

/**
 * val_compara - Compara dois Valores
 * 
 * @param v1: Primeiro Valor
 * @param v2: Segundo Valor
 * 
 * @return: 
 *   - Negativo se v1 < v2
 *   - Zero se v1 == v2
 *   - Positivo se v1 > v2
 * 
 * Comportamento:
 *   - Se ambos NULL, retorna 0
 *   - Se v1 == NULL, retorna -1
 *   - Se v2 == NULL, retorna 1
 *   - Compara os valores em centavos
 * 
 * Exemplo:
 *   Valor* v1 = val_cria(10, 0);
 *   Valor* v2 = val_cria(20, 0);
 *   int comp = val_compara(v1, v2); // Retorna negativo (10 < 20)
 */
int val_compara(const Valor* v1, const Valor* v2);

#endif /* VALOR_H */
