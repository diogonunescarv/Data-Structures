#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


struct equipe{
    string nomeEquipe;
    string lider;
    string linguagem;
    int qtdMembros;
};

class noh {
friend class lista;
private:
    equipe elenco; // poderia ser outro tipo de variável
    noh* proximo;
public:
    //noh();
    noh(equipe d);
};

// construindo time chamando seu construtor
noh::noh(equipe d){
    elenco = d;
    proximo = NULL;
}


// lista dinamicamente encadeada
class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
     // imprime reverso a partir de um nó -> exemplo de uso de recursão
    void imprimeReversoAux(noh* umNoh);
public:
    // construtores e destrutor
    lista();
    lista(const lista& umaLista);
    ~lista();
    // sobrecarga do operador de atribuição
    lista& operator=(const lista& umaLista);
    // inserção, remoção e procura
    inline void insere(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor); // retorna a posição do nó com va
    // métodos adicionais (impressão, vazia)
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};


// constrói uma lista inicialmente vazia
lista::lista() {
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;
}

// construtor de cópia
lista::lista(const lista& umaLista) {
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;

  noh* aux = umaLista.primeiro;

  while (aux != NULL){
    insereNoFim(aux->elenco);
    aux = aux->proximo;
  }
}

// destrutor da lista (chama função privada auxiliar)
lista::~lista( ) {
  removeTodos();
}

// remove todos os elementos da lista
void lista::removeTodos( ) {
  noh* aux = primeiro;
  noh* temp;

  while (aux != NULL){
    temp = aux;
    aux = aux->proximo;
    delete temp;
  }

  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;
}

// sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista){
    // limpa a lista atual
    removeTodos();
     // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;

    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }

    return *this;
}

// insere no final da lista
void lista::insereNoFim(equipe elenco) {
  noh* novo = new noh(elenco);
  if(vazia()){
    primeiro = novo;
    ultimo = novo;
  } else{
    ultimo->proximo = novo;
    ultimo = novo;
  }
  tamanho++;
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco) {
  noh* novo = new noh(elenco);
  if(vazia()){
    primeiro = novo;
    ultimo = novo;
  } else{
    novo->proximo = primeiro;
    primeiro = novo;
  }
  tamanho++;
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, equipe elenco){
  noh* novo = new noh(elenco);

  if ((posicao <= tamanho) && (posicao >= 0)){
    if(vazia()){
        insereNoInicio(elenco);
    } else if (posicao == 0){
        insereNoInicio(elenco);
    } else if (posicao == tamanho){
        insereNoFim(elenco);
    } else {
        noh* aux = primeiro;
        int posAux = 0;

        while (posAux != (posicao - 1)){
            aux = aux->proximo;
            posAux++;
        }

        novo->proximo = aux->proximo;
        aux->proximo = novo;
        tamanho++;
    }
  } else {
    cout << "Posição Inexistente!" << endl;
  }
}

//procura a posição de um determinado elemento
int lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }

    noh* aux = primeiro;
    int posAux = 0;

    while ((aux != NULL) && (aux->elenco.nomeEquipe != valor)){
        aux = aux->proximo;
        posAux++;
    }

    if (aux == NULL) {
        posAux = -1;
    }

    return posAux;

}


// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }

    noh* aux = primeiro;

    while ((aux != NULL)){
        cout << "(" + aux->elenco.nomeEquipe + ", " + aux->elenco.lider + ", " + aux->elenco.linguagem + ", " << aux->elenco.qtdMembros << ")" << endl;
        aux = aux->proximo;
    }
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return (primeiro == NULL);
}

void lista::removeNoFim() {
    if (vazia()) {
        cout << "Remoção em lista vazia!" << endl;
        return;
    }
    if (primeiro == ultimo) {
        delete primeiro;
        primeiro = NULL;
        ultimo = NULL;
    } else {
        noh* atual = primeiro;
        while (atual->proximo != ultimo) {
            atual = atual->proximo;
        }
        delete ultimo;
        ultimo = atual;
        ultimo->proximo = NULL;
    }
    tamanho--;
}

void lista::removeNoInicio() {
    if (vazia()) {
        cout << "Remoção em lista vazia!" << endl;
        return;
    }
    noh* aux = primeiro;
    primeiro = primeiro->proximo;
    delete aux;
    if (primeiro == NULL) {
        ultimo = NULL;
    }
    tamanho--;
}

int main() {
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoFim(info);
                    break;
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;
                case 's': // remover
                    cin >> nomeEquipe;
                    if(minhaLista.procura(nomeEquipe) == -1){
                        cout <<  "Nao encontrado" << endl;
                    } else{
                        cout << minhaLista.procura(nomeEquipe) << endl;
                    }

                    break;
                case 'r': // remover
                    minhaLista.removeNoInicio();
                    break;
                case 'a': // remover
                    minhaLista.removeNoFim();
                    break;
                case 'p': // limpar tudo
                    minhaLista.imprime();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}
