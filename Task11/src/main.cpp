#include <iostream>
#include <string>

#include "arvoreAvl.hpp"

#define SUCCESS 0
#define MAX_TAM 100

int main(int argc, char const *argv[]) 
{
  char word[MAX_TAM];
  int page;

  ArvoreAvl tree;

  while (std::cin >> word >> page)
    tree.Insere(word, page);

  tree.Imprime();

  return SUCCESS;
}