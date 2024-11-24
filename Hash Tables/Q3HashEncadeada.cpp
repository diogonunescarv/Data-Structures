/* 
 * Tabela tabelaHash usando lista explícita
 * by Joukim, 2019
 * Atualizado por Renato, 2023
 */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;

// Um noh guarda um par (chave / valor) 
class noh {
    friend class lista;
    friend class tabelaHash;
    private:
        string chave;
        char tipo;
        int valor;
        noh* proximo;
        noh(const string& c = "", const char& t = 'a', const int& v=0, noh* prox = NULL):
            chave(c), tipo(t), valor(v), proximo(prox) { }
};

// Uma lista guarda todos os Nos cuja chave foi mapeada na mesma posição.
class lista {
    friend class tabelaHash;
    private:
        noh* primeiro; // primeiro nó da lista
        unsigned short numElementos; // quantidade de valores na lista
    public:
        
        lista() {
            numElementos = 0;
            primeiro = NULL;
        } // Construtor

        ~lista() {
            noh* aux = primeiro;
            noh* temp;
            
            while (aux != NULL){
                temp = aux;
                aux = aux->proximo;
                delete temp;
            }
            
            numElementos = 0;
            primeiro = NULL;
        } // Destrutor
        
        unsigned short tamanho() { return numElementos; } // Consulta do Tamanho
        
        // Adiciona um novo par (chave, valor) na lista
        // Insere no início, para não precisar de ponteiro para o fim
        void insere(const string& c, const char& t,const int& v) {
            noh* novo = new noh(c, t, v);
            if(vazia()){
                primeiro = novo;
            } else{
                novo->proximo = primeiro;
                primeiro = novo;
            }
            numElementos++;
        }

        // Remove o noh com dada chave da lista.
        // Se a chave não existe, retorna informação.
        bool remove(const string& c) {
            if (vazia()) {
                return false; // Lista vazia, não há nada para remover
            }

            noh* atual = primeiro;
            noh* anterior = NULL;

            // Percorrer a lista para encontrar o nó com a chave correspondente
            while (atual != NULL && atual->chave != c) {
                anterior = atual;
                atual = atual->proximo;
            }

            // Verificar se a chave foi encontrada
            if (atual == NULL) {
                return false; // Chave não encontrada
            }

            // Caso especial: o nó a ser removido é o primeiro
            if (anterior == NULL) {
                primeiro = atual->proximo; // Atualizar o início da lista
            } else {
                anterior->proximo = atual->proximo; // Remover o nó no meio ou fim
            }

            delete atual; // Liberar a memória
            numElementos--; // Atualizar o número de elementos

            return true; // Remoção bem-sucedida
        }
        
        // verifica se a lista está vazia
        bool vazia() {
            return (primeiro == NULL);
        }
        
        // Busca um elemento na lista, retorna falso se não encontrado
        // o valor buscado é retornado por passagem por referência
        // na variável valorBuscado
        bool busca(const string& c, char& tipoBuscado, int& valorBuscado) {
            if (vazia()) {
                return false; // Lista vazia, não há nada para remover
            }
            noh* aux = primeiro;
            for (int i = 0; i<numElementos; i++){
                if(c == aux->chave){
                    tipoBuscado = aux->tipo;
                    valorBuscado = aux->valor;
                    return true;
                }
                aux = aux->proximo;
            }

            return false; 
        }
        
        // Verifica se já tem algum dado na lista com 
        // uma dada chave
        bool verificaOcorrencia(const string& c) {
            noh* aux = primeiro;
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
            noh* atual = primeiro;
            while (atual != NULL) {
                    cout << "[" << atual->chave << "/"
                         << atual->valor << "]";
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
            numPosicoes = cap;
            tabela = new lista[numPosicoes];
        }

        ~tabelaHash(){
            delete[] tabela;
        }
        
        // Insere um nó com dada chave e valor.
        bool insere(const string& c, char& t, const int& v) {
            unsigned pos = funcaoHash(c);

            tabela[pos].insere(c, t, v);

            cout << "chave '" + c + "' inserida na posicao " << pos << endl;  

            return true;
        }

        // Retorna um valor associado a uma dada chave.
        // Se a chave não existe, retorna "NÃO ENCONTRADO!".
        bool valor(const string& c, char& tipoBuscado, int& valorRetorno) {
            unsigned pos = funcaoHash(c);

            /**if (tabela[pos].vazia()){
                cout << "Erro: hash vazia!" << endl;
                return false;
            } else **/ 
            if (!tabela[pos].busca(c, tipoBuscado, valorRetorno)){
                cout << "Elemento inexistente!" << endl;
                return false;
            } else {
                return true;
            }
        }

        // Retira do hash um nó com dada chave.
        bool remove(const string& c) { 
            unsigned pos = funcaoHash(c);
            /**if (tabela[pos].vazia()){
                cout << "Erro: hash vazia!" << endl;
                return false;
            } else **/ 
            if (!tabela[pos].remove(c)){
                cout << "Elemento inexistente!" << endl;
                return false;
            } else {
                return true;
            }
        }

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
    char comando;
    string chave;
    char tipo = 'a';
    int valor = -1;    
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> chave >> tipo>> valor;
                    tabela.insere(chave, tipo, valor);
                    break;
                case 'r': // remover
                    cin >> chave;
                    tabela.remove(chave);
                    break;
                case 'l': // remover
                    cin >> chave;
                    if (tabela.valor(chave,tipo,valor)){
                        cout << "Tipo: " << tipo << " Valor: " << valor << endl;
                    }
                    break;
                case 'p': // mostrar estrutura
                    tabela.imprime();
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
    tabela.imprime();
    cout << endl;
    return 0;
}
