#ifndef ARVORE_AVL_HPP
#define ARVORE_AVL_HPP

#include <string>
#include <list>

struct Node
{
  std::string _palavra;
  std::list<int> _paginas;
  Node *esq;
  Node *dir;
  int _altura;

  Node(std::string palavra, int pagina) 
    : _palavra(palavra), esq(nullptr), dir(nullptr), _altura(1)
  {
    _paginas.push_back(pagina);
  }
};

class ArvoreAvl
{
  private:
    Node *_raiz = nullptr;

    int FatorDeEquilibrio(Node *atual);
    void SetAltura(Node *atual);

    Node *RotacaoDireita(Node *y);
    Node *RotacaoEsquerda(Node *x);

    Node *InsereRecursivo(Node *atual, int pagina, std::string palavra);

    void ImprimeEmOrdemRecursivo(Node *atual);

  public:
    void Insere(std::string palavra, int pagina);

    int GetAltura(Node *atual);
    
    void Imprime();
};

#endif
