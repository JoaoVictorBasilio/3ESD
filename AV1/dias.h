/**
 * ================================================================
 * DIAS.H - TAD DIAS (Períodos de Tempo)
 * ================================================================
 * 
 * Este arquivo contém a definição do TAD Dias, que representa
 * períodos de tempo em semanas e dias.
 * 
 * Operações disponíveis:
 *   - Criação e liberação
 *   - Conversão para total de dias, semanas e string
 *   - Soma, multiplicação e comparação
 * 
 * Autor: Professor
 * 
 * ================================================================
 */

#ifndef DIAS_H
#define DIAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Estrutura que armazena um período de tempo
 * 
 * Campos:
 *   @semanas: Número de semanas
 *   @dias:    Número de dias adicionais
 * 
 * Invariantes:
 *   - semanas >= 0
 *   - dias >= 0 e dias < 7
 */
typedef struct dias Dias;

/**
 * dias_cria - Cria um novo período de Dias
 * 
 * @param semanas: Número de semanas (deve ser >= 0)
 * @param dias:    Número de dias (deve ser >= 0)
 * 
 * @return: Ponteiro para o novo Dias criado, ou NULL em caso de erro
 * 
 * Comportamento:
 *   - Se dias >= 7, ajusta automaticamente (ex: 10 dias = 1 semana e 3 dias)
 *   - Se semanas < 0 ou dias < 0, retorna NULL
 *   - Se falha na alocação de memória, retorna NULL
 * 
 * Exemplo:
 *   Dias* d = dias_cria(1, 10); // Cria 2 semanas e 3 dias (1 + 10/7)
 */
Dias* dias_cria(int semanas, int dias);

/**
 * dias_libera - Libera a memória alocada para Dias
 * 
 * @param d: Ponteiro para Dias a ser liberado
 * 
 * Comportamento:
 *   - Se d == NULL, não faz nada (seguro)
 *   - Libera a memória alocada para Dias
 */
void dias_libera(Dias* d);

/**
 * dias_paraTotalDias - Converte Dias para total de dias
 * 
 * @param d: Ponteiro para Dias a ser convertido
 * 
 * @return: Total de dias (int)
 * 
 * Comportamento:
 *   - Se d == NULL, retorna 0
 *   - Calcula: (semanas * 7) + dias
 * 
 * Exemplo:
 *   Dias* d = dias_cria(1, 3);
 *   int total = dias_paraTotalDias(d); // Retorna 10 (1*7 + 3)
 */
int dias_paraTotalDias(const Dias* d);

/**
 * dias_paraSemanas - Converte Dias para semanas (float)
 * 
 * @param d: Ponteiro para Dias a ser convertido
 * 
 * @return: Total em semanas (float)
 * 
 * Comportamento:
 *   - Se d == NULL, retorna 0.0
 *   - Calcula: semanas + (dias / 7.0)
 * 
 * Exemplo:
 *   Dias* d = dias_cria(1, 3);
 *   float sem = dias_paraSemanas(d); // Retorna 1.4285 (1 + 3/7)
 */
float dias_paraSemanas(const Dias* d);

/**
 * dias_paraString - Converte Dias para string formatada
 * 
 * @param d: Ponteiro para Dias a ser convertido
 * 
 * @return: String formatada "X sem, X dias" (alocada dinamicamente)
 * 
 * Comportamento:
 *   - Se d == NULL, retorna "0 sem, 0 dias"
 *   - A string deve ser liberada com free() após o uso
 *   - Formato: "%d sem, %d dias"
 * 
 * Exemplo:
 *   Dias* d = dias_cria(1, 3);
 *   char* str = dias_paraString(d); // "1 sem, 3 dias"
 *   printf("%s", str);
 *   free(str); // IMPORTANTE: liberar a string
 */
char* dias_paraString(const Dias* d);

/**
 * dias_compara - Compara dois períodos de Dias
 * 
 * @param d1: Primeiro Dias
 * @param d2: Segundo Dias
 * 
 * @return: 
 *   - Negativo se d1 < d2
 *   - Zero se d1 == d2
 *   - Positivo se d1 > d2
 * 
 * Comportamento:
 *   - Se ambos NULL, retorna 0
 *   - Se d1 == NULL, retorna -1
 *   - Se d2 == NULL, retorna 1
 *   - Compara o total de dias
 * 
 * Exemplo:
 *   Dias* d1 = dias_cria(1, 0);
 *   Dias* d2 = dias_cria(0, 10);
 *   int comp = dias_compara(d1, d2); // Retorna 0 (ambos têm 7 dias)
 */
int dias_compara(const Dias* d1, const Dias* d2);

/**
 * dias_soma - Soma dois períodos de Dias
 * 
 * @param d1: Primeiro Dias (operando 1)
 * @param d2: Segundo Dias (operando 2)
 * 
 * @return: Novo Dias com o resultado da soma (d1 + d2), ou NULL em erro
 * 
 * Comportamento:
 *   - Se d1 == NULL ou d2 == NULL, retorna NULL
 *   - Soma o total de dias e ajusta semanas automaticamente
 *   - Retorna um novo Dias (memória alocada)
 * 
 * Exemplo:
 *   Dias* d1 = dias_cria(1, 3);
 *   Dias* d2 = dias_cria(0, 5);
 *   Dias* soma = dias_soma(d1, d2); // 1 semana e 8 dias -> 2 semanas e 1 dia
 */
Dias* dias_soma(const Dias* d1, const Dias* d2);

/**
 * dias_multiplica - Multiplica Dias por um fator inteiro
 * 
 * @param d:     Dias a ser multiplicado
 * @param fator: Fator inteiro (deve ser >= 1)
 * 
 * @return: Novo Dias multiplicado, ou NULL em erro
 * 
 * Comportamento:
 *   - Se d == NULL ou fator < 1, retorna NULL
 *   - Multiplica o total de dias e ajusta semanas automaticamente
 *   - Retorna um novo Dias (memória alocada)
 * 
 * Exemplo:
 *   Dias* d = dias_cria(1, 3);
 *   Dias* mult = dias_multiplica(d, 2); // 2 semanas e 6 dias (10*2=20 -> 2*7+6)
 */
Dias* dias_multiplica(const Dias* d, int fator);

#endif /* DIAS_H */