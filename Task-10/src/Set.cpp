#include "Set.hpp"

StringSet::StringSet(int tamanho) {
    tamanhoOriginal = tamanho;
    tamanhoTabela = 2 * tamanhoOriginal;
    tamanhoConjunto = 0;
    tabela = new ElementoTabela[tamanhoTabela];

    for (int i = 0; i < tamanhoTabela; ++i) {
        tabela[i].vazio = true;
        tabela[i].retirada = false;
    }
}

StringSet::~StringSet() {
    delete[] tabela;
}

int StringSet::Hash(string s) {
    int hash = 0;
    for (char c : s) {
        hash = (hash * 31 + static_cast<int>(c)) % tamanhoTabela;
    }
    return hash;
}

void StringSet::Rehash(int pos) {
    int novoTamanho = tamanhoTabela * 2;
    ElementoTabela *novaTabela = new ElementoTabela[novoTamanho];

    for (int i = 0; i < novoTamanho; ++i) {
        novaTabela[i].vazio = true;
        novaTabela[i].retirada = false;
    }

    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada) {
            int newPos = Hash(tabela[i].dado);

            while (!novaTabela[newPos].vazio) {
                newPos = (newPos + 1) % novoTamanho;
            }

            novaTabela[newPos] = tabela[i];
        }
    }

    delete[] tabela;
    tabela = novaTabela;
    tamanhoTabela = novoTamanho;
}

void StringSet::Resize(size_t novoTamanho) {
    ElementoTabela *novaTabela = new ElementoTabela[novoTamanho];

    for (size_t i = 0; i < novoTamanho; ++i) {
        novaTabela[i].vazio = true;
        novaTabela[i].retirada = false;
    }

    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada) {
            int newPos = Hash(tabela[i].dado);

            while (!novaTabela[newPos].vazio) {
                newPos = (newPos + 1) % novoTamanho;
            }

            novaTabela[newPos] = tabela[i];
        }
    }

    delete[] tabela;
    tabela = novaTabela;
    tamanhoTabela = novoTamanho;
}

void StringSet::Inserir(string s) {
    int pos = Hash(s);

    while (!tabela[pos].vazio && !tabela[pos].retirada) {
        if (tabela[pos].dado == s) {
            return; // Elemento já existe, não insira novamente
        }
        pos = (pos + 1) % tamanhoTabela;
    }

    tabela[pos].dado = s;
    tabela[pos].vazio = false;
    tabela[pos].retirada = false;
    tamanhoConjunto++;

    if (tamanhoConjunto > tamanhoTabela / 2) {
        // Rehash se a tabela estiver mais da metade cheia
        Resize(tamanhoTabela * 2);
    }
}

void StringSet::Remover(string s) {
    int pos = Hash(s);

    while (!tabela[pos].vazio) {
        if (!tabela[pos].retirada && tabela[pos].dado == s) {
            tabela[pos].retirada = true;
            tamanhoConjunto--;

            // Rehash se a tabela estiver menos de um quarto cheia
            if (tamanhoConjunto < tamanhoTabela / 4) {
                Resize(tamanhoTabela / 2);
            }

            return;
        }
        pos = (pos + 1) % tamanhoTabela;
    }
}

bool StringSet::Pertence(string s) {
    int pos = Hash(s);

    while (!tabela[pos].vazio) {
        if (!tabela[pos].retirada && tabela[pos].dado == s) {
            return true;
        }
        pos = (pos + 1) % tamanhoTabela;
    }

    return false;
}

StringSet* StringSet::Intersecao(StringSet* S) {
    StringSet* resultado = new StringSet(tamanhoOriginal);

    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada && S->Pertence(tabela[i].dado)) {
            resultado->Inserir(tabela[i].dado);
        }
    }

    return resultado;
}

StringSet* StringSet::Uniao(StringSet* S) {
    StringSet* resultado = new StringSet(tamanhoOriginal);

    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada) {
            resultado->Inserir(tabela[i].dado);
        }
    }

    for (int i = 0; i < S->tamanhoTabela; ++i) {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada) {
            resultado->Inserir(S->tabela[i].dado);
        }
    }

    return resultado;
}

StringSet* StringSet::DiferencaSimetrica(StringSet* S) {
    StringSet* resultado = new StringSet(tamanhoOriginal);

    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada && !S->Pertence(tabela[i].dado)) {
            resultado->Inserir(tabela[i].dado);
        }
    }

    for (int i = 0; i < S->tamanhoTabela; ++i) {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada && !Pertence(S->tabela[i].dado)) {
            resultado->Inserir(S->tabela[i].dado);
        }
    }

    return resultado;
}

void StringSet::Imprimir() {
    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada) {
            cout << tabela[i].dado << " ";
        }
    }
    cout << endl;
}