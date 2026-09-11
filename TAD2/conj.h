#ifndef CONJ_H
#define CONJ_H

/*
 * TAD Conjunto
 * -----------
 * Armazena uma coleção de inteiros sem repetição.
 * É usado para representar grupos de elementos e operações como
 * união, interseção, diferença e verificação de membro.
 */

/* TAD conjunto */
typedef struct tconjunto TConjunto;
typedef TConjunto Conjunto;
typedef TConjunto ElemConjunto;

/* Cria um conjunto de inteiros vazio */
TConjunto* conj_cria(void);

/* Libera um conjunto de inteiros */
void conj_libera(TConjunto *c);

/* Inclui um novo número no conjunto caso ele ainda não pertença ao conjunto */
TConjunto* conj_insere(TConjunto *c, int x);

/* Verifica se um número pertence ao conjunto */
int conj_ehMembro(const TConjunto *c, int x);

/* Retira um número do conjunto caso ele pertença ao conjunto */
TConjunto* conj_remove(TConjunto *c, int x);

/* União de dois conjuntos */
TConjunto* conj_uniao(const TConjunto *a, const TConjunto *b);

/* Interseção de dois conjuntos */
TConjunto* conj_intersecao(const TConjunto *a, const TConjunto *b);

/* Diferença entre dois conjuntos */
TConjunto* conj_diferenca(const TConjunto *a, const TConjunto *b);

/* Mostra na tela os elementos de um conjunto */
void conj_exibe(const TConjunto *c);

/* Retorna uma string com os elementos do conjunto */
char* conj_paraString(const TConjunto *c);

/* Compatibilidade com nomes antigos */
#define criaTC conj_cria
#define lerTC conj_cria
#define printTC conj_exibe
#define conj_Cria conj_cria
#define conj_Libera conj_libera
#define conj_Insere conj_insere
#define conj_Ehmembro conj_ehMembro
#define conj_Remove conj_remove
#define conj_Uniao conj_uniao
#define conj_Intersecao conj_intersecao
#define conj_Diferenca conj_diferenca
#define conj_exibe conj_exibe

#endif