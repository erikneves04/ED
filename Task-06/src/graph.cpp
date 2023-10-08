#include <iostream>

#include "graph.hpp"
#include "LinkedList.hpp"

Grafo::Grafo()
{
    vertices = new LinkedList<LinkedList<int>*>;
}

Grafo::~Grafo()
{
    for(int i = 0; i < vertices->Size(); i++)
        delete vertices->Get(i);

    delete vertices;
}

void Grafo::InsereVertice()
{
    vertices->Insert(new LinkedList<int>);
}

void Grafo::InsereAresta(int v, int w)
{
    if (v >= vertices->Size() || w >= vertices->Size())
        return;

    auto list = vertices->Get(v);

    for(int i = 0; i < list->Size(); i++)
        if(list->Get(i) == w )
            return;

    list->Insert(w);

    list = vertices->Get(w);
    for(int i = 0; i < list->Size(); i++)
        if(list->Get(i) == v )
            return;

    list->Insert(v);    
}

int Grafo::QuantidadeVertices()
{
    return vertices->Size();
}

int Grafo::QuantidadeArestas()
{
    int count = 0;

    for(int i = 0; i < vertices->Size(); i++)
        count += vertices->Get(i)->Size();

    return count / 2;
}

int Grafo::GrauMinimo()
{
    if (vertices->Size() == 0)
        return 0;

    int min = vertices->Get(0)->Size();

    for(int i = 1; i < vertices->Size(); i++)
    {
        auto list = vertices->Get(i);

        if(list->Size() < min)
            min = list->Size();
    }

    return min;
}

int Grafo::GrauMaximo()
{
    if (vertices->Size() == 0)
        return 0;

    int max = vertices->Get(0)->Size();

    for(int i = 1; i < vertices->Size(); i++)
    {
        auto list = vertices->Get(i);

        if(list->Size() > max)
            max = list->Size();
    }

    return max;
}

void Grafo::ImprimeVizinhos(int v)
{
    if (v >= vertices->Size())
        return;

    auto list = vertices->Get(v);

    for(int i = 0; i < list->Size(); i++)
        std::cout << list->Get(i) << " ";
    
    std::cout << std::endl;
}