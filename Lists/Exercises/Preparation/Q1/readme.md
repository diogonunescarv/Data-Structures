# Questão 1: Lista Simplesmente Encadeada - Equipes de Maratona

## Descrição

Este programa gerencia uma lista encadeada de equipes participantes de uma maratona de programação. Cada equipe possui os seguintes atributos:

- **name da Equipe**: uma string.
- **name do Líder**: uma string.
- **Linguagem de Programação**: uma string.
- **Quantidade de Membros**: um número inteiro.

O programa permite inserir, remover, buscar e imprimir as equipes cadastradas na lista encadeada. A estrutura e os comands estão baseados no código fornecido.

## comands de Entrada

O programa aceita os seguintes comands:

- `i <nameEquipe> <Lider> <Linguagem> <QtdMembros>`: Insere uma nova equipe no início da lista.
- `h <nameEquipe> <Lider> <Linguagem> <QtdMembros>`: Insere uma nova equipe no final da lista.
- `m <posição> <nameEquipe> <Lider> <Linguagem> <QtdMembros>`: Insere uma nova equipe na posição informada (índice 0 é a posição inicial). Se a posição não existir, imprime `Posição Inexistente!`.
- `r`: Remove a equipe do início da lista. Caso a lista esteja Empty, imprime `Remoção em lista Empty!`.
- `a`: Remove a equipe do final da lista. Caso a lista esteja Empty, imprime `Remoção em lista Empty!`.
- `p`: Imprime todas as equipes cadastradas no formato `(name, Lider, Linguagem, QtdMembros)`. Caso a lista esteja Empty, imprime `Lista Empty!`.
- `s <nameEquipe>`: Busca uma equipe pelo name. Se a equipe não for encontrada, imprime `Nao encontrado`.
- `f`: Finaliza o programa.

## Exemplo de Entrada e Saída

Exemplo de comands e suas respectivas saídas:

Entrada:
```plaintext
r
a
p
s Thundercats
i Vingadores Stark Ruby 3
h LigaDaJustica Batman C++ 4
m 1 MuppetBabies Kermit Python 9
p
s Thundercats
r
p
a
p
f
Remoção em lista Empty!
Remoção em lista Empty!
Lista Empty!
Lista Empty!
(Vingadores, Stark, Ruby, 3)
(MuppetBabies, Kermit, Python, 9)
(LigaDaJustica, Batman, C++, 4)
Nao encontrado
(MuppetBabies, Kermit, Python, 9)
(LigaDaJustica, Batman, C++, 4)
(MuppetBabies, Kermit, Python, 9)
```
