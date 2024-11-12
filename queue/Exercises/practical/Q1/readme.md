# Questão 1: Fila com Encadeamento - Lista de Tarefas do Jogador - Maior Recompensa no Prazo

## Descrição

Este projeto é uma extensão da implementação de uma estrutura de dados do tipo **fila**, utilizando encadeamento de nós, para gerenciar uma lista de tarefas de um jogador. Nesta versão, o campo **prêmio** foi alterado para representar um valor em **moedas digitais** (inteiro), indicando a recompensa obtida pela conclusão de cada tarefa.

Foi adicionada uma funcionalidade que permite contabilizar e somar as recompensas das atividades com tempo inferior a um valor informado pelo jogador. Essas atividades são movidas para o início da fila. Se não houver atividades com tempo inferior ao valor especificado, o programa imprime `0`.

## Estrutura dos Itens

Cada item da lista de tarefas possui os seguintes atributos:

- **Nome da Tarefa**: uma string sem espaços.
- **Prêmio**: um valor inteiro representando moedas digitais.
- **Tipo**: um único caractere.
- **Tempo para Realização**: um número inteiro.

## Comandos de Entrada

O programa aceita os seguintes comandos para manipulação da fila de tarefas:

- `i <nome_da_tarefa> <premio> <tipo> <tempo>`: Insere uma tarefa na lista de tarefas do jogador.
- `r`: Remove o item do frente da lista de tarefas.
- `l`: Limpa (remove todos os itens) da lista de tarefas.
- `e`: Exibe o item na frente da lista de tarefas (sem removê-lo).
- `p <tempo>`: Calcula e exibe o valor total das recompensas das tarefas que possuem um tempo menor que o valor especificado. Estas tarefas são movidas para o início da fila.
- `f`: Finaliza a execução do programa.

## Comportamento das Saídas

As saídas de cada comando já estão implementadas na função principal do código fornecido, exceto pela remoção de itens após a execução do programa. Ao finalizar (`f`), todos os itens da fila são desenfileirados e exibidos.

## Exemplo de Entrada e Saída

Entrada:
```plaintext
r
i destruirArmazen 252 f 100
i salvarDonzela 888 e 300
i montarObservatorioMonteM2 582 d 400
i eliminarChefao 12585 a 2000
i eliminarBando 25354 a 30000
p 500
r
e
f
Erro: fila vazia!
1722
Nome: destruirArmazen Premio: 252 Tipo: f Tempo: 100
Nome: salvarDonzela Premio: 888 Tipo: e Tempo: 300
Nome: montarObservatorioMonteM2 Premio: 582 Tipo: d Tempo: 400
Nome: eliminarChefao Premio: 12585 Tipo: a Tempo: 2000
Nome: eliminarBando Premio: 25354 Tipo: a Tempo: 30000
```
