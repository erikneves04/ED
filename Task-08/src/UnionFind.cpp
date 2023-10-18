#include "unionFind.hpp"
#include <iostream>
UnionFind::UnionFind(int n) 
{
    this->tamanho = n;
    this->subconjuntos = new Subconjunto[n];
}

UnionFind::~UnionFind() 
{
    delete[] this->subconjuntos;
}

void UnionFind::Make(int x) 
{
    this->subconjuntos[x].representante = x;
    this->subconjuntos[x].rank = 0;
}

int UnionFind::Find(int x) 
{
    return this->subconjuntos[x].representante;
}

void UnionFind::Union(int x, int y) 
{
    for(int i = 0; i < this->tamanho; i++)
    {
        if(this->subconjuntos[i].representante == y)
        {
            this->subconjuntos[i].representante = subconjuntos[x].representante;
            this->subconjuntos[i].rank++;
        }
    }
}