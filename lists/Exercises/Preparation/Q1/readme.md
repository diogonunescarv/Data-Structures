# Questão 1: Lista Simplesmente Encadeada - Equipes de Maratona

## Descrição

Este programa gerencia uma lista encadeada de equipes participantes de uma maratona de programação. Cada equipe possui os seguintes atributos:

- **Nome da Equipe**: uma string.
- **Nome do Líder**: uma string.
- **Linguagem de Programação**: uma string.
- **Quantidade de Membros**: um número inteiro.

O programa permite inserir, remover, buscar e imprimir as equipes cadastradas na lista encadeada. A estrutura e os comandos estão baseados no código fornecido.

## Comandos de Entrada

O programa aceita os seguintes comandos:

- `i <NomeEquipe> <Lider> <Linguagem> <QtdMembros>`: Insere uma nova equipe no início da lista.
- `h <NomeEquipe> <Lider> <Linguagem> <QtdMembros>`: Insere uma nova equipe no final da lista.
- `m <posição> <NomeEquipe> <Lider> <Linguagem> <QtdMembros>`: Insere uma nova equipe na posição informada (índice 0 é a posição inicial). Se a posição não existir, imprime `Posição Inexistente!`.
- `r`: Remove a equipe do início da lista. Caso a lista esteja vazia, imprime `Remoção em lista vazia!`.
- `a`: Remove a equipe do final da lista. Caso a lista esteja vazia, imprime `Remoção em lista vazia!`.
- `p`: Imprime todas as equipes cadastradas no formato `(Nome, Lider, Linguagem, QtdMembros)`. Caso a lista esteja vazia, imprime `Lista vazia!`.
- `s <NomeEquipe>`: Busca uma equipe pelo nome. Se a equipe não for encontrada, imprime `Nao encontrado`.
- `f`: Finaliza o programa.

## Exemplo de Entrada e Saída

Exemplo de comandos e suas respectivas saídas:

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
Remoção em lista vazia!
Remoção em lista vazia!
Lista vazia!
Lista vazia!
(Vingadores, Stark, Ruby, 3)
(MuppetBabies, Kermit, Python, 9)
(LigaDaJustica, Batman, C++, 4)
Nao encontrado
(MuppetBabies, Kermit, Python, 9)
(LigaDaJustica, Batman, C++, 4)
(MuppetBabies, Kermit, Python, 9)
```
