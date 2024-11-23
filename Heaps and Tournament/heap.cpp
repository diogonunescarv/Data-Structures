#include <iostream>
#include <stdexcept> // para usar exceção com runtime_error
#include <utility>   // para usar swap

using namespace std;

struct dado {
  string nomeTarefa;
  char tipoTarefa;
  int energiaGasta;
  int tempoEstimado;
  int prioridade;
};

bool operator>(dado d1, dado d2) { return d1.energiaGasta > d2.energiaGasta; }

bool operator<(dado d1, dado d2) { return d1.energiaGasta < d2.energiaGasta; }

ostream &operator<<(ostream &output, const dado &d) {
  output << "[" << d.nomeTarefa << "/" << d.tipoTarefa << "/" << d.energiaGasta
         << "/" << d.tempoEstimado << "/" << d.prioridade << "]";
  return output;
}

class MaxHeap {
private:
  dado *heap;
  int capacidade;
  int tamanho;
  inline int pai(int i);
  inline int esquerdo(int i);
  inline int direito(int i);
  void corrigeDescendo(int i);
  void corrigeSubindo(int i);

public:
  MaxHeap(int cap);
  ~MaxHeap();
  void imprime();
  dado retiraRaiz();
  void insere(dado d);
};

MaxHeap::MaxHeap(int cap) {
  capacidade = cap;
  heap = new dado[capacidade];
  tamanho = 0;
}

MaxHeap::~MaxHeap() { delete[] heap; }

int MaxHeap::pai(int i) { return (i - 1) / 2; }

int MaxHeap::esquerdo(int i) { return (2 * i); }

int MaxHeap::direito(int i) { return (2 * i + 1); }

void MaxHeap::corrigeDescendo(int i) {
  int esq = esquerdo(i);
  int dir = direito(i);
  int maior = i;

  if (esq < tamanho && heap[esq] > heap[i]) {
    maior = esq;
  }

  if (dir < tamanho && heap[dir] > heap[maior]) {
    maior = dir;
  }

  if (maior != i) {
    swap(heap[i], heap[maior]);
    corrigeDescendo(maior);
  }
}

void MaxHeap::corrigeSubindo(int i) {
  int p = pai(i);
  if (p >= 0 && heap[i] > heap[p]) {
    swap(heap[i], heap[p]);
    corrigeSubindo(p);
  }
}

void MaxHeap::imprime() {
  if (tamanho == 0) {
    cout << "Heap vazia!" << endl;
    return;
  }
  for (int i = 0; i < tamanho; i++) {
    cout << heap[i] << " ";
  }
  cout << endl;
}

dado MaxHeap::retiraRaiz() {
  if (tamanho == 0) {
    throw runtime_error("Erro ao retirar raiz");
  }
  dado aux = heap[0];
  swap(heap[0], heap[tamanho - 1]);
  tamanho--;
  corrigeDescendo(0);
  return aux;
}

void MaxHeap::insere(dado d) {
  if (tamanho == capacidade) {
    throw runtime_error("Heap cheia");
  }
  heap[tamanho] = d; // Corrigido: usar tamanho, não tamanho+1
  corrigeSubindo(tamanho);
  tamanho++;
}

int main() {
  int capacidade;
  dado info;
  char comando;

  cin >> capacidade;
  MaxHeap meuHeap(capacidade);

  do {
    try {
      cin >> comando;
      switch (comando) {
      case 'i': // inserir
        cin >> info.nomeTarefa >> info.tipoTarefa >> info.energiaGasta >>
            info.tempoEstimado >> info.prioridade;
        meuHeap.insere(info);
        break;
      case 'r': // remover
        cout << meuHeap.retiraRaiz().nomeTarefa << endl;
        break;
      case 'p': // imprimir
        meuHeap.imprime();
        break;
      case 'f': // finalizar
        // checado no do-while
        break;
      default:
        cerr << "Comando inválido\n";
      }
    } catch (runtime_error &e) {
      cout << e.what() << endl;
    }
  } while (comando != 'f'); // finalizar execução

  return 0;
}
