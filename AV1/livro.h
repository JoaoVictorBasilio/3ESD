
/**
 * ================================================================
 * LIVRO.H - TAD LIVRO (Sistema de Biblioteca)
 * ================================================================
 * 
 * Este arquivo contém a definição do TAD Livro, que representa
 * um livro com multa diária e atraso na biblioteca.
 * 
 * O TAD Livro utiliza os TADs Valor e Dias.
 * 
 * Autor: Professor
 * 
 * ================================================================
 */

#ifndef LIVRO_H
#define LIVRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valor.h"
#include "dias.h"

/**
 * Estrutura que armazena os dados de um livro
 * 
 * Campos:
 *   @titulo:        Título do livro (string alocada dinamicamente)
 *   @multa_diaria:  Valor da multa por dia de atraso (TAD Valor)
 *   @atraso:        Período de atraso (TAD Dias)
 * 
 * Invariantes:
 *   - titulo != NULL
 *   - multa_diaria != NULL
 *   - atraso != NULL
 */
typedef struct livro  Livro;

/**
 * liv_cria - Cria um novo Livro
 * 
 * @param titulo:        Título do livro (string)
 * @param multa_diaria:  Valor da multa diária (TAD Valor)
 * @param atraso:        Período de atraso (TAD Dias)
 * 
 * @return: Ponteiro para o novo Livro criado, ou NULL em caso de erro
 * 
 * Comportamento:
 *   - Se titulo == NULL, multa_diaria == NULL ou atraso == NULL, retorna NULL
 *   - Aloca memória para a estrutura Livro
 *   - Aloca e copia o título (strdup ou malloc + strcpy)
 *   - Armazena os ponteiros dos TADs (não duplica)
 * 
 * ATENÇÃO: Os TADs Valor e Dias são "emprestados" para o Livro.
 *          O Livro NÃO deve duplicá-los, apenas armazenar os ponteiros.
 *          A liberação será feita em cascata por liv_libera().
 * 
 * Exemplo:
 *   Valor* multa = val_cria(2, 50);
 *   Dias* atraso = dias_cria(0, 3);
 *   Livro* livro = liv_cria("Dom Quixote", multa, atraso);
 */
Livro* liv_cria(const char* titulo, Valor* multa_diaria, Dias* atraso);

/**
 * liv_libera - Libera a memória do Livro em cascata
 * 
 * @param l: Ponteiro para o Livro a ser liberado
 * 
 * Comportamento:
 *   - Se l == NULL, não faz nada (seguro)
 *   - Libera o título (free)
 *   - Libera a multa_diaria (val_libera)
 *   - Libera o atraso (dias_libera)
 *   - Libera a estrutura Livro (free)
 * 
 * ATENÇÃO: Esta função libera TODOS os componentes do Livro em cascata.
 *          A ordem de liberação deve ser: título -> TADs -> estrutura.
 */
void liv_libera(Livro* l);

/**
 * liv_calculaMulta - Calcula o valor total da multa
 * 
 * @param l: Ponteiro para o Livro
 * 
 * @return: Novo Valor com o total da multa, ou NULL em erro
 * 
 * Comportamento:
 *   - Se l == NULL, l->multa_diaria == NULL ou l->atraso == NULL, retorna NULL
 *   - Converte multa_diaria para centavos (val_paraCentavos)
 *   - Converte atraso para total de dias (dias_paraTotalDias)
 *   - Calcula: centavos * total_dias
 *   - Converte o resultado para reais e centavos
 *   - Retorna um novo Valor (memória alocada)
 * 
 * Fórmula: multa_total = multa_diaria * total_dias
 * 
 * Exemplo:
 *   Livro* l = ...; // multa = R$ 2,50, atraso = 3 dias
 *   Valor* multa = liv_calculaMulta(l); // R$ 7,50
 */
Valor* liv_calculaMulta(const Livro* l);

/**
 * liv_paraString - Converte Livro para string formatada
 * 
 * @param l: Ponteiro para o Livro
 * 
 * @return: String formatada (alocada dinamicamente), ou NULL em erro
 * 
 * Comportamento:
 *   - Se l == NULL, retorna "Livro inválido"
 *   - Obtém o título (liv_getTitulo)
 *   - Obtém a string da multa diária (val_paraString)
 *   - Obtém a string do atraso (dias_paraString)
 *   - Calcula a multa total (liv_calculaMulta)
 *   - Obtém a string da multa total (val_paraString)
 *   - Monta a string final no formato:
 *     "Livro: [titulo] | Multa diária: [R$ X,XX] | Atraso: [X sem, X dias] | Multa total: [R$ X,XX]"
 *   - Libera as strings auxiliares após uso
 *   - Retorna a string final (deve ser liberada com free())
 * 
 * Exemplo:
 *   Livro* l = ...;
 *   char* str = liv_paraString(l);
 *   printf("%s", str);
 *   free(str); // IMPORTANTE: liberar a string
 */
char* liv_paraString(const Livro* l);

/**
 * liv_aplicaDescontoVIP - Aplica desconto VIP na multa total
 * 
 * @param l:          Ponteiro para o Livro
 * @param percentual: Percentual de desconto (0 a 100%)
 * 
 * @return: Novo Valor com desconto aplicado, ou NULL em erro
 * 
 * Comportamento:
 *   - Se l == NULL ou percentual < 0 ou percentual > 100, retorna NULL
 *   - Calcula a multa total (liv_calculaMulta)
 *   - Aplica o desconto (val_aplicaDesconto)
 *   - Libera a multa total intermediária
 *   - Retorna o novo Valor com desconto
 * 
 * ATENÇÃO: Esta função NÃO modifica o Livro, apenas calcula e retorna
 *          um novo Valor com o desconto aplicado.
 * 
 * Exemplo:
 *   Livro* l = ...; // multa total = R$ 100,00
 *   Valor* vip = liv_aplicaDescontoVIP(l, 15.0); // R$ 85,00 (15% de desconto)
 */
Valor* liv_aplicaDescontoVIP(const Livro* l, float percentual);

/* ================================================================
 * GETTERS - Funções de acesso aos campos do Livro
 * ================================================================ */

/**
 * liv_getTitulo - Getter do título do livro
 * 
 * @param l: Ponteiro para o Livro
 * 
 * @return: Ponteiro constante para o título, ou NULL se inválido
 */
const char* liv_getTitulo(const Livro* l);

/**
 * liv_getMultaDiaria - Getter da multa diária
 * 
 * @param l: Ponteiro para o Livro
 * 
 * @return: Ponteiro para a multa diária, ou NULL se inválido
 */
Valor* liv_getMultaDiaria(const Livro* l);

/**
 * liv_getAtraso - Getter do atraso
 * 
 * @param l: Ponteiro para o Livro
 * 
 * @return: Ponteiro para o atraso, ou NULL se inválido
 */
Dias* liv_getAtraso(const Livro* l);

#endif /* LIVRO_H */