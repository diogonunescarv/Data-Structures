#include <iostream>
#include <stdexcept>

using namespace std;

const int FILAVAZIA = -1;
const int CAPACIDADE_FILA = 6;

struct Dado {
  string nome;
  string assunto;
  char tipo;
  int nProcesso;
};

// Imprime informações de um dado qualquer.
void imprimir_dado(const Dado &umDado) {
  cout << "Nome: " << umDado.nome << " "
       << "Assunto: " << umDado.assunto << " "
       << "Tipo: " << umDado.tipo << " "
       << "Processo: " << umDado.nProcesso << endl;
}

class Fila {
private:
  Dado *mFila;
  int posPrimeiro, posUltimo;

public:
  // Constrói fila vazia.
  Fila();
  // Destrutor que desaloca memória.
  ~Fila();
  // Retira e retorna o elemento que estiver na primeira posição.
  Dado Desenfileirar();
  // Insere um elemento na fila.
  void Enfileirar(const Dado &d);
  // Apagar todos os dados da fila.
  void LimparTudo();
  // Imprime os valores do elemento que está na frente da fila, sem
  // Desenfileirar.
  inline void PrimeiroDaFila();
  // Informa se a fila está Vazia.
  inline bool Vazia();
  // Informa se a fila está Cheia.
  inline bool Cheia();
};

Fila::Fila() {
  mFila = new Dado[CAPACIDADE_FILA]; // Aloca o array de Dado com o tamanho
                                     // máximo da fila
  posPrimeiro = 0;
  posUltimo = FILAVAZIA; // Inicializa o último como -1 indicando fila vazia
}

Fila::~Fila() {
  delete[] mFila; // Desaloca o vetor dinâmico no destrutor.
}

Dado Fila::Desenfileirar() {
  if (this->Vazia()) {
    throw runtime_error("Erro: fila vazia!");
  }
  Dado dadoRemovido = mFila[posPrimeiro];

  // Avança o índice do primeiro elemento (com comportamento circular).
  if (posPrimeiro == posUltimo) {
    // Caso só haja um elemento, a fila ficará vazia.
    posPrimeiro = 0;
    posUltimo = FILAVAZIA;
  } else {
    posPrimeiro = (posPrimeiro + 1) % CAPACIDADE_FILA;
  }

  return dadoRemovido;
}

void Fila::Enfileirar(const Dado &d) {
  if (this->Cheia()) {
    throw runtime_error("Erro: fila cheia!");
  }

  // Se a fila está vazia, o primeiro e o último devem ser o mesmo.
  if (posUltimo == FILAVAZIA) {
    posPrimeiro = 0;
    posUltimo = 0;
  } else {
    // Atualiza o índice do último elemento (com comportamento circular).
    posUltimo = (posUltimo + 1) % CAPACIDADE_FILA;
  }

  mFila[posUltimo] = d;
}

void Fila::LimparTudo() {
  posPrimeiro = FILAVAZIA;
  posUltimo = FILAVAZIA;
}


void Fila::PrimeiroDaFila() {
  if (this->Vazia()) {
    throw runtime_error("Erro: fila vazia!");
  }
  imprimir_dado(mFila[posPrimeiro]);
}

bool Fila::Vazia() { return posUltimo == FILAVAZIA; }

bool Fila::Cheia() {
  // A fila está cheia quando o próximo índice de posUltimo atingiria posPrimeiro
  return ((posUltimo + 1) % CAPACIDADE_FILA) == posPrimeiro &&
         posUltimo != FILAVAZIA;
}

int main() {
  Fila fila;
  Dado info;
  char comando;
  do {
    try {
      cin >> comando;
      switch (comando) {
      case 'i': // inserir
        cin >> info.nome >> info.assunto >> info.tipo >> info.nProcesso;
        fila.Enfileirar(info);
        break;
      case 'r': // remover
        imprimir_dado(fila.Desenfileirar());
        break;
      case 'l': // limpar tudo
        fila.LimparTudo();
        break;
      case 'e': // espiar
        if (!fila.Vazia())
          fila.PrimeiroDaFila();
        else
          cout << "Erro: fila vazia!" << endl;
        break;
      case 'f': // finalizar
        // checado no do-while
        break;
      default:
        cerr << "comando inválido\n";
      }
    } catch (runtime_error &e) {
      cout << e.what() << endl;
    }
  } while (comando != 'f'); // finalizar execução

  // Imprimir os dados restantes na fila.
  while (!fila.Vazia()) {
    imprimir_dado(fila.Desenfileirar());
  }

  cout << endl;
  return 0;
}
