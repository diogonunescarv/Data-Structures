// TORNEIO

#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int INVALIDO = -1;

class torneio {
private:
  int *heap;
  int tamanho;
  int capacidade;
  int inicioDados;
  inline int pai(int filho);
  inline int esquerda(int getPai);
  inline int direita(int getPai);
  void arruma();
  void compete(int i);
  void verBaseMaior();

public:
  torneio(int vet[], int tam);
  ~torneio();
};

// Construtor da classe
torneio::torneio(int vet[], int tam) {
  capacidade = tam * 2 - 1;
  heap = new int[capacidade];

  // Inicializando os nós folha com os valores do vetor de entrada
  for (int i = 0; i < tam; i++) {
    heap[capacidade - tam + i] = vet[i];
  }

  // Preenchendo as posições intermediárias com valores inválidos (ainda não
  // competiram)
  for (int i = 0; i < capacidade - tam; i++) {
    heap[i] = INVALIDO;
  }

  tamanho = tam;
  inicioDados = capacidade - tam;

  arruma(); 
}

// Destrutor da classe
torneio::~torneio() { delete[] heap; }

// Retorno a posição do nó pai de um determinado elemento
int torneio::pai(int filho) { return (filho - 1) / 2; }

// Retorna o filho à esquerda de um determinado nó
int torneio::esquerda(int pai) { return 2 * pai + 1; }

// Retorna o filho à direita do nó pai
int torneio::direita(int pai) { return 2 * pai + 2; }

// Faz a competição por cada posição vencedora no vetor e imprime o vencedor
void torneio::arruma() {
  for (int i = inicioDados - 1; i >= 0; i--) {
    compete(i); 
  }
  cout << heap[0]
       << endl; 
}

// Faz a competição entre os elementos
void torneio::compete(int i) {
  int esq = esquerda(i);
  int dir = direita(i);

  if (esq < capacidade && dir < capacidade) {
    if (heap[esq] != INVALIDO && heap[dir] != INVALIDO) {
      heap[i] = max(heap[esq], heap[dir]);
    } else if (heap[esq] != INVALIDO) {
      heap[i] = heap[esq];
    } else if (heap[dir] != INVALIDO) {
      heap[i] = heap[dir];
    }
  }
}

int main() {
  int tam;
  cin >> tam;

  int vet[tam];
  for (int i = 0; i < tam; i++) {
    cin >> vet[i];
  }

  torneio participantes(vet, tam);

  return 0;
}
