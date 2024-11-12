#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado {
  string nome;
  int premio;
  char tipo;
  int tempo;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado &umDado) {
  cout << "Nome: " << umDado.nome << " ";
  cout << "Premio: " << umDado.premio << " ";
  cout << "Tipo: " << umDado.tipo << " ";
  cout << "tempo: " << umDado.tempo << endl;
}

class Noh {
  friend class Fila;

private:
  Dado mDado; // poderia ser outro tipo de variável
  Noh *mProx;

public:
  Noh(Dado v) {
    mDado = v;
    mProx = NULL;
  }
};

class Fila {
public:
  // Constrói Fila vazia.
  Fila();
  // Destrutor que desaloca memória.
  ~Fila();
  // Retira e retorna o elemento que estiver na frente da Fila.
  // Escreve uma mensagem de erro se não for possível desenfileirar.
  Dado Desenfileirar();
  // Insere um elemento na Fila.
  void Enfileirar(const Dado &d);
  // Apagar todos os dados da Fila.
  void LimparTudo();
  void somarPremios(int corte);
  // Retorna o elemento que está na frente da Fila, sem desenfileirar.
  inline void Primeiro();
  // Informa se a Fila está Vazia.
  inline bool Vazia();
 

private:
  Noh *mPtPrimeiro;
  Noh *mPtrUltimo;
};

Fila::Fila() {
  mPtrUltimo = nullptr;
  mPtPrimeiro = nullptr;
}

Fila::~Fila() { LimparTudo(); }

Dado Fila::Desenfileirar() {
  if (this->Vazia())
    throw runtime_error("Erro: Fila vazia!");

  Noh *auxiliar = mPtPrimeiro;
  Dado dadoRemovido = mPtPrimeiro->mDado;
  mPtPrimeiro = mPtPrimeiro->mProx;

  if (mPtPrimeiro == nullptr) {
    mPtrUltimo = nullptr;
  }

  delete auxiliar; 
  return dadoRemovido;
}

void Fila::Enfileirar(const Dado &d) {
  Noh *novoNoh = new Noh(d);

  if (this->Vazia()) {
    mPtPrimeiro = novoNoh;
    mPtrUltimo = novoNoh;
  } else {
    mPtrUltimo->mProx = novoNoh;
    mPtrUltimo = novoNoh;
  }
}

void Fila::LimparTudo() {
  while (!this->Vazia()) {
    Desenfileirar();
  }
}

void Fila::Primeiro() {
  if (this->Vazia())
    throw runtime_error("Erro: Fila vazia!");
  imprimir_dado(mPtPrimeiro->mDado);
}

bool Fila::Vazia() { return mPtPrimeiro == nullptr; }

void Fila::somarPremios(int corte) {
  Fila Aux1, Aux2;  
  Dado nohAuxiliar;
  int total = 0;
  
  while(not Vazia()){
    nohAuxiliar = Desenfileirar();
    if (nohAuxiliar.tempo < corte){
       total += nohAuxiliar.premio;
       Aux1.Enfileirar(nohAuxiliar);
    } else {
       Aux2.Enfileirar(nohAuxiliar);
    }
  }
  
  while(not Aux1.Vazia()){
    nohAuxiliar = Aux1.Desenfileirar();
    Enfileirar(nohAuxiliar);
  }
  
  while(not Aux2.Vazia()){
    nohAuxiliar = Aux2.Desenfileirar();
    Enfileirar(nohAuxiliar);
  }
  
  cout << total << endl;
}

int main() {
  Fila fila;
  Dado info;
  char comando;
  int corte;
  do {
    try {
      cin >> comando;
      switch (comando) {
      case 'i': // inserir
        cin >> info.nome >> info.premio >> info.tipo >> info.tempo;
        fila.Enfileirar(info);
        break;
      case 'r': // remover
        imprimir_dado(fila.Desenfileirar());
        break;
      case 'l': // limpar tudo
        fila.LimparTudo();
        break;
      case 'e': // espiar
        fila.Primeiro();
        break;
      case 'f': // finalizar
        // checado no do-while
        break;
      case 'p': // finalizar

        cin >> corte;
        fila.somarPremios(corte);
        break;
      default:
        cerr << "comando inválido\n";
      }
    } catch (runtime_error &e) {
      cout << e.what() << endl;
    }
  } while (comando != 'f'); // finalizar execução
  while (not fila.Vazia()) {
    imprimir_dado(fila.Desenfileirar());
  }
  cout << endl;
  return 0;
}

