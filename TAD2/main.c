#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instante.h" // Deve conter inst_somaMinutos, inst_compara, inst_cria, inst_libera

/*
 * Programa principal de teste do TAD Instante.
 * O objetivo deste módulo é validar a regra de negócio da agenda:
 * um novo compromisso só deve ser aceito se não houver sobreposição
 * de intervalo com os itens já agendados.
 *
 * A solução usa os TADs de Data, Horário e Instante para representar
 * os momentos de início e término dos compromissos de forma consistente.
 */

// 1. Definição da estrutura interna do compromisso
typedef struct {
    char descricao[100];
    Instante *inicio;
    int duracao_minutos;
} Compromisso;

// Protótipos das funções do Compromisso
Compromisso* compro_cria(const char *descricao, Instante *inicio, int duracao_minutos);
void compro_libera(Compromisso *c);
int compro_pode_inserir(Compromisso **agenda, int n, Compromisso *novo);

// Função auxiliar para instanciar um Compromisso
Compromisso* compro_cria(const char *descricao, Instante *inicio, int duracao_minutos) {
    if (inicio == NULL || duracao_minutos <= 0) return NULL;
    
    Compromisso *c = (Compromisso *) malloc(sizeof(Compromisso));
    if (c == NULL) return NULL;
    
    strncpy(c->descricao, descricao, 99);
    c->descricao[99] = '\0';
    c->inicio = inicio;
    c->duracao_minutos = duracao_minutos;
    
    return c;
}

// Função para liberar a memória do compromisso e seu instante
void compro_libera(Compromisso *c) {
    if (c != NULL) {
        if (c->inicio != NULL) {
            inst_libera(c->inicio);
        }
        free(c);
    }
}

// 2. Função de Validação utilizando inst_somaMinutos e inst_compara
int compro_pode_inserir(Compromisso **agenda, int n, Compromisso *novo) {
    if (novo == NULL || novo->inicio == NULL) return 0;

    // Calcula o instante de término do novo compromisso
    Instante *fim_novo = inst_somaMinutos(novo->inicio, novo->duracao_minutos);

    for (int i = 0; i < n; i++) {
        Compromisso *atual = agenda[i];
        
        // Calcula o instante de término do compromisso já agendado
        Instante *fim_atual = inst_somaMinutos(atual->inicio, atual->duracao_minutos);

        // Verifica a sobreposição de horários (interseção de intervalos)
        // Há conflito se: InicioNovo < FimAtual E InicioAtual < FimNovo
        if (inst_compara(novo->inicio, fim_atual) < 0 && 
            inst_compara(atual->inicio, fim_novo) < 0) {
            
            // Conflito detectado, limpa as variáveis temporárias e retorna 0
            inst_libera(fim_novo);
            inst_libera(fim_atual);
            return 0; 
        }
        
        // Sem conflito com este item, libera o temporário e segue o loop
        inst_libera(fim_atual);
    }

    // Passou por toda a agenda sem conflitos
    inst_libera(fim_novo);
    return 1;
}

int main() {
    Compromisso *agenda[10];
    int n = 0;

    // 1. Inserir compromisso 1: 01/09/2026 das 14:00 às 15:30 (90 min)
    Instante *t1 = inst_cria(1, 9, 2026, 14, 0, 0);
    Compromisso *c1 = compro_cria("Reuniao de Planejamento", t1, 90);
    
    if (compro_pode_inserir(agenda, n, c1)) {
        agenda[n++] = c1;
        printf("Compromisso 1 inserido com sucesso!\n\n");
    } else {
        printf("ERRO: Compromisso 1 recusado!\n\n");
        compro_libera(c1);
    }

    // 2. Tentar inserir compromisso 2 (COM CONFLITO): 01/09/2026 das 15:00 às 16:00 (60 min)
    Instante *t2 = inst_cria(1, 9, 2026, 15, 0, 0);
    Compromisso *c2 = compro_cria("Apresentacao de Projeto", t2, 60);
    printf("Tentando inserir: '%s' (15:00h)...\n", c2->descricao);
    
    if (compro_pode_inserir(agenda, n, c2)) {
        agenda[n++] = c2;
        printf("-> Compromisso inserido com sucesso!\n\n");
    } else {
        printf("-> ERRO: Horario em conflito! Compromisso recusado.\n\n");
        compro_libera(c2); // Recusado, libera memória
    }

    // 3. Tentar inserir compromisso 3 (SEM CONFLITO): 01/09/2026 das 15:30 às 16:30 (60 min)
    Instante *t3 = inst_cria(1, 9, 2026, 15, 30, 0);
    Compromisso *c3 = compro_cria("Sessao de Code Review", t3, 60);
    printf("Tentando inserir: '%s' (15:30h)...\n", c3->descricao);
    
    if (compro_pode_inserir(agenda, n, c3)) {
        agenda[n++] = c3;
        printf("-> Compromisso inserido com sucesso!\n\n");
    } else {
        printf("-> ERRO: Horario em conflito! Compromisso recusado.\n\n");
        compro_libera(c3);
    }

    // Limpeza de memória final dos compromissos aceitos na agenda
    for (int i = 0; i < n; i++) {
        compro_libera(agenda[i]);
    }

    return 0;
}