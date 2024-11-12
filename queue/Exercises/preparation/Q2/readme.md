# Questão 2: Fila com Encadeamento - Lista de Tarefas do Jogador

## Descrição

Este projeto implementa uma estrutura de dados do tipo **fila**, utilizando encadeamento de nós, para gerenciar uma lista de tarefas de um jogador. Com base no código fornecido, a estrutura permite as seguintes operações:
- **Enfileiramento** de itens na fila.
- **Desenfileiramento** de itens da fila.
- **Verificação** do item no frente da fila (sem removê-lo).
- **Limpeza** da lista de tarefas (remoção de todos os elementos).

O desenfileiramento gera uma mensagem de erro ("Erro: fila vazia!") caso a fila já esteja vazia. Cada item na lista de tarefas possui os seguintes atributos:

- **Nome da Tarefa**: uma string sem espaços.
- **Prêmio**: uma string sem espaços.
- **Tipo**: um único caractere.
- **Tempo para Realização**: um número inteiro.

## Comandos de Entrada

O programa aceita os seguintes comandos para manipulação da fila de tarefas:

- `i <nome_da_tarefa> <premio> <tipo> <tempo>`: Insere uma tarefa na lista de tarefas do jogador.
- `r`: Remove o item do frente da lista de tarefas.
- `l`: Limpa (remove todos os itens) da lista de tarefas.
- `e`: Exibe o item na frente da lista de tarefas (sem removê-lo).
- `f`: Finaliza a execução do programa.

## Comportamento das Saídas

As saídas de cada comando já estão implementadas na função principal do código fornecido. Ao finalizar o programa (`f`), todos os itens da fila são desenfileirados e exibidos.

## Exemplo de Entrada e Saída

Entrada:
```plaintext
r
i destruirArmazen jaqueta f 100
i salvarDonzela hb20 e 300
i montarObservatorioMonteM2 binoculo d 400
i eliminarChefao milDolares a 2000
i eliminarBando dezmilDolares a 30000
r
e
f
Erro: fila vazia!
Nome: destruirArmazen Premio: jaqueta Tipo: f Tempo: 100
Nome: salvarDonzela Premio: hb20 Tipo: e Tempo: 300
Nome: montarObservatorioMonteM2 Premio: binoculo Tipo: d Tempo: 400
Nome: eliminarChefao Premio: milDolares Tipo: a Tempo: 2000
Nome: eliminarBando Premio: dezmilDolares Tipo: a Tempo: 30000
```
