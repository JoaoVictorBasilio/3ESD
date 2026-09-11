#include <stdio.h>

#include <math.h>

#include <string.h>

#include <stdlib.h>

#define QTD_PREF 6

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

void cadastrarPessoas(char nomes[][50], float *notas, int quantidade)
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
        scanf(" %49[^\n]", nomes[i]);

        for (j = 0; j < QTD_PREF; j++)
        {
            printf("Nota para %s: ", preferencias[j]);
            notas[i * QTD_PREF + j] = leNotaValida();
        }
    }
}

void exibirPessoas(char nomes[][50], float *notas, int quantidade)
{
    int i;
    int j;

    printf("\n=================================================================\n");
    printf("%-18s MUS   CIN   JOG   ESP   LEI   PROG\n", "NOME");
    printf("=================================================================\n");

    for (i = 0; i < quantidade; i++)
    {
        printf("%-18s", nomes[i]);

        for (j = 0; j < QTD_PREF; j++)
        {
            printf("%-6.1f", notas[i * QTD_PREF + j]);
        }

        printf("\n");
    }

    printf("=================================================================\n");
}

int buscaPessoa(char nomes[][50], int quantidade, char pessoa[])
{
    int i;

    for (i = 0; i < quantidade; i++)
    {
        /* strcmp devolve zero quando as strings sao iguais. */
        if (strcmp(pessoa, nomes[i]) == 0)
        {
            return i;
        }
    }

    return -1;
}

void encontrarPessoa(char nomes[][50], float *notas, int quantidade)
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

    indice = buscaPessoa(nomes, quantidade, pessoa);

    if (indice == -1)
    {
        printf("Pessoa nao cadastrada.\n");
        return;
    }

    printf("\nInteresses de %s:\n", nomes[indice]);

    for (j = 0; j < QTD_PREF; j++)
    {
        printf("%s: %.1f\n", preferencias[j], notas[indice * QTD_PREF + j]);
    }
}

float calculaDistancia(float *notas, int pessoa1, int pessoa2)
{
    float soma = 0;
    float diferenca;
    int j;

    for (j = 0; j < QTD_PREF; j++)
    {
        diferenca = notas[pessoa1 * QTD_PREF + j]
                  - notas[pessoa2 * QTD_PREF + j];

        soma = soma + diferenca * diferenca;
    }

    return sqrt(soma);
}

void compararPessoas(char nomes[][50], float *notas, int quantidade)
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

void encontrarMaisSemelhante(char nomes[][50], float *notas, int quantidade)
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

void exibirRanking(
    char nomes[][50],
    float *notas,
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
    scanf(" %49[^\n]", ref);

    indice = buscaPessoa(nomes, quantidade, ref);

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

    indices = (int *) malloc(
        (quantidade - 1) * sizeof(int)
    );

    if (indices == NULL)
    {
        printf("Erro ao alocar memoria para os indices.\n");
        return;
    }

    distancias = (float *) malloc(
        (quantidade - 1) * sizeof(float)
    );

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
                calculaDistancia(notas, indice, i);

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
    printf("PERFIS MAIS PROXIMOS DE %s\n", nomes[indice]);
    printf("========================================\n");

    for (i = 0; i < quantidadeRanking; i++)
    {
        printf(
            "%d - %s: %.2f\n",
            i + 1,
            nomes[indices[i]],
            distancias[i]
        );
    }

    free(indices);
    free(distancias);
}

void analisarPreferencias(
    char nomes[][50],
    float *notas,
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

    /* Calcula a diferenca absoluta em cada preferencia. */
    for (j = 0; j < QTD_PREF; j++)
    {
        diferencas[j] = fabs(
            notas[pessoa1 * QTD_PREF + j] -
            notas[pessoa2 * QTD_PREF + j]
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
    printf("%s x %s\n\n", nomes[pessoa1], nomes[pessoa2]);

    printf(
        "%-15s %-10s %-10s %-10s\n",
        "Preferencia",
        nomes[pessoa1],
        nomes[pessoa2],
        "Diferenca"
    );

    printf("-------------------------------------------------\n");

    for (j = 0; j < QTD_PREF; j++)
    {
        printf(
            "%-15s %-10.1f %-10.1f %-10.1f\n",
            preferencias[j],
            notas[pessoa1 * QTD_PREF + j],
            notas[pessoa2 * QTD_PREF + j],
            diferencas[j]
        );
    }

    printf("-------------------------------------------------\n");

    distancia = calculaDistancia(notas, pessoa1, pessoa2);
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
    char (*nomes)[50] = NULL;
    float *notas = NULL;
    int quantidade = 0;
    int opcao;

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

        printf("\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:

                free(nomes);
                nomes = NULL;

                if (notas != NULL)
                {
                    free(notas);
                    notas = NULL;
                }

                printf("\nDigite a quantidade de pessoas: ");
                scanf("%d", &quantidade);

                if (quantidade <= 0)
                {
                    printf("Quantidade invalida.\n");
                    quantidade = 0;
                    break;
                }

                nomes = malloc(quantidade * sizeof(*nomes));

                if (nomes == NULL)
                {
                    printf("Erro ao alocar memoria.\n");
                    quantidade = 0;
                    break;
                }

                notas = malloc(quantidade * QTD_PREF * sizeof(float));

                if (notas == NULL)
                {
                    printf("Erro ao alocar memoria.\n");
                    free(nomes);
                    nomes = NULL;
                    quantidade = 0;
                    break;
                }

                cadastrarPessoas(nomes, notas, quantidade);

                break;

            case 2:

                if (quantidade == 0 || notas == NULL)
                {
                    printf("\nNenhuma pessoa cadastrada.\n");
                }
                else
                {
                    exibirPessoas(nomes, notas, quantidade);
                }

                break;

            case 3:

                if (quantidade == 0)
                {
                    printf("\nNenhuma pessoa cadastrada.\n");
                }
                else
                {
                    encontrarPessoa(nomes, notas, quantidade);
                }

                break;

            case 4:

                if (quantidade < 2 || notas == NULL)
                {
                    printf("\nCadastre pelo menos duas pessoas.\n");
                }
                else
                {
                    compararPessoas(nomes, notas, quantidade);
                }

                break;

            case 5:

                if (quantidade < 2 || notas == NULL)
                {
                    printf("\nCadastre pelo menos duas pessoas.\n");
                }
                else
                {
                    encontrarMaisSemelhante(nomes, notas, quantidade);
                }

                break;

            case 6:

                if (quantidade < 2 || notas == NULL)
                {
                    printf("\nCadastre pelo menos duas pessoas.\n");
                }
                else
                {
                    exibirRanking(nomes, notas, quantidade);
                }

                break;

            case 7:

                if (quantidade < 2 || notas == NULL)
                {
                    printf("\nCadastre pelo menos duas pessoas.\n");
                }
                else
                {
                    analisarPreferencias(nomes, notas, quantidade);
                }

                break;

            case 0:

                printf("\nEncerrando o programa...\n");

                break;

            default:

                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    free(notas);
    free(nomes);

    return 0;
}

