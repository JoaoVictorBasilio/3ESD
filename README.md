# 3ESD

Repositório da disciplina de Estruturas de Dados (3ESD) da FAETERJ-RIO.

Este projeto reúne implementações de TADs e exercícios práticos em C, com foco em:
- manipulação de dados e estruturas dinâmicas
- representação de datas, horas e instantes temporais
- conjuntos e matrizes
- reservas, bolsas e escala de trabalho
- validação de regras de negócio em programas de teste

## Estrutura principal
- TAD: implementação de um TAD de Data e Reserva
- TAD2: conjunto de TADs complementares, como Altura, Massa, Bagagem, Conjunto, Horário, Data, Instante, Matriz e Escala

## Compilação rápida
Para compilar a TAD2, execute:

```bash
cd /opt/lampp/htdocs/Codigos/3ESD/TAD2
mkdir -p output
gcc -Wall -Wextra -std=c11 *.c -o output/main
./output/main
```

Os programas foram organizados para facilitar a leitura e a compreensão dos conceitos de encapsulamento, tipos abstratos de dados e operações básicas sobre estruturas.
