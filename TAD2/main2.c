#include <stdio.h>
#include <stdlib.h>
#include "bagagem.h"
#include "massa.h" // Precisamos disto para usar a função mas_paraGramas()

int main() {
    Bagagem* cargas[4];
    
    /* 
     * DADOS TESTES FORNECIDOS (CORRIGIDOS!)
     * Removi os zeros à esquerda (ex: 0,50 -> 0, 50) para evitar 
     * que o compilador leia os números em base octal e quebre a matemática.
     */
    cargas[0] = bag_cria(alt_cria(0, 50), alt_cria(0, 40), alt_cria(0, 60), mas_cria(15, 0));
    cargas[1] = bag_cria(alt_cria(1, 0),  alt_cria(0, 80), alt_cria(1, 20), mas_cria(45, 500));
    cargas[2] = bag_cria(alt_cria(0, 30), alt_cria(0, 30), alt_cria(0, 40), mas_cria(8,  200));
    cargas[3] = bag_cria(alt_cria(0, 80), alt_cria(0, 60), alt_cria(0, 90), mas_cria(30, 0));
    
    double limite_peso_kg = 80.0;
    double peso_acumulado_kg = 0.0;
    double volume_acumulado_m3 = 0.0; // Adicionamos isto para ter um controlo total
    
    printf("=== PROCESSAMENTO DE EMBARQUE DE CARGA ===\n");

    for (int i = 0; i < 4; i++) {
        char *info = bag_paraString(cargas[i]);
        double vol = bag_calculaVolumeM3(cargas[i]);
        
        // 1. Aceder ao peso de forma segura através do novo getter
        Massa* peso_bag = bag_getMassa(cargas[i]);
        
        // 2. Converter a Massa em kg com casas decimais (ex: 45500g -> 45.5kg)
        double peso_item_kg = mas_paraGramas(peso_bag) / 1000.0;
        
        // 3. Lógica de Validação Logística
        if (peso_acumulado_kg + peso_item_kg <= limite_peso_kg) {
            // O item cabe no avião! Somamos à carga total.
            peso_acumulado_kg += peso_item_kg;
            volume_acumulado_m3 += vol;
            printf("Item %d: [EMBARCADO] %s | Vol: %.3fm3\n", i + 1, info, vol);
        } else {
            // O item faz o avião passar dos 80kg. Rejeitado!
            printf("Item %d: [REJEITADO - EXCESSO DE PESO] %s | Vol: %.3fm3\n", i + 1, info, vol);
        }

        // Limpeza de memória
        free(info);
        bag_libera(cargas[i]);
    }
    
    // Imprimir o relatório final do voo
    printf("\n=== RESUMO FINAL DO VOO ===\n");
    printf("Peso Total Embarcado: %.3f kg (Limite: %.1f kg)\n", peso_acumulado_kg, limite_peso_kg);
    printf("Volume Total Ocupado: %.3f m3\n", volume_acumulado_m3);
    
    return 0;
}