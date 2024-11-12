# Questão 1: Fila com Armazenamento em Vetor - Lista de Processos em uma Repartição Pública

## Descrição

Este projeto implementa uma estrutura de dados do tipo **fila**, utilizando armazenamento em vetor, para gerenciar uma lista de processos em uma repartição pública. Baseado no código fornecido, a estrutura oferece as seguintes funcionalidades:
- **Enfileiramento** de itens na fila.
- **Desenfileiramento** de itens da fila.
- **Verificação** do item no topo da fila (sem removê-lo).
- **Limpeza** da fila (remoção de todos os elementos).

O desenfileiramento gera uma mensagem de erro ("Erro: fila vazia!") caso a fila já esteja vazia. Da mesma forma, o enfileiramento gera uma mensagem de erro ("Erro: fila cheia!") quando todas as posições do vetor estão ocupadas. A repartição pública gerencia até **seis processos simultaneamente**.

## Estrutura dos Itens

Cada item da fila representa um processo e possui os seguintes atributos:
- **Assunto**: uma string sem espaços.
- **Nome do Interessado**: uma string sem espaços.
- **Tipo**: um único caractere.
- **Número do Processo**: um número inteiro.

## Comandos de Entrada

O programa aceita os seguintes comandos para manipulação da fila:

- `i <assunto> <nome> <tipo> <numero>`: Insere um item na lista de processos.
- `r`: Remove o item do topo da lista de processos.
- `l`: Limpa (remove todos os itens) da lista de processos.
- `e`: Exibe o item no topo da lista de processos (sem removê-lo).
- `f`: Finaliza a execução do programa.

## Comportamento das Saídas

As saídas de cada comando já estão implementadas na função principal do código exemplo fornecido. Ao finalizar o programa (`f`), todos os itens da fila são desenfileirados e exibidos.

## Exemplo de Entrada e Saída

Entrada:
```plaintext
r
i processo1 Joao a 2
i processo2 Maria c 5
i processo3 Severino d 9
i processo4 Marcos f 12
i processo5 Barnabe a 10
i processo6 Tiao z 22
i processo7 Marlon a 40
r
e
i processo7 Marlon a 40
f
Erro: fila vazia!
Erro: fila cheia!
Nome: processo1 Assunto: Joao Tipo: a Processo: 2
Nome: processo2 Assunto: Maria Tipo: c Processo: 5
Nome: processo3 Assunto: Severino Tipo: d Processo: 9
Nome: processo4 Assunto: Marcos Tipo: f Processo: 12
Nome: processo5 Assunto: Barnabe Tipo: a Processo: 10
Nome: processo6 Assunto: Tiao Tipo: z Processo: 22
Nome: processo7 Assunto: Marlon Tipo: a Processo: 40
```
