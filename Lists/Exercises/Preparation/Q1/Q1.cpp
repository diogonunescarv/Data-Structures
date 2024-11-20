#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


struct equipe{
    string nameEquipe;
    string lider;
    string linguagem;
    int qtdMembros;
};

class Node {
friend class lista;
private:
    equipe elenco; // poderia ser outro type de variável
    Node* proximo;
public:
    //Node();
    Node(equipe d);
};

// construindo time chamando seu construtor
Node::Node(equipe d){
    elenco = d;
    proximo = NULL;
}


// lista dinamicamente encadeada
class lista {
private:
    Node* primeiro;
    Node* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
     // imprime reverso a partir de um nó -> exemplo de uso de recursão
    void imprimeReversoAux(Node* umNode);
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
    int procura(string value); // retorna a posição do nó com va
    // métodos adicionais (impressão, Empty)
    void imprime();
    void imprimeReverso();
    inline bool Empty();
    void removeNoFim();
    void removeNoInicio();
};


// constrói uma lista inicialmente Empty
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

  Node* aux = umaLista.primeiro;

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
  Node* aux = primeiro;
  Node* temp;

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
     // percorre a lista recebida como parâmetro, copiando os Datas
    Node* aux = umaLista.primeiro;

    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }

    return *this;
}

// insere no final da lista
void lista::insereNoFim(equipe elenco) {
  Node* novo = new Node(elenco);
  if(Empty()){
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
  Node* novo = new Node(elenco);
  if(Empty()){
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
  Node* novo = new Node(elenco);

  if ((posicao <= tamanho) && (posicao >= 0)){
    if(Empty()){
        insereNoInicio(elenco);
    } else if (posicao == 0){
        insereNoInicio(elenco);
    } else if (posicao == tamanho){
        insereNoFim(elenco);
    } else {
        Node* aux = primeiro;
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
int lista::procura(string value) {
    if (Empty()) {
        throw runtime_error("Lista Empty!");
    }

    Node* aux = primeiro;
    int posAux = 0;

    while ((aux != NULL) && (aux->elenco.nameEquipe != value)){
        aux = aux->proximo;
        posAux++;
    }

    if (aux == NULL) {
        posAux = -1;
    }

    return posAux;

}


// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valuees, por exemplo)
void lista::imprime() {
    if (Empty()) {
        throw runtime_error("Lista Empty!");
    }

    Node* aux = primeiro;

    while ((aux != NULL)){
        cout << "(" + aux->elenco.nameEquipe + ", " + aux->elenco.lider + ", " + aux->elenco.linguagem + ", " << aux->elenco.qtdMembros << ")" << endl;
        aux = aux->proximo;
    }
}

// verifica se a lista está Empty
inline bool lista::Empty() {
    return (primeiro == NULL);
}

void lista::removeNoFim() {
    if (Empty()) {
        cout << "Remoção em lista Empty!" << endl;
        return;
    }
    if (primeiro == ultimo) {
        delete primeiro;
        primeiro = NULL;
        ultimo = NULL;
    } else {
        Node* atual = primeiro;
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
    if (Empty()) {
        cout << "Remoção em lista Empty!" << endl;
        return;
    }
    Node* aux = primeiro;
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
    char comand;
    int posicao;
    string nameEquipe;

    do {
        try {
            cin >> comand;
            switch (comand) {
                case 'i': // inserir
                    cin >> info.nameEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.nameEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoFim(info);
                    break;
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.nameEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;
                case 's': // remover
                    cin >> nameEquipe;
                    if(minhaLista.procura(nameEquipe) == -1){
                        cout <<  "Nao encontrado" << endl;
                    } else{
                        cout << minhaLista.procura(nameEquipe) << endl;
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
                    cerr << "comand inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comand != 'f'); // finalizar execução
    cout << endl;
    return 0;
}
