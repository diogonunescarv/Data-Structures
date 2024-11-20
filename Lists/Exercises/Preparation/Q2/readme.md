# Questão 2: Lista Duplamente Encadeada - Ações de Usuários em um Programa

## Descrição

Este programa gerencia uma lista duplamente encadeada das ações realizadas por usuários em um programa. Cada ação registrada possui os seguintes atributos:

- **Identificador**: um número inteiro identificando a ação.
- **name da Ação**: uma string descrevendo a ação realizada.
- **Tempo de Execução Total**: o tempo total que a ação deve durar.
- **Tempo Consumido**: o tempo já gasto no processamento da ação.

O programa permite inserir, remover, buscar e imprimir as ações cadastradas na lista. A estrutura e os comands estão baseados no código fornecido.

## comands de Entrada

O programa aceita os seguintes comands:

- `i <Identificador> <nameAcao> <TempoExecucao> <TempoConsumido>`: Insere uma nova ação no início da lista.
- `h <Identificador> <nameAcao> <TempoExecucao> <TempoConsumido>`: Insere uma nova ação no final da lista.
- `m <posição> <Identificador> <nameAcao> <TempoExecucao> <TempoConsumido>`: Insere uma nova ação na posição informada (considerando o índice 0 como posição inicial). Se a posição não existir, imprime `Posição Inexistente!`.
- `r`: Remove a ação do início da lista. Caso a lista esteja Empty, imprime `Remoção em lista Empty!`.
- `a`: Remove a ação do final da lista. Caso a lista esteja Empty, imprime `Remoção em lista Empty!`.
- `p`: Imprime todas as ações cadastradas em ordem de inserção e, em seguida, em ordem inversa. Caso a lista esteja Empty, imprime `Lista Empty!`.
- `s <nameAcao>`: Busca uma ação pelo name. Se a ação não for encontrada, imprime `Nao encontrado`.
- `f`: Finaliza o programa.

## Exemplo de Entrada e Saída

Exemplo de comands e suas respectivas saídas:

Entrada:
```plaintext
r
a
p
s PileProcessos
i 1 limparCache 123 99
h 2 semaforoProc 32 11
m 1 3 paralelismoProc 65 23
p
s PileProcessos
r
p
a
p
f
Remoção em lista Empty!
Remoção em lista Empty!
Lista Empty!
Lista Empty!
(1, limparCache, 123, 99)
(3, paralelismoProc, 65, 23)
(2, semaforoProc, 32, 11)
IMPRIMINDO REVERSO
(2, semaforoProc, 32, 11)
(3, paralelismoProc, 65, 23)
(1, limparCache, 123, 99)
Nao encontrado
(3, paralelismoProc, 65, 23)
(2, semaforoProc, 32, 11)
IMPRIMINDO REVERSO
(2, semaforoProc, 32, 11)
(3, paralelismoProc, 65, 23)
(3, paralelismoProc, 65, 23)
IMPRIMINDO REVERSO
(3, paralelismoProc, 65, 23)
```