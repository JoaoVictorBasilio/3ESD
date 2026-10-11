#include <stdio.h>
#include <stdlib.h>
#include "altura.h"
#include "massa.h"

typedef struct {
    char nome[50];
    Altura *altura;
    Massa *massa;
} Atleta;

char* atleta_paraString(const Atleta *at) {
    char *s_alt = alt_getAltura(at->altura);
    char *s_mas = mas_paraString(at->massa);
    char *res = (char*) malloc(200 * sizeof(char));
    
    if (res != NULL) {
        sprintf(res, "Atleta: %s | Altura: %s | Peso: %s", at->nome, s_alt, s_mas);
    }
    
    free(s_alt);
    free(s_mas);
    return res;
}

int main() {
    /* DADOS TESTES FORNECIDOS */
    Atleta equipe[3] = {
        {"Carlos Silva", alt_cria(1, 85), mas_cria(82, 500)},
        {"Mariana Souza", alt_cria(1, 68), mas_cria(58, 200)},
        {"Lucas Lima", alt_cria(2, 5), mas_cria(110, 0)} // Corrigido de 2,05 para 2,5 (2 metros e 5 cm)
    };
    
    printf("=== RELATÓRIO DE ATLETAS ===\n");
    for (int i = 0; i < 3; i++) {
        char *str_atleta = atleta_paraString(&equipe[i]);
        
        // --- CÁLCULO DE IMC CONSUMINDO O TAD ---
        
        // 1. Extrair os valores usando a função void com ponteiros
        int m, cm;
        alt_acessa(equipe[i].altura, &m, &cm);
        
        // 2. Calcular a altura final em metros (ex: 1 + 85 / 100.0 = 1.85)
        double h_m = m + (cm / 100.0);
        
        // 3. Extrair a massa e converter para quilos
        double p_kg = mas_paraGramas(equipe[i].massa) / 1000.0;
        
        // 4. Aplicar a fórmula do IMC
        double imc = p_kg / (h_m * h_m);
        
        printf("%s | IMC: %.2f\n", str_atleta, imc);
        
        free(str_atleta);
        
        // Liberação dos TADs
        alt_libera(equipe[i].altura);
        mas_libera(equipe[i].massa);
    }
    return 0;
}