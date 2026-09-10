/*----------------------------------------------------------------------
                        SISTEMA DE AFINIDADES - V5
----------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define QTD_PREF 6

typedef struct {
char nome[50];
float notas[QTD_PREF];
} Pessoa;

float leNotaValida();
void cadastrarPessoas(Pessoa *pessoas[], int quantidade);
void exibirPessoas(Pessoa *pessoas[], int quantidade);
int buscaPessoa(Pessoa *pessoas[], int quantidade, char pessoa[]);
void encontrarPessoa(Pessoa *pessoas[], int quantidade);
/*float calculaDistancia(float notas[][QTD_PREF], int pessoa1, int pessoa2);
void compararPessoas(char nomes[][50], float notas[][QTD_PREF], int quantidade);
void encontrarMaisSemelhante(char nomes[][50], float notas[][QTD_PREF], int quantidade);
void exibirRanking(char nomes[][50], float notas[][QTD_PREF], int quantidade);
void analisarPreferencias(char nomes[][50], float notas[][QTD_PREF], int quantidade);*/

int main()
{
    Pessoa **pessoas = NULL;
    int quantidade = 0;
    int opcao,i;

    do
    {
        printf("\n========================================\n");
        printf("        SISTEMA DE AFINIDADES\n");
        printf("========================================\n");
        printf("1 - Cadastrar pessoas\n");
        printf("2 - Exibir pessoas e preferencias\n");
        printf("3 - Buscar pessoa pelo nome\n");
        printf("4 - Comparar duas pessoas\n");
        printf("5 - Encontrar pessoa mais semelhante\n");
        printf("6 - Exibir ranking de afinidade\n");
        printf("7 - Analisar preferencias de duas pessoas\n");
        printf("0 - Encerrar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        /* As opcoes de consulta dependem de um cadastro anterior. */
        if (opcao >= 2 && opcao <= 7 && quantidade == 0)
        {
            printf("Nenhuma pessoa foi cadastrada.\n");
        }
        else
        {
            switch (opcao)
            {
                case 1:
                    do
                    {
                        printf("Quantas pessoas deseja cadastrar? ");
                        scanf("%d", &quantidade);

                        if (quantidade < 1)
                        {
                            printf("Quantidade invalida. Cadastre no mínimo 1 pessoa.\n");
                        }
                    }
                    while (quantidade < 1);

                    pessoas = (Pessoa **) malloc(quantidade * sizeof(Pessoa *));

                    if (pessoas == NULL) {
                        printf("Memória insuficiente!\n");
                        
                        return 1;
                    }

                    cadastrarPessoas(pessoas, quantidade);
                    break;

                case 2:
                    exibirPessoas(pessoas, quantidade);
                    break;

                case 3:
                    encontrarPessoa(pessoas, quantidade);
                    break;

                /*case 4:
                    compararPessoas(nomes, notas, quantidade);
                    break;

                case 5:
                    encontrarMaisSemelhante(nomes, notas, quantidade);
                    break;

                case 6:
                    exibirRanking(nomes, notas, quantidade);
                    break;

                case 7:
                    analisarPreferencias(nomes, notas, quantidade);
                    break;*/
                case 0:
                    printf("Programa encerrado.\n");
                    break;

                default:
                    printf("Opcao invalida.\n");
            }
        }
    }
    while (opcao != 0);


    if(pessoas != NULL){
        for(i=0; i < quantidade; i++){
        free(pessoas[i]);
        }
        free(pessoas);
    }

    return 0;
}

float leNotaValida()
{
    float nota;

    do
    {
        scanf("%f", &nota);

        if (nota < 0 || nota > 10)
        {
            printf("Nota invalida. Digite novamente: ");
        }
    }
    while (nota < 0 || nota > 10);

    return nota;
}

void cadastrarPessoas(Pessoa *pessoas[], int quantidade)
{
    char preferencias[QTD_PREF][15] = {
        "Musica", "Cinema", "Jogos",
        "Esportes", "Leitura", "Programacao"
    };
    int i;
    int j;

    for (i = 0; i < quantidade; i++)
    {
        //Aloca uma pessoa por vez e guarda no vetor
        pessoas[i] = (Pessoa *) malloc(sizeof(Pessoa));

        printf("\nPessoa %d\n", i + 1);
        printf("Digite o nome: ");

        /* O espaco inicial descarta o Enter da leitura anterior. */
        scanf(" %49[^\n]", pessoas[i]->nome);

        for (j = 0; j < QTD_PREF; j++)
        {
            printf("Nota para %s: ", preferencias[j]);
            pessoas[i]->notas[j] = leNotaValida();
        }
    }
}

void exibirPessoas(Pessoa *pessoas[], int quantidade)
{
    int i;
    int j;

    printf("\n=================================================================\n");
    printf("%-18s MUS   CIN   JOG   ESP   LEI   PROG\n", "NOME");
    printf("=================================================================\n");

    for (i = 0; i < quantidade; i++)
    {
        printf("%-18s", pessoas[i]->nome);

        for (j = 0; j < QTD_PREF; j++)
        {
            printf("%-6.1f", pessoas[i]->notas[j]);
        }

        printf("\n");
    }

    printf("=================================================================\n");
}

int buscaPessoa(Pessoa *pessoas[], int quantidade, char pessoa[]){
    int i;

    for (i = 0; i < quantidade; i++)
    {
        /* strcmp devolve zero quando as strings sao iguais. */
        if (strcmp(pessoa, pessoas[i]->nome) == 0)
        {
            return i;
        }
    }

    return -1;
}

void encontrarPessoa(Pessoa *pessoas[], int quantidade)
{
    char preferencias[QTD_PREF][15] = {
        "Musica", "Cinema", "Jogos",
        "Esportes", "Leitura", "Programacao"
    };
    char pessoa[50];
    int indice;
    int j;

    printf("Digite o nome da pessoa: ");
    scanf(" %49[^\n]", pessoa);

    indice = buscaPessoa(pessoas, quantidade, pessoa);

    if (indice == -1)
    {
        printf("Pessoa nao cadastrada.\n");
        return;
    }

    printf("\nInteresses de %s:\n", pessoas[indice]->nome);

    for (j = 0; j < QTD_PREF; j++)
    {
        printf("%s: %.1f\n", preferencias[j], pessoas[indice]->notas[j]);
    }
}

/*float calculaDistancia(float notas[][QTD_PREF], int pessoa1, int pessoa2)
{
    float soma = 0;
    float diferenca;
    int j;

    for (j = 0; j < QTD_PREF; j++)
    {
        diferenca = notas[pessoa1][j] - notas[pessoa2][j];
        soma = soma + diferenca * diferenca;
    }

    return sqrt(soma);
}

void compararPessoas(char nomes[][50], float notas[][QTD_PREF], int quantidade)
{
    char nome1[50];
    char nome2[50];
    int pessoa1;
    int pessoa2;
    float distancia;

    printf("Digite o nome da primeira pessoa: ");
    scanf(" %49[^\n]", nome1);
    printf("Digite o nome da segunda pessoa: ");
    scanf(" %49[^\n]", nome2);

    pessoa1 = buscaPessoa(nomes, quantidade, nome1);
    pessoa2 = buscaPessoa(nomes, quantidade, nome2);

    if (pessoa1 == -1 || pessoa2 == -1)
    {
        printf("Uma ou ambas as pessoas nao foram encontradas.\n");
        return;
    }

    distancia = calculaDistancia(notas, pessoa1, pessoa2);

    printf("\n========================================\n");
    printf("COMPARACAO DE PERFIS\n");
    printf("========================================\n");
    printf("%s x %s\n", nomes[pessoa1], nomes[pessoa2]);
    printf("Distancia euclidiana: %.2f\n", distancia);
}

void encontrarMaisSemelhante(char nomes[][50], float notas[][QTD_PREF], int quantidade)
{
    char nomeReferencia[50];
    int referencia;
    int maisSemelhante = -1;
    int i;
    float distancia;
    float menorDistancia;

    printf("Digite a pessoa de referencia: ");
    scanf(" %49[^\n]", nomeReferencia);

    referencia = buscaPessoa(nomes, quantidade, nomeReferencia);

    if (referencia == -1)
    {
        printf("Pessoa nao cadastrada.\n");
        return;
    }

    if (quantidade < 2)
    {
        printf("Nao existem outras pessoas para comparar.\n");
        return;
    }

    for (i = 0; i < quantidade; i++)
    {
        if (i != referencia)
        {
            distancia = calculaDistancia(notas, referencia, i);
            printf("Distancia para %s: %.2f\n", nomes[i], distancia);

            /* A primeira candidata inicia o menor valor. *
            if (maisSemelhante == -1 || distancia < menorDistancia)
            {
                menorDistancia = distancia;
                maisSemelhante = i;
            }
        }
    }

    printf("\nPerfil mais semelhante: %s\n", nomes[maisSemelhante]);
    printf("Distancia: %.2f\n", menorDistancia);
}

void exibirRanking(char nomes[][50], float notas[][QTD_PREF], int quantidade)
{
    char nomeReferencia[50];
    int referencia;
    int indices[MAX_PESSOAS];
    float distancias[MAX_PESSOAS];
    int quantidadeRanking = 0;
    int i;
    int j;
    int indiceAuxiliar;
    float distanciaAuxiliar;

    printf("Digite a pessoa de referencia: ");
    scanf(" %49[^\n]", nomeReferencia);

    referencia = buscaPessoa(nomes, quantidade, nomeReferencia);

    if (referencia == -1)
    {
        printf("Pessoa nao cadastrada.\n");
        return;
    }

    if (quantidade < 2)
    {
        printf("Nao existem outras pessoas para o ranking.\n");
        return;
    }

    for (i = 0; i < quantidade; i++)
    {
        if (i != referencia)
        {
            indices[quantidadeRanking] = i;
            distancias[quantidadeRanking] = calculaDistancia(notas, referencia, i);
            quantidadeRanking++;
        }
    }

    /* Os vetores precisam ser trocados juntos para continuarem sincronizados. *
    for (i = 0; i < quantidadeRanking - 1; i++)
    {
        for (j = i + 1; j < quantidadeRanking; j++)
        {
            if (distancias[j] < distancias[i])
            {
                distanciaAuxiliar = distancias[i];
                distancias[i] = distancias[j];
                distancias[j] = distanciaAuxiliar;

                indiceAuxiliar = indices[i];
                indices[i] = indices[j];
                indices[j] = indiceAuxiliar;
            }
        }
    }

    printf("\n========================================\n");
    printf("PERFIS MAIS PROXIMOS DE %s\n", nomes[referencia]);
    printf("========================================\n");

    for (i = 0; i < quantidadeRanking; i++)
    {
        printf("%d - %s: %.2f\n",
               i + 1, nomes[indices[i]], distancias[i]);
    }
}

void analisarPreferencias(char nomes[][50], float notas[][QTD_PREF], int quantidade)
{
    char preferencias[QTD_PREF][15] = {
        "Musica", "Cinema", "Jogos",
        "Esportes", "Leitura", "Programacao"
    };
    char nome1[50];
    char nome2[50];
    int pessoa1;
    int pessoa2;
    int j;
    float diferencas[QTD_PREF];
    float menorDiferenca;

    printf("Digite o nome da primeira pessoa: ");
    scanf(" %49[^\n]", nome1);
    printf("Digite o nome da segunda pessoa: ");
    scanf(" %49[^\n]", nome2);

    pessoa1 = buscaPessoa(nomes, quantidade, nome1);
    pessoa2 = buscaPessoa(nomes, quantidade, nome2);

    if (pessoa1 == -1 || pessoa2 == -1)
    {
        printf("Uma ou ambas as pessoas nao foram encontradas.\n");
        return;
    }

    for (j = 0; j < QTD_PREF; j++)
    {
        diferencas[j] = fabs(notas[pessoa1][j] - notas[pessoa2][j]);
    }

    menorDiferenca = diferencas[0];

    for (j = 1; j < QTD_PREF; j++)
    {
        if (diferencas[j] < menorDiferenca)
        {
            menorDiferenca = diferencas[j];
        }
    }

    printf("\n=================================================\n");
    printf("ANALISE DE PERFIS: %s x %s\n", nomes[pessoa1], nomes[pessoa2]);
    printf("=================================================\n");
    printf("%-15s %-10s %-10s %-10s\n",
           "Preferencia", nomes[pessoa1], nomes[pessoa2], "Diferenca");

    for (j = 0; j < QTD_PREF; j++)
    {
        printf("%-15s %-10.1f %-10.1f %-10.1f\n",
               preferencias[j], notas[pessoa1][j], notas[pessoa2][j],
               diferencas[j]);
    }

    printf("Distancia euclidiana: %.2f\n",
           calculaDistancia(notas, pessoa1, pessoa2));
    printf("\nPreferencias mais semelhantes:\n");

    for (j = 0; j < QTD_PREF; j++)
    {
        /* A margem evita falhas em comparacoes diretas entre valores float. *
        if (fabs(diferencas[j] - menorDiferenca) < 0.0001)
        {
            printf("%s\n", preferencias[j]);
        }
    }
}
    */
