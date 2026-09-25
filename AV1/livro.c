

/**
 * ================================================================
 * LIVRO.C - IMPLEMENTAÇÃO DO TAD LIVRO
 * ================================================================
 * 
 * Implementação do TAD Livro, que utiliza os TADs Valor e Dias.
 * 
 * Autor: [Nome do Aluno]
 *  
 * ================================================================
 */

#include "livro.h"

struct livro {
    char* titulo;
    Valor* multa_diaria;
    Dias* atraso;
};
/**
 * liv_cria - Cria um novo Livro
 * 
 * Implementação:
 *   1. Valida os parâmetros
 *   2. Aloca memória para a estrutura Livro
 *   3. Aloca e copia o título
 *   4. Armazena os ponteiros dos TADs (não duplica)
 *   5. Retorna o ponteiro para o Livro criado
 */
Livro* liv_cria(const char* titulo, Valor* multa_diaria, Dias* atraso) {
    if (titulo == NULL || multa_diaria == NULL || atraso == NULL) {
        return NULL;
    }

    Livro* l = (Livro*)malloc(sizeof(Livro));
    if (l == NULL) {
        return NULL;
    }

    l->titulo = (char*)malloc((strlen(titulo) + 1) * sizeof(char));
    
    if (l->titulo == NULL) {
        free(l);
        return NULL;
    }
    
    strcpy(l->titulo, titulo);

    l->multa_diaria = multa_diaria;
    l->atraso = atraso;

    return l;
}
/**
 * liv_libera - Libera a memória do Livro em cascata
 */
void liv_libera(Livro* l) {
    if (l != NULL) {
        if (l->titulo != NULL) {
            free(l->titulo);
        }
        
        val_libera(l->multa_diaria);
        dias_libera(l->atraso);
        free(l);
    }
}

/**
 * liv_calculaMulta - Calcula o valor total da multa
 * 
 * Fórmula: multa_total = multa_diaria * total_dias
 */
Valor* liv_calculaMulta(const Livro* l) {
    if (l == NULL || l->multa_diaria == NULL || l->atraso == NULL) {
        return NULL;
    }

    int centavos_diaria = val_paraCentavos(l->multa_diaria);
    int total_dias = dias_paraTotalDias(l->atraso);

    int centavos_total = centavos_diaria * total_dias;

    int reais = centavos_total / 100;
    int centavos = centavos_total % 100;

    return val_cria(reais, centavos);
}

/**
 * liv_paraString - Converte Livro para string formatada
 * 
 * Formato: "Livro: [titulo] | Multa diária: [R$ X,XX] | Atraso: [X sem, X dias] | Multa total: [R$ X,XX]"
 */
char* liv_paraString(const Livro* l) {
    if (l == NULL) {
        char* erro = (char*)malloc(20);
        if (erro != NULL) strcpy(erro, "Livro inválido");
        return erro;
    }

    const char* tit = liv_getTitulo(l);
    char* str_multa_diaria = val_paraString(l->multa_diaria);
    char* str_atraso = dias_paraString(l->atraso);
    Valor* v_total = liv_calculaMulta(l);
    char* str_multa_total = val_paraString(v_total);

    size_t tamanho = strlen(tit) + strlen(str_multa_diaria) + 
                    strlen(str_atraso) + strlen(str_multa_total) + 100;
    char* str_final = (char*)malloc(tamanho);

    if (str_final != NULL) {
        
        strcpy(str_final, "Livro: ");
        strcat(str_final, tit);
        strcat(str_final, " | Multa diária: ");
        strcat(str_final, str_multa_diaria);
        strcat(str_final, " | Atraso: ");
        strcat(str_final, str_atraso);
        strcat(str_final, " | Multa total: ");
        strcat(str_final, str_multa_total);
    }

    free(str_multa_diaria);
    free(str_atraso);
    free(str_multa_total);
    val_libera(v_total);

    return str_final;
}

/**
 * liv_aplicaDescontoVIP - Aplica desconto VIP na multa total
 */
Valor* liv_aplicaDescontoVIP(const Livro* l, float percentual) {
    if (l == NULL || percentual < 0.0f || percentual > 100.0f) {
        return NULL;
    }

    Valor* total = liv_calculaMulta(l);
    if (total == NULL) {
        return NULL;
    }

    Valor* com_desconto = val_aplicaDesconto(total, percentual);
    val_libera(total);

    return com_desconto;
}

/* ================================================================
 * GETTERS - JÁ IMPLEMENTADOS
 * ================================================================ */

/**
 * liv_getTitulo - Retorna o título do livro
 */
const char* liv_getTitulo(const Livro* l) {
    if (l == NULL) {
        return NULL;
    }
    return l->titulo;
}

/**
 * liv_getMultaDiaria - Retorna a multa diária
 */
Valor* liv_getMultaDiaria(const Livro* l) {
    if (l == NULL) {
        return NULL;
    }
    return l->multa_diaria;
}

/**
 * liv_getAtraso - Retorna o atraso
 */
Dias* liv_getAtraso(const Livro* l) {
    if (l == NULL) {
        return NULL;
    }
    return l->atraso;
}