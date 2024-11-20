#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;

// Um Node guarda um par (chave / value)
class Node {
    friend class lista;
    friend class tabelaHash;
    private:
        string chave;
        char type;
        int value;
        Node* proximo;
        Node(const string& c = "", const char& t = 'a', const int& v=0, Node* prox = NULL):
            chave(c), type(t), value(v), proximo(prox) { }
};

// Uma lista guarda todos os Nos cuja chave foi mapeada na mesma posição.
class lista {
    friend class tabelaHash;
    private:
        Node* primeiro; // primeiro nó da lista
        unsigned short numElementos; // quantidade de valuees na lista
    public:

        lista() {
            numElementos = 0;
            primeiro = NULL;
        } // Construtor

        ~lista() {
            Node* aux = primeiro;
            Node* temp;

            while (aux != NULL){
                temp = aux;
                aux = aux->proximo;
                delete temp;
            }

            numElementos = 0;
            primeiro = NULL;
        } // Destrutor

        unsigned short tamanho() { return numElementos; } // Consulta do Tamanho

        // Adiciona um novo par (chave, value) na lista
        // Insere no início, para não precisar de ponteiro para o fim
        void insere(const string& c, const char& t,const int& v) {
            Node* novo = new Node(c, t, v);
            if(Empty()){
                primeiro = novo;
            } else{
                novo->proximo = primeiro;
                primeiro = novo;
            }
            numElementos++;
        }

        // Remove o Node com dada chave da lista.
        // Se a chave não existe, retorna informação.
        bool remove(const string& c) {

        }

        void removeNoInicio() {
            if (Empty()) {
                //cout << "Remoção em lista Empty!" << endl;
                return;
            }
            Node* aux = primeiro;
            primeiro = primeiro->proximo;
            delete aux;
            numElementos--;
        }

        // verifica se a lista está Empty
        bool Empty() {
            return (primeiro == NULL);
        }

        // Busca um elemento na lista, retorna falso se não encontrado
        // o value buscado é retornado por passagem por referência
        // na variável valueBuscado
        bool busca(const string& c, char& typeBuscado, int& valueBuscado) {
            Node* aux = primeiro;
            for (int i = 0; i<numElementos; i++){
                if(c == aux->chave){
                    typeBuscado = aux->type;
                    valueBuscado = aux->value;
                    return true;
                }
                aux = aux->proximo;
            }
            return false;
        }

        // Verifica se já tem algum Data na lista com
        // uma dada chave
        bool verificaOcorrencia(const string& c) {
            Node* aux = primeiro;
            for (int i = 0; i<numElementos; i++){
                if(c == aux->chave){
                    return true;
                }
                aux = aux->proximo;
            }
            return false;
        }

        // Imprime o conteúdo da lista, para fins de depuração
        void imprime() {
            Node* atual = primeiro;
            while (atual != NULL) {
                    cout << "[" << atual->chave << "/"
                         << atual->value << "]";
                    atual = atual->proximo;
            }
        }
};


class tabelaHash {
    private:
        // vetor de ponteiros para lista
        lista* tabela;
        // quantidade de posições na tabela hash
        unsigned numPosicoes;
        // converte uma chave (string) num endereço da tabela
        // - versão simples
        unsigned funcaoHash(const string& s) {
            return funcaoHash(s, numPosicoes);
        }
        // converte uma chave (string) num endereço da tabela
        // - versão para redimensionamento
        unsigned funcaoHash(const string& s, int cap) {
            unsigned pos = 0;
            for (unsigned int i = 0; i < s.size(); ++i)
                pos = (UMPRIMO * pos + s[i]) % cap;
            return pos;
        }
    public:
        // construtor padrão
        tabelaHash(unsigned cap = 100) {

        }
        ~tabelaHash(){ }
        // Insere um nó com dada chave e value.
        bool insere(const string& c, char& t, const int& v) {}
        // Retorna um value associado a uma dada chave.
        // Se a chave não existe, retorna "NÃO ENCONTRADO!".
        bool value(const string& c, char& typeBuscado, int& valueRetorno) {   }
        // Retira do hash um nó com dada chave.
        bool remove(const string& c) {  }
        // Imprime o conteúdo interno do hash (para fins de depuração)
        void imprime() {
            for (unsigned i = 0; i < numPosicoes; i++) {
                cout << i << ": ";
                tabela[i].imprime();
                cout << endl;
            }
        }
};

int main() {
    int tamanhoTH;
    cin >> tamanhoTH;
    tabelaHash tabela(tamanhoTH);
    char comand;
    string chave;
    char type = 'a';
    int value = -1;
    do {
        try{
            cin >> comand;
            switch (comand) {
                case 'i': // inserir
                    cin >> chave >> type>> value;
                    if (not tabela.insere(chave, type, value))
                        cout << "Erro na inserção: chave já existente!" << endl;
                    break;
                case 'r': // remover
                    cin >> chave;
                    if (not tabela.remove(chave))
                        cout << "Erro na remoção: chave não encontrada!" << endl;
                    break;
                case 'l': // remover
                    cin >> chave;
                    if (not tabela.value(chave,type,value))
                        cout << "Erro na busca: chave não encontrada!" << endl;
                    else
                        cout << "type: " << type << " value: " << value << endl;
                    break;
                case 'p': // mostrar estrutura
                    tabela.imprime();
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
    tabela.imprime();
    cout << endl;
    return 0;
}/*
 * Tabela tabelaHash usando lista explícita
 * by Joukim, 2019
 * Atualizado por Renato, 2023
 */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;

// Um Node guarda um par (chave / value)
class Node {
    friend class lista;
    friend class tabelaHash;
    private:
        string chave;
        char type;
        int value;
        Node* proximo;
        Node(const string& c = "", const char& t = 'a', const int& v=0, Node* prox = NULL):
            chave(c), type(t), value(v), proximo(prox) { }
};

// Uma lista guarda todos os Nos cuja chave foi mapeada na mesma posição.
class lista {
    friend class tabelaHash;
    private:
        Node* primeiro; // primeiro nó da lista
        unsigned short numElementos; // quantidade de valuees na lista
    public:

        lista() {
            numElementos = 0;
            primeiro = NULL;
        } // Construtor

        ~lista() {
            Node* aux = primeiro;
            Node* temp;

            while (aux != NULL){
                temp = aux;
                aux = aux->proximo;
                delete temp;
            }

            numElementos = 0;
            primeiro = NULL;
        } // Destrutor

        unsigned short tamanho() { return numElementos; } // Consulta do Tamanho

        // Adiciona um novo par (chave, value) na lista
        // Insere no início, para não precisar de ponteiro para o fim
        void insere(const string& c, const char& t,const int& v) {
            Node* novo = new Node(c, t, v);
            if(Empty()){
                primeiro = novo;
            } else{
                novo->proximo = primeiro;
                primeiro = novo;
            }
            numElementos++;
        }

        // Remove o Node com dada chave da lista.
        // Se a chave não existe, retorna informação.
        bool remove(const string& c) {

        }

        void removeNoInicio() {
            if (Empty()) {
                //cout << "Remoção em lista Empty!" << endl;
                return;
            }
            Node* aux = primeiro;
            primeiro = primeiro->proximo;
            delete aux;
            numElementos--;
        }

        // verifica se a lista está Empty
        bool Empty() {
            return (primeiro == NULL);
        }

        // Busca um elemento na lista, retorna falso se não encontrado
        // o value buscado é retornado por passagem por referência
        // na variável valueBuscado
        bool busca(const string& c, char& typeBuscado, int& valueBuscado) {
            Node* aux = primeiro;
            for (int i = 0; i<numElementos; i++){
                if(c == aux->chave){
                    typeBuscado = aux->type;
                    valueBuscado = aux->value;
                    return true;
                }
                aux = aux->proximo;
            }
            return false;
        }

        // Verifica se já tem algum Data na lista com
        // uma dada chave
        bool verificaOcorrencia(const string& c) {
            Node* aux = primeiro;
            for (int i = 0; i<numElementos; i++){
                if(c == aux->chave){
                    return true;
                }
                aux = aux->proximo;
            }
            return false;
        }

        // Imprime o conteúdo da lista, para fins de depuração
        void imprime() {
            Node* atual = primeiro;
            while (atual != NULL) {
                    cout << "[" << atual->chave << "/"
                         << atual->value << "]";
                    atual = atual->proximo;
            }
        }
};


class tabelaHash {
    private:
        // vetor de ponteiros para lista
        lista* tabela;
        // quantidade de posições na tabela hash
        unsigned numPosicoes;
        // converte uma chave (string) num endereço da tabela
        // - versão simples
        unsigned funcaoHash(const string& s) {
            return funcaoHash(s, numPosicoes);
        }
        // converte uma chave (string) num endereço da tabela
        // - versão para redimensionamento
        unsigned funcaoHash(const string& s, int cap) {
            unsigned pos = 0;
            for (unsigned int i = 0; i < s.size(); ++i)
                pos = (UMPRIMO * pos + s[i]) % cap;
            return pos;
        }
    public:
        // construtor padrão
        tabelaHash(unsigned cap = 100) {

        }
        ~tabelaHash(){ }
        // Insere um nó com dada chave e value.
        bool insere(const string& c, char& t, const int& v) {}
        // Retorna um value associado a uma dada chave.
        // Se a chave não existe, retorna "NÃO ENCONTRADO!".
        bool value(const string& c, char& typeBuscado, int& valueRetorno) {   }
        // Retira do hash um nó com dada chave.
        bool remove(const string& c) {  }
        // Imprime o conteúdo interno do hash (para fins de depuração)
        void imprime() {
            for (unsigned i = 0; i < numPosicoes; i++) {
                cout << i << ": ";
                tabela[i].imprime();
                cout << endl;
            }
        }
};

int main() {
    int tamanhoTH;
    cin >> tamanhoTH;
    tabelaHash tabela(tamanhoTH);
    char comand;
    string chave;
    char type = 'a';
    int value = -1;
    do {
        try{
            cin >> comand;
            switch (comand) {
                case 'i': // inserir
                    cin >> chave >> type>> value;
                    if (not tabela.insere(chave, type, value))
                        cout << "Erro na inserção: chave já existente!" << endl;
                    break;
                case 'r': // remover
                    cin >> chave;
                    if (not tabela.remove(chave))
                        cout << "Erro na remoção: chave não encontrada!" << endl;
                    break;
                case 'l': // remover
                    cin >> chave;
                    if (not tabela.value(chave,type,value))
                        cout << "Erro na busca: chave não encontrada!" << endl;
                    else
                        cout << "type: " << type << " value: " << value << endl;
                    break;
                case 'p': // mostrar estrutura
                    tabela.imprime();
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
    tabela.imprime();
    cout << endl;
    return 0;
}
