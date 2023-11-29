#include "arvoreAvl.hpp"
#include <iostream>
#include <algorithm>

int ArvoreAvl::GetAltura(Node *atual)
{
  return atual->_altura;
}

void ArvoreAvl::SetAltura(Node *atual)
{
  if (atual == nullptr)
    return;
    
  int altEsq = (atual->esq != nullptr) ? atual->esq->_altura : 0;
  int altDir = (atual->dir != nullptr) ? atual->dir->_altura : 0;
  atual->_altura = 1 + std::max(altEsq, altDir);

  SetAltura(atual->esq);
  SetAltura(atual->dir);
}

int ArvoreAvl::FatorDeEquilibrio(Node *atual)
{
  int altEsq = (atual->esq != nullptr) ? atual->esq->_altura : 0;
  int altDir = (atual->dir != nullptr) ? atual->dir->_altura : 0;
  return (altEsq - altDir);
}

Node *ArvoreAvl::RotacaoDireita(Node *y)
{
  Node *x = y->esq;
  Node *T2 = x->dir;

  x->dir = y;
  y->esq = T2;

  SetAltura(y);
  SetAltura(x);

  return x;
}

Node *ArvoreAvl::RotacaoEsquerda(Node *x)
{
  Node *y = x->dir;
  Node *T2 = y->esq;

  y->esq = x;
  x->dir = T2;

  SetAltura(x);
  SetAltura(y);

  return y;
}

void ArvoreAvl::Insere(std::string palavra, int pagina)
{
  _raiz = InsereRecursivo(_raiz, pagina, palavra);
}

Node *ArvoreAvl::InsereRecursivo(Node *atual, int pagina, std::string palavra)
{
  if (atual == nullptr)
    return new Node(palavra, pagina);

  if (palavra < atual->_palavra)
    atual->esq = InsereRecursivo(atual->esq, pagina, palavra);
  else if (palavra > atual->_palavra)
    atual->dir = InsereRecursivo(atual->dir, pagina, palavra);
  else if (std::find(atual->_paginas.begin(), atual->_paginas.end(), pagina) == atual->_paginas.end())
    atual->_paginas.push_back(pagina);

  SetAltura(atual);

  int fatorEquilibrio = FatorDeEquilibrio(atual);

  if (fatorEquilibrio > 1 && (atual->esq != nullptr) && (palavra < atual->esq->_palavra))
    return RotacaoDireita(atual);

  if (fatorEquilibrio < -1 && (atual->dir != nullptr) && (palavra > atual->dir->_palavra))
    return RotacaoEsquerda(atual);

  if (fatorEquilibrio > 1 && (atual->esq != nullptr) && (palavra > atual->esq->_palavra))
  {
    atual->esq = RotacaoEsquerda(atual->esq);
    return RotacaoDireita(atual);
  }

  if (fatorEquilibrio < -1 && (atual->dir != nullptr) && (palavra < atual->dir->_palavra))
  {
    atual->dir = RotacaoDireita(atual->dir);
    return RotacaoEsquerda(atual);
  }

  return atual;
}

void ArvoreAvl::Imprime()
{
  ImprimeEmOrdemRecursivo(_raiz);
  std::cout << std::endl;
}

void ArvoreAvl::ImprimeEmOrdemRecursivo(Node *atual)
{
  if (atual == nullptr)
    return;

  if (atual->esq != nullptr)
    ImprimeEmOrdemRecursivo(atual->esq);

  std::cout << atual->_palavra << ": ";
  std::list<int> paginasOrdenadas(atual->_paginas.begin(), atual->_paginas.end());
  paginasOrdenadas.sort();

  for (auto it = paginasOrdenadas.begin(); it != paginasOrdenadas.end(); ++it)
  {
    std::cout << *it;

    if (std::next(it) != paginasOrdenadas.end())
      std::cout << " ";
  }
  std::cout << std::endl;

  if (atual->dir != nullptr)
    ImprimeEmOrdemRecursivo(atual->dir);
}