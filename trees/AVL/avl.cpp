#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <queue>

typedef std::string TChave; // chave da árvore
typedef float TValor; // valor da árvore

// === Declarações das classes ===================================================
class NohAVL; // declaração avançada

class AVL {
    public:
        AVL();
        ~AVL();
        TValor& Valor(TChave chave);
        void EscreverEmOrdem();
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(TChave chave, const TValor& valor);
        bool ConferirLigacoes();
        void Remover(TChave chave);
    private:
        NohAVL* mPtRaiz;
};

class NohAVL {
    friend std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh);
    friend void AVL::EscreverNivelANivel(std::ostream& saida);
    public:
        NohAVL (TChave c, const TValor& v);
        ~NohAVL();
        void DesalocarFilhosRecursivo();
        NohAVL* InserirRecursivo(NohAVL* ptNoh);
        NohAVL* MenorRecursivo();
        NohAVL* RemoverRecursivo(TChave chave);
        TValor& Valor(TChave chave);
    private:
        NohAVL* ArrumarBalanceamento();
        void AtualizarAltura();
        int FatorBalanceamento();
        int InformarAltura(NohAVL* umNoh);
        NohAVL* Remover();
        NohAVL* RotacionarEsquerda();
        NohAVL* RotacionarDireita();
        void SubstitutirPor(NohAVL* ptNoh);
        void Transplantar(NohAVL* ptFilho);
        void TrocarFilho(NohAVL* ptAntigo, NohAVL* ptNovo);
        TChave mChave;
        TValor mValor;
        NohAVL* mPtEsq;
        NohAVL* mPtDir;
        NohAVL* mPtPai;
        unsigned int mAltura; // folhas têm altura 1
};

// === Implementações das classes ================================================

using namespace std;

// === Classe NohAVL =============================================================

NohAVL::NohAVL(TChave c, const TValor& v)
    : mChave(c), mValor(v), mPtEsq(NULL), mPtDir(NULL), mPtPai(NULL), mAltura(1) {
}

NohAVL::~NohAVL() {
}

// Faz as rotações e ajustes necessários inclusive do nó pai. Atualiza a altura.
// Retorna o ponteiro para o nó que ficar na posição dele após os ajustes.
NohAVL* NohAVL::ArrumarBalanceamento() {
    AtualizarAltura();
    int fb = FatorBalanceamento();

    // Desbalanceamento à esquerda
    if (fb > 1) {
        if (mPtEsq->FatorBalanceamento() < 0) { // Rotação dupla à direita
            mPtEsq = mPtEsq->RotacionarEsquerda();
        }
        return RotacionarDireita();
    }
    // Desbalanceamento à direita
    else if (fb < -1) {
        if (mPtDir->FatorBalanceamento() > 0) { // Rotação dupla à esquerda
            mPtDir = mPtDir->RotacionarDireita();
        }
        return RotacionarEsquerda();
    }

    return this; // Se estiver balanceado, retorna o nó atual
}

// Calcula e atualiza a altura de um nó.
void NohAVL::AtualizarAltura() {
    unsigned int alturaEsq = (mPtEsq ? mPtEsq->mAltura : 0);
    unsigned int alturaDir = (mPtDir ? mPtDir->mAltura : 0);
    mAltura = 1 + max(alturaEsq, alturaDir);
}

// Desaloca todos os descendentes.
void NohAVL::DesalocarFilhosRecursivo() {
    if (mPtEsq) {
        mPtEsq->DesalocarFilhosRecursivo();
        delete mPtEsq;
        mPtEsq = nullptr;
    }
    if (mPtDir) {
        mPtDir->DesalocarFilhosRecursivo();
        delete mPtDir;
        mPtDir = nullptr;
    }
}

// Calcula e retorna o fator de balanceamento do nó.
int NohAVL::FatorBalanceamento() {
    int alturaEsq = (mPtEsq ? mPtEsq->mAltura : 0);
    int alturaDir = (mPtDir ? mPtDir->mAltura : 0);
    return alturaEsq - alturaDir;
}

// Insere um nó numa subárvore. Retorna o ponteiro para o nó que ficou no lugar do que recebeu
// a mensagem.
NohAVL* NohAVL::InserirRecursivo(NohAVL* ptNoh) {
    if (ptNoh->mChave < mChave) {
        if (mPtEsq == nullptr) {
            mPtEsq = ptNoh;
            ptNoh->mPtPai = this;
        } else {
            mPtEsq = mPtEsq->InserirRecursivo(ptNoh);
        }
    } else {
        if (mPtDir == nullptr) {
            mPtDir = ptNoh;
            ptNoh->mPtPai = this;
        } else {
            mPtDir = mPtDir->InserirRecursivo(ptNoh);
        }
    }
    return ArrumarBalanceamento();
}

// Busca o nó que tem a menor chave. Retorna o ponteiro para ele.
NohAVL* NohAVL::MenorRecursivo() {
    return (mPtEsq ? mPtEsq->MenorRecursivo() : this);
}

// Remove o nó. Retorna o ponteiro para o nó que ficou no lugar dele.
// Confira com RemoverRecursivo(TChave).
NohAVL* NohAVL::Remover() {
    if (mPtEsq == nullptr && mPtDir == nullptr) { // Caso 1: Nó folha
        delete this; // Libera o nó atual
        return nullptr; // Retorna nullptr para o pai
    } 
    
    else if (mPtEsq == nullptr) { // Caso 2: Apenas filho direito
        NohAVL* filhoDir = mPtDir;
        filhoDir->mPtPai = mPtPai; // Atualiza o pai do filho direito
        delete this; // Libera o nó atual
        return filhoDir; // Retorna o filho direito
    } 
    
    else if (mPtDir == nullptr) { // Caso 2: Apenas filho esquerdo
        NohAVL* filhoEsq = mPtEsq;
        filhoEsq->mPtPai = mPtPai; // Atualiza o pai do filho esquerdo
        delete this; // Libera o nó atual
        return filhoEsq; // Retorna o filho esquerdo
    } 
    
    else { // Caso 3: Nó com dois filhos
        // Encontra o sucessor: menor valor na subárvore direita
        NohAVL* sucessor = mPtDir;
        while (sucessor->mPtEsq != nullptr) {
            sucessor = sucessor->mPtEsq;
        }

        // Copia os dados do sucessor para o nó atual
        this->mChave = sucessor->mChave;
        this->mValor = sucessor->mValor;

        // Remove o sucessor da subárvore direita
        mPtDir = mPtDir->RemoverRecursivo(sucessor->mChave);

        // Ajusta o ponteiro pai do filho direito
        if (mPtDir) mPtDir->mPtPai = this;
    }

    // Atualiza a altura do nó atual
    AtualizarAltura();

    // Verifica e ajusta o balanceamento
    return ArrumarBalanceamento();
}


// Busca recursivamente um nó com dada chave e o remove. Retorna o ponteiro para o nó que ficou
// no lugar do nó que recebeu a mensagem.
// Confira com Remover().
NohAVL* NohAVL::RemoverRecursivo(TChave chave) {
    if (chave < mChave) {
        if (mPtEsq) mPtEsq = mPtEsq->RemoverRecursivo(chave);
    } else if (chave > mChave) {
        if (mPtDir) mPtDir = mPtDir->RemoverRecursivo(chave);
    } else {
        if (!mPtEsq && !mPtDir) {
            delete this;
            return nullptr;
        } else if (!mPtEsq || !mPtDir) {
            NohAVL* filho = (mPtEsq ? mPtEsq : mPtDir);
            filho->mPtPai = mPtPai;
            delete this;
            return filho;
        } else {
            NohAVL* sucessor = mPtDir->MenorRecursivo();
            mChave = sucessor->mChave;
            mValor = sucessor->mValor;
            mPtDir = mPtDir->RemoverRecursivo(sucessor->mChave);
        }
    }
    return ArrumarBalanceamento();
}

// Rotaciona à direita a subárvore. Retorna a nova raiz da subárvore.
NohAVL* NohAVL::RotacionarDireita() {
    NohAVL* novaRaiz = mPtEsq;
    mPtEsq = novaRaiz->mPtDir;
    if (novaRaiz->mPtDir != nullptr) {
        novaRaiz->mPtDir->mPtPai = this;
    }
    novaRaiz->mPtDir = this;

    novaRaiz->mPtPai = mPtPai;
    mPtPai = novaRaiz;

    AtualizarAltura();
    novaRaiz->AtualizarAltura();

    return novaRaiz; // Nova raiz da subárvore
}


// Rotaciona à esquerda a subárvore. Retorna a nova raiz da subárvore.
NohAVL* NohAVL::RotacionarEsquerda() {
    // Nó atual: "this" (A)
    // Nó direito: mPtDir (B)
    NohAVL* novoRaiz = mPtDir; // B será a nova raiz da subárvore
    mPtDir = novoRaiz->mPtEsq; // A recebe a subárvore esquerda de B
    if (mPtDir) {
        mPtDir->mPtPai = this; // Atualiza o pai da nova subárvore direita de A
    }

    novoRaiz->mPtEsq = this; // B passa a apontar para A como filho esquerdo
    novoRaiz->mPtPai = mPtPai; // O pai de B se torna o pai original de A
    mPtPai = novoRaiz; // Atualiza o pai de A

    // Atualiza as alturas dos nós
    AtualizarAltura();       // Atualiza altura de A
    novoRaiz->AtualizarAltura(); // Atualiza altura de B

    return novoRaiz; // Retorna a nova raiz da subárvore
}


// Atualiza todas as ligações, para que ptNoh, fique no lugar deste nó.
// Usado na remoção com dois filhos.
void NohAVL::SubstitutirPor(NohAVL* ptNoh) {
    if (mPtPai) {
        if (mPtPai->mPtEsq == this) {
            mPtPai->mPtEsq = ptNoh;
        } else {
            mPtPai->mPtDir = ptNoh;
        }
    }
    if (ptNoh) {
        ptNoh->mPtPai = mPtPai;
    }
}


// Muda as ligações do pai e do filho para desligar o nó atual.
// Usado para remoção na situação em que não existem os dois filhos.
void NohAVL::Transplantar(NohAVL* ptFilho) {
    if (mPtPai) {
        if (mPtPai->mPtEsq == this) {
            mPtPai->mPtEsq = ptFilho;
        } else {
            mPtPai->mPtDir = ptFilho;
        }
    }
    if (ptFilho) {
        ptFilho->mPtPai = mPtPai;
    }
}


// Substitui um dos filhos por um novo nó.
void NohAVL::TrocarFilho(NohAVL* ptAntigo, NohAVL* ptNovo) {
    if (mPtEsq == ptAntigo) {
        mPtEsq = ptNovo;
    } else if (mPtDir == ptAntigo) {
        mPtDir = ptNovo;
    }
    if (ptNovo) {
        ptNovo->mPtPai = this;
    }
}


// Busca recursivamente uma dada chave e retorna o valor associado a ela.
// Levanta exceção se não encontrar a chave.
TValor& NohAVL::Valor(TChave chave) {
    if (chave == mChave) {
        return mValor;
    } else if (chave < mChave) {
        if (mPtEsq) return mPtEsq->Valor(chave);
    } else {
        if (mPtDir) return mPtDir->Valor(chave);
    }
    throw std::runtime_error("Chave não encontrada.");
}

// Escreve o conteúdo de um nó no formato [altura:chave/valor].
// Escreve "[]" se o ponteiro recebido for NULL.
ostream& operator<<(ostream& saida, NohAVL* ptNoh) {
    if (ptNoh == NULL)
        saida << "[]";
    else
        saida << '[' << ptNoh->mAltura << ':' << ptNoh->mChave << '/' << ptNoh->mValor << ']';
    return saida;
}

// === Classe AVL =================================================================================
AVL::AVL() : mPtRaiz(NULL) {
}

AVL::~AVL() {
    if (mPtRaiz != NULL) {
        mPtRaiz->DesalocarFilhosRecursivo();
        delete mPtRaiz;
    }
}

// Retorna o valor associado a uma dada chave.
TValor& AVL::Valor(TChave chave) {
    if (mPtRaiz == NULL)
        throw runtime_error("Tentativa de buscar valor numa arvore vazia.");
    return mPtRaiz->Valor(chave);
}

// Escreve o conteúdo da árvore nível a nível, na saída de dados informada.
// Usado para conferir se a estrutra da árvore está correta.
void AVL::EscreverNivelANivel(ostream& saida) {
    queue<NohAVL*> filhos;
    NohAVL* fimDeNivel = new NohAVL(TChave(), TValor()); // nó especial para marcar fim de um nível
    filhos.push(mPtRaiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        NohAVL* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << ptNoh << ' ';
            if (ptNoh != NULL) {
                filhos.push(ptNoh->mPtEsq);
                filhos.push(ptNoh->mPtDir);
            }
        }
    }
    delete fimDeNivel;
}

// Insere um par chave/valor na árvore.
void AVL::Inserir(TChave chave, const TValor& valor) {
    NohAVL* novo = new NohAVL(chave, valor);
    if (mPtRaiz == nullptr) {
        mPtRaiz = novo;
    } else {
        mPtRaiz = mPtRaiz->InserirRecursivo(novo);
    }
}

// Remove da árvore o nó que tiver uma dada chave.
void AVL::Remover(TChave chave) {
    if (mPtRaiz != nullptr) {
        mPtRaiz = mPtRaiz->RemoverRecursivo(chave);
    }
}

// === Programa ===================================================================================
int main() {
    AVL minhaArvore;
    char opcao;
    TChave chave;
    TValor valor;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave >> valor;
                minhaArvore.Inserir(chave, valor);
                break;
            case 'r': // Remover
                try {
                    cin >> chave;
                    minhaArvore.Remover(chave);
                }
                catch (runtime_error& erro) {
                    cerr << erro.what() << endl;
                }
                break;
            case 'b': // Buscar
                try {
                    cin >> chave;
                    valor = minhaArvore.Valor(chave);
                    cout << valor << endl;
                }
                catch (runtime_error& erro) {
                    cerr << erro.what() << endl;
                }
                break;
            case 'e': // Escrever nós nível a nível
                minhaArvore.EscreverNivelANivel(cout);
                break;
            case 'f': // Finalizar o programa
                // vai verificar depois
                break;
            default:
                cerr << "Opção inválida\n";
        }
    } while (opcao != 'f');
    return 0;
}
