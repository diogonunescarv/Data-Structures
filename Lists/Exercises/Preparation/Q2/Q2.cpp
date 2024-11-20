#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

struct acaoPrograma {
    int identificador;
    string nameAcao;
    int tempoExecucao;
    int tempoConsumido;
};

class Node {
friend class listadup;
private:
    acaoPrograma acao;
    Node* proximo;
    Node* anterior;
public:
    Node(acaoPrograma d);
};

Node::Node(acaoPrograma d) {
    acao = d;
    proximo = NULL;
    anterior = NULL;
}

class listadup {
private:
    Node* primeiro;
    Node* ultimo;
    int tamanho;
    void removeTodos();
public:
    listadup();
    listadup(const listadup& umaLista);
    ~listadup();
    listadup& operator=(const listadup& umaLista);
    void insereNoFim(acaoPrograma acao);
    void insereNoInicio(acaoPrograma acao);
    void insereNaPosicao(int posicao, acaoPrograma acao);
    int procura(string value);
    void imprime();
    inline bool Empty();
    void removeNoFim();
    void removeNoInicio();
};

listadup::listadup() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

listadup::~listadup() {
    removeTodos();
}

void listadup::removeTodos() {
    Node* aux = primeiro;
    while (aux != NULL) {
        Node* temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

void listadup::insereNoFim(acaoPrograma acao) {
    Node* novo = new Node(acao);
    if (Empty()) {
        primeiro = novo;
        ultimo = novo;
    } else {
        ultimo->proximo = novo;
        novo->anterior = ultimo;
        ultimo = novo;
    }
    tamanho++;
}

void listadup::insereNoInicio(acaoPrograma acao) {
    Node* novo = new Node(acao);
    if (Empty()) {
        primeiro = novo;
        ultimo = novo;
    } else {
        novo->proximo = primeiro;
        primeiro->anterior = novo;
        primeiro = novo;
    }
    tamanho++;
}

void listadup::insereNaPosicao(int posicao, acaoPrograma acao) {
    Node* novo = new Node(acao);

    if ((posicao <= tamanho) && (posicao >= 0)){
        if (Empty()) {
            insereNoInicio(acao);
        } else if (posicao == 0) {
            insereNoInicio(acao);
        } else if (posicao == tamanho) {
            insereNoFim(acao);
        } else {
            Node* aux = primeiro;
            int posAux = 0;

            while (posAux != (posicao - 1)) {
                aux = aux->proximo;
                posAux++;
            }

            novo->proximo = aux->proximo;
            aux->proximo->anterior = novo;
            aux->proximo = novo;
            novo->anterior = aux;
            tamanho++;
        }
    } else {
        cout << "Posição Inexistente!" << endl;
    }
}

int listadup::procura(string value) {
    if (Empty()) {
        throw runtime_error("Lista Empty!");
    }

    Node* aux = primeiro;
    int posAux = 0;

    while ((aux != NULL) && (aux->acao.nameAcao != value)){
        aux = aux->proximo;
        posAux++;
    }

    if (aux == NULL) {
        cout << "Nao encontrado" << endl;
        return -1;
    }

    cout << posAux << endl;
    return posAux;
}

void listadup::imprime() {
    if (Empty()) {
        cout << "Lista Empty!" << endl;
        return;
    }

    Node* aux = primeiro;
    while (aux != NULL) {
        cout << "(" << aux->acao.identificador << ", "
             << aux->acao.nameAcao << ", "
             << aux->acao.tempoExecucao << ", "
             << aux->acao.tempoConsumido << ")" << endl;
        aux = aux->proximo;
    }

    cout << "IMPRIMINDO REVERSO " << endl;

    aux = ultimo;
    while (aux != NULL) {
        cout << "(" << aux->acao.identificador << ", "
             << aux->acao.nameAcao << ", "
             << aux->acao.tempoExecucao << ", "
             << aux->acao.tempoConsumido << ")" << endl;
        aux = aux->anterior;
    }
}

inline bool listadup::Empty() {
    return (primeiro == NULL);
}

void listadup::removeNoInicio() {
    if (Empty()) {
        cout << "Remoção em lista Empty!" << endl;
        return;
    }
    Node* aux = primeiro;
    primeiro = primeiro->proximo;
    if (primeiro != NULL) {
        primeiro->anterior = NULL;
    } else {
        ultimo = NULL;
    }
    delete aux;
    tamanho--;
}

void listadup::removeNoFim() {
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

int main() {
    listadup minhaLista;
    acaoPrograma info;
    char comand;
    int posicao;
    string nameAcao;

    do {
        try {
            cin >> comand;
            switch (comand) {
                case 'i':
                    cin >> info.identificador >> info.nameAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h':
                    cin >> info.identificador >> info.nameAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoFim(info);
                    break;
                case 'm':
                    cin >> posicao >> info.identificador >> info.nameAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNaPosicao(posicao, info);
                    break;
                case 's':
                    cin >> nameAcao;
                    minhaLista.procura(nameAcao);
                    break;
                case 'r':
                    minhaLista.removeNoInicio();
                    break;
                case 'a':
                    minhaLista.removeNoFim();
                    break;
                case 'p':
                    minhaLista.imprime();
                    break;
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comand != 'f');
    return 0;
}
