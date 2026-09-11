#include <stdio.h>

#include <math.h>

#include <string.h>

#include <stdlib.h>

#define QTD_PREF 6

typedef struct {
char nome[50];
float notas[QTD_PREF];
} Pessoa;

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

void cadastrarPessoas(Pessoa pessoas[], int quantidade)
{
    char preferencias[QTD_PREF][15] = {
        "Musica", "Cinema", "Jogos",
        "Esportes", "Leitura", "Programacao"
    };
    int i;
    int j;

    for (i = 0; i < quantidade; i++)
    {
        printf("\nPessoa %d\n", i + 1);
        printf("Digite o nome: ");

        /* O espaco inicial descarta o Enter da leitura anterior. */
        scanf(" %49[^\n]", pessoas[i].nome);

        for (j = 0; j < QTD_PREF; j++)
        {
            printf("Nota para %s: ", preferencias[j]);
            pessoas[i].notas[j] = leNotaValida();
        }
    }
}

void exibirPessoas(Pessoa pessoas[], int quantidade)
{
    int i;
    int j;

    printf("\n=================================================================\n");
    printf("%-18s MUS   CIN   JOG   ESP   LEI   PROG\n", "NOME");
    printf("=================================================================\n");

    for (i = 0; i < quantidade; i++)
    {
        printf("%-18s", pessoas[i].nome);

        for (j = 0; j < QTD_PREF; j++)
        {
            printf("%-6.1f", pessoas[i].notas[j]);
        }

        printf("\n");
    }

    printf("=================================================================\n");
}

int buscaPessoa(Pessoa pessoas[], int quantidade, char pessoa[]){
    int i;

    for (i = 0; i < quantidade; i++)
    {
        /* strcmp devolve zero quando as strings sao iguais. */
        if (strcmp(pessoa, pessoas[i].nome) == 0)
        {
            return i;
        }
    }

    return -1;
}

void encontrarPessoa(Pessoa pessoas[], int quantidade)
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

    printf("\nInteresses de %s:\n", pessoas[indice].nome);

    for (j = 0; j < QTD_PREF; j++)
    {
        printf("%s: %.1f\n", preferencias[j], pessoas[indice].notas[j]);
    }
}

float calculaDistancia(Pessoa *pessoas, int pessoa1, int pessoa2)
{
    float soma = 0;
    float diferenca;
    int j;

    for (j = 0; j < QTD_PREF; j++)
    {
        diferenca = pessoas[pessoa1].notas[j] - pessoas[pessoa2].notas[j];

        soma = soma + diferenca * diferenca;
    }

    return sqrt(soma);
}

void compararPessoas(Pessoa *pessoas, int quantidade)
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

    pessoa1 = buscaPessoa(pessoas, quantidade, nome1);
    pessoa2 = buscaPessoa(pessoas, quantidade, nome2);

    if (pessoa1 == -1 || pessoa2 == -1)
    {
        printf("Uma ou ambas as pessoas nao foram encontradas.\n");
        return;
    }

    distancia = calculaDistancia(pessoas, pessoa1, pessoa2);

    printf("\n========================================\n");
    printf("COMPARACAO DE PERFIS\n");
    printf("========================================\n");

    printf("%s x %s\n",
           pessoas[pessoa1].nome,
           pessoas[pessoa2].nome);

    printf("Distancia euclidiana: %.2f\n", distancia);
}

void encontrarMaisSemelhante(Pessoa *pessoas, int quantidade)
{
    char nomeReferencia[50];
    int referencia;
    int maisSemelhante = -1;
    int i;
    float distancia;
    float menorDistancia;

    printf("Digite a pessoa de referencia: ");
    scanf(" %49[^\n]", nomeReferencia);

    referencia = buscaPessoa(pessoas, quantidade, nomeReferencia);

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
            distancia = calculaDistancia(pessoas, referencia, i);

            printf("Distancia para %s: %.2f\n",
                   pessoas[i].nome,
                   distancia);

            if (maisSemelhante == -1 || distancia < menorDistancia)
            {
                menorDistancia = distancia;
                maisSemelhante = i;
            }
        }
    }

    printf("\nPerfil mais semelhante: %s\n",
           pessoas[maisSemelhante].nome);

    printf("Distancia: %.2f\n", menorDistancia);
}

void exibirRanking(
    Pessoa *pessoas,
    int quantidade
)
{
    char ref[50];
    int indice;

    int *indices;
    float *distancias;

    int quantidadeRanking = 0;
    int i;
    int j;

    int indiceAuxiliar;
    float distanciaAuxiliar;

    printf("Digite o nome da pessoa de referencia: ");
    if (scanf(" %49[^\n]", ref) != 1)
    {
        printf("Nao foi possivel ler o nome.\n");
        return;
    }

    indice = buscaPessoa(pessoas, quantidade, ref);

    if (indice == -1)
    {
        printf("Pessoa nao cadastrada.\n");
        return;
    }

    if (quantidade < 2)
    {
        printf("Nao existem outras pessoas cadastradas.\n");
        return;
    }

    /* Uma posicao por pessoa, excluindo a referencia. */
    indices = malloc((quantidade - 1) * sizeof(int));
    if (indices == NULL)
    {
        printf("Erro ao alocar memoria para os indices.\n");
        return;
    }

    distancias = malloc((quantidade - 1) * sizeof(float));
    if (distancias == NULL)
    {
        printf("Erro ao alocar memoria para as distancias.\n");
        free(indices);
        return;
    }

    /* Inclui todas as pessoas, exceto a propria referencia. */
    for (i = 0; i < quantidade; i++)
    {
        if (i != indice)
        {
            indices[quantidadeRanking] = i;

            distancias[quantidadeRanking] =
                calculaDistancia(pessoas, indice, i);

            quantidadeRanking++;
        }
    }

    /* Ordena os vetores paralelos pela menor distancia. */
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
    printf(
        "PERFIS MAIS PROXIMOS DE %s\n",
        pessoas[indice].nome
    );
    printf("========================================\n");

    for (i = 0; i < quantidadeRanking; i++)
    {
        printf(
            "%d - %s: %.2f\n",
            i + 1,
            pessoas[indices[i]].nome,
            distancias[i]
        );
    }

    free(indices);
    free(distancias);
}

void analisarPreferencias(
    Pessoa *pessoas,
    int quantidade
)
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
    float distancia;

    printf("Digite o nome da primeira pessoa: ");
    if (scanf(" %49[^\n]", nome1) != 1)
    {
        printf("Nao foi possivel ler o nome.\n");
        return;
    }

    printf("Digite o nome da segunda pessoa: ");
    if (scanf(" %49[^\n]", nome2) != 1)
    {
        printf("Nao foi possivel ler o nome.\n");
        return;
    }

    pessoa1 = buscaPessoa(pessoas, quantidade, nome1);
    pessoa2 = buscaPessoa(pessoas, quantidade, nome2);

    if (pessoa1 == -1 || pessoa2 == -1)
    {
        printf("Uma ou ambas as pessoas nao foram encontradas.\n");
        return;
    }

    /* Calcula a diferenca absoluta em cada preferencia. */
    for (j = 0; j < QTD_PREF; j++)
    {
        diferencas[j] = fabs(
            pessoas[pessoa1].notas[j] -
            pessoas[pessoa2].notas[j]
        );
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
    printf("ANALISE DE PERFIS\n");
    printf("=================================================\n");
    printf(
        "%s x %s\n\n",
        pessoas[pessoa1].nome,
        pessoas[pessoa2].nome
    );

    printf(
        "%-15s %-10s %-10s %-10s\n",
        "Preferencia",
        pessoas[pessoa1].nome,
        pessoas[pessoa2].nome,
        "Diferenca"
    );

    printf("-------------------------------------------------\n");

    for (j = 0; j < QTD_PREF; j++)
    {
        printf(
            "%-15s %-10.1f %-10.1f %-10.1f\n",
            preferencias[j],
            pessoas[pessoa1].notas[j],
            pessoas[pessoa2].notas[j],
            diferencas[j]
        );
    }

    printf("-------------------------------------------------\n");

    distancia = calculaDistancia(pessoas, pessoa1, pessoa2);
    printf("Distancia euclidiana: %.2f\n", distancia);

    printf("\nPreferencias mais semelhantes:\n");

    /* A margem evita problemas de igualdade direta entre floats. */
    for (j = 0; j < QTD_PREF; j++)
    {
        if (fabs(diferencas[j] - menorDiferenca) < 0.0001)
        {
            printf("%s\n", preferencias[j]);
        }
    }
}

int main()
{
    Pessoa *pessoas = NULL;
    int quantidade = 0;
    int opcao;

    do
    {
        printf("\n========================================\n");
        printf("       SISTEMA DE RECOMENDACAO\n");
        printf("========================================\n");
        printf("1 - Cadastrar pessoas\n");
        printf("2 - Exibir pessoas e preferencias\n");
        printf("3 - Buscar pessoa pelo nome\n");
        printf("4 - Comparar duas pessoas\n");
        printf("5 - Encontrar pessoa mais semelhante\n");
        printf("6 - Exibir ranking de afinidade\n");
        printf("7 - Analisar preferencias de duas pessoas\n");
        printf("0 - Encerrar\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:

                printf("\nDigite a quantidade de pessoas: ");
                scanf("%d", &quantidade);

                if (quantidade <= 0)
                {
                    printf("A quantidade deve ser maior que zero.\n");
                    quantidade = 0;
                    break;
                }

                if (pessoas != NULL)
                {
                    free(pessoas);
                    pessoas = NULL;
                }

                pessoas = malloc(quantidade * sizeof(Pessoa));

                if (pessoas == NULL)
                {
                    printf("Erro ao alocar memoria.\n");
                    quantidade = 0;
                    break;
                }

                cadastrarPessoas(pessoas, quantidade);

                printf("\nPessoas cadastradas com sucesso!\n");

                break;

            case 2:

                if (pessoas == NULL || quantidade == 0)
                {
                    printf("\nNenhuma pessoa cadastrada.\n");
                    break;
                }

                exibirPessoas(pessoas, quantidade);

                break;

            case 3:

                if (pessoas == NULL || quantidade == 0)
                {
                    printf("\nNenhuma pessoa cadastrada.\n");
                    break;
                }

                encontrarPessoa(pessoas, quantidade);

                break;

            case 4:

                if (pessoas == NULL || quantidade == 0)
                {
                    printf("\nNenhuma pessoa cadastrada.\n");
                    break;
                }

                compararPessoas(pessoas, quantidade);

                break;

            case 5:

                if (pessoas == NULL || quantidade == 0)
                {
                    printf("\nNenhuma pessoa cadastrada.\n");
                    break;
                }

                encontrarMaisSemelhante(pessoas, quantidade);

                break;

            case 6:

                if (pessoas == NULL || quantidade == 0)
                {
                    printf("\nNenhuma pessoa cadastrada.\n");
                    break;
                }

                exibirRanking(pessoas, quantidade);

                break;

            case 7:

                if (pessoas == NULL || quantidade == 0)
                {
                    printf("\nNenhuma pessoa cadastrada.\n");
                    break;
                }

                analisarPreferencias(pessoas, quantidade);

                break;

            case 0:

                printf("\nPrograma encerrado.\n");

                break;

            default:

                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    free(pessoas);

    return 0;
}

