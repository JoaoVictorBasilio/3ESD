#include <stdio.h>
#include <stdlib.h>
#include "Data.h"

typedef struct {
    char modulo[50];
    int horas_estimadas;
    tData* dt_prazo;
    tData* dt_entrega;
} tEntregavel;

// Função auxiliar para criar e instanciar um entregável
tEntregavel* criar_entregavel(const char* mod, int horas, int diaP, int mesP, int anoP, int diaE, int mesE, int anoE) {
    tEntregavel* e = (tEntregavel*) malloc(sizeof(tEntregavel));
    sprintf(e->modulo, "%s", mod);
    e->horas_estimadas = horas;
    e->dt_prazo = dta_cria(diaP, mesP, anoP);
    e->dt_entrega = dta_cria(diaE, mesE, anoE);
    return e;
}

int main() {
    // Vetor de ponteiros para struct tEntregavel alocado e preenchido
    tEntregavel* projeto[6];
    projeto[0] = criar_entregavel("Modulo de Autenticacao", 40, 15, 10, 2026,  5, 10, 2026); // 10 dias antes (Bônus 20%)
    projeto[1] = criar_entregavel("API de Pagamentos",     80, 20, 10, 2026, 20, 10, 2026); // No dia (Pontuação normal)
    projeto[2] = criar_entregavel("Relatorios em PDF",     30, 10, 10, 2026, 14, 10, 2026); // 4 dias de atraso (Penalidade)
    projeto[3] = criar_entregavel("Dashboard Analytics",   60, 25, 10, 2026, 22, 10, 2026); // 3 dias antes (No prazo - sem bônus)
    projeto[4] = criar_entregavel("Modulo de Notificacao", 20, 05, 10, 2026, 30, 9, 2026); // 5 dias antes (Bônus 20%)
    projeto[5] = criar_entregavel("Integracao Gateway",    50, 01, 11, 2026, 15, 11, 2026); // 14 dias de atraso (Penalidade severa)

    int total_entregaveis = 6;
    int i;

    // TODO: Escreva a partir daqui a lógica para calcular o desempenho de cada entregável
    // utilizando as funções do TAD Data (dta_diferenca, dta_exibe/dta_getData, dta_libera, etc.)

    for (i = 0; i < total_entregaveis; i++) {
        
        int status = dta_compara(projeto[i]->dt_entrega, projeto[i]->dt_prazo);
        int dias = dta_diferenca(projeto[i]->dt_entrega, projeto[i]->dt_prazo) - 1;
        
        float pontuacao = projeto[i]->horas_estimadas;

  
        if (status == -1 && dias >= 5) {
  
            pontuacao = pontuacao + (pontuacao * 0.20);
            
        } else if (status == 1) {
    
            pontuacao = pontuacao - (pontuacao * 0.05 * dias);
            
    
            if (pontuacao < 0) {
                pontuacao = 0;
            }

        printf("Modulo: %s\n", projeto[i]->modulo);
        
        printf("Prazo: ");
        dta_exibe(projeto[i]->dt_prazo); 
        
        printf(" | Entrega: ");
        dta_exibe(projeto[i]->dt_entrega);
        

        if (status == -1) {
            printf("\nStatus: Antecipado em %d dias\n", dias);
        } else if (status == 1) {
            printf("\nStatus: Atrasado em %d dias\n", dias);
        } else {
            printf("\nStatus: Entregue exatamento no prazo\n");
        }

        printf("Pontuacao Base:  %d\n", projeto[i]->horas_estimadas);
        printf("Pontuacao Final: %.2f\n", pontuacao);
        printf("----------------------------------------\n");

   
        dta_libera(projeto[i]->dt_prazo);
        dta_libera(projeto[i]->dt_entrega);
        free(projeto[i]);
    }
    }

    return 0;
}
