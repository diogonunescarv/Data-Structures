#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

struct acaoPrograma {
    int identificador;
    string nomeAcao;
    int tempoExecucao;
    int tempoConsumido;
};

class noh {
friend class listadup;
private:
    acaoPrograma acao;
    noh* proximo;
    noh* anterior;
public:
    noh(acaoPrograma d);
};

noh::noh(acaoPrograma d) {
    acao = d;
    proximo = NULL;
    anterior = NULL;
}

class listadup {
private:
    noh* primeiro;
    noh* ultimo;
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
    int procura(string valor);
    void imprime();
    inline bool vazia();
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
    noh* aux = primeiro;
    while (aux != NULL) {
        noh* temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

void listadup::insereNoFim(acaoPrograma acao) {
    noh* novo = new noh(acao);
    if (vazia()) {
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
    noh* novo = new noh(acao);
    if (vazia()) {
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
    noh* novo = new noh(acao);

    if ((posicao <= tamanho) && (posicao >= 0)){
        if (vazia()) {
            insereNoInicio(acao);
        } else if (posicao == 0) {
            insereNoInicio(acao);
        } else if (posicao == tamanho) {
            insereNoFim(acao);
        } else {
            noh* aux = primeiro;
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

int listadup::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }

    noh* aux = primeiro;
    int posAux = 0;

    while ((aux != NULL) && (aux->acao.nomeAcao != valor)){
        aux = aux->proximo;
        posAux++;
    }

    if (aux == NULL) {
        cout << "Nao encontrado" << endl;
        return -1;
    }

    return posAux;
}

void listadup::imprime() {
    if (vazia()) {
        cout << "Lista vazia!" << endl;
        return;
    }

    noh* aux = primeiro;
    while (aux != NULL) {
        cout << "(" << aux->acao.identificador << ", "
             << aux->acao.nomeAcao << ", "
             << aux->acao.tempoExecucao << ", "
             << aux->acao.tempoConsumido << ")" << endl;
        aux = aux->proximo;
    }

    cout << "  IMPRIMINDO REVERSO " << endl;

    aux = ultimo;
    while (aux != NULL) {
        cout << "(" << aux->acao.identificador << ", "
             << aux->acao.nomeAcao << ", "
             << aux->acao.tempoExecucao << ", "
             << aux->acao.tempoConsumido << ")" << endl;
        aux = aux->anterior;
    }
}

inline bool listadup::vazia() {
    return (primeiro == NULL);
}

void listadup::removeNoInicio() {
    if (vazia()) {
        cout << "Remoção em lista vazia!" << endl;
        return;
    }
    noh* aux = primeiro;
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

int main() {
    listadup minhaLista;
    acaoPrograma info;
    char comando;
    int posicao;
    string nomeAcao;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i':
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h':
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoFim(info);
                    break;
                case 'm':
                    cin >> posicao >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNaPosicao(posicao, info);
                    break;
                case 's':
                    cin >> nomeAcao;
                    minhaLista.procura(nomeAcao);
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
    } while (comando != 'f');
    return 0;
}
