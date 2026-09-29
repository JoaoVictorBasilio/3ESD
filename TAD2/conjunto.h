/* TAD conjunto*/

/* Elementos do conjunto s�o acessados atrav�s do endere�o de um de seus elementos */

/* Tipo elemento de conjunto*/

typedef struct conj Conjunto;
typedef struct elemento Elem;
 

/* Cria um conjunto de inteiros vazio */

Conjunto* conj_Cria(void);

/*Libera um conjunto de inteiros */

void  conj_Libera(Conjunto*A);

/* Inclui um novo n� no Conjunto caso ele ainda n�o pertenca ao conjunto */

void  conj_Insere(Conjunto *C, int x);

/* Verifica se um n� pertence ao Conjunto - 1 se pertence ou 0 caso contr�rio */

int conj_Ehmembro(Conjunto*A, int x);

/* Retira um n� do Conjunto caso ele  pertenca ao conjunto */

int  conj_Remove(int x, Conjunto *C);

 

 

 

/* Uniao de dois conjuntos retornando o conjunto Uniao */

Conjunto* conj_Uniao(Conjunto *A, Conjunto *B);

 

/* Intersecao de dois conjuntos retornando o conjunto Intersecao */

Conjunto* conj_Intersecao(Conjunto* A, Conjunto* B);

 

 

/* Diferencao entre dois conjuntos retornando o conjunto Diferenca */

Conjunto* conj_Diferenca(Conjunto*A, Conjunto*B);

 

/* Mostra na tela os elementos de um conjunto */

void conj_exibe(Conjunto*A);

