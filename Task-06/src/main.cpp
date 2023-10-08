#include <iostream>
#include "graph.hpp"

#define SUCCESS (00)
#define FAILURE (01)

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        std::cout << "Usage: -function < input.txt" << std::endl;
        return FAILURE;
    }

    int numVertices, numArestas;

    std::cin >> numVertices;

    Grafo grafo;

    for(int i = 0; i < numVertices; i++)
        grafo.InsereVertice();
        
    for(int i = 0; i < numVertices; i++)
    {
        std::cin >> numArestas;

        for(int j = 0; j < numArestas; j++)
        {
            int v;
            std::cin >> v;
            grafo.InsereAresta(i, v);
        }
    }

    std::string operation = argv[1];

    if (operation == "-d")
    {
        std::cout << grafo.QuantidadeVertices() << std::endl;
        std::cout << grafo.QuantidadeArestas() << std::endl;
        std::cout << grafo.GrauMinimo() << std::endl;
        std::cout << grafo.GrauMaximo() << std::endl;
    }
    else if (operation == "-n")
    {
        for(int i = 0; i < numVertices; i++)
        {
            grafo.ImprimeVizinhos(i);
        }
    }
    else if (operation == "-k")
    {
        auto expected = (grafo.QuantidadeVertices() - 1);

        if (grafo.GrauMaximo() != expected || grafo.GrauMinimo() != expected)
            std::cout << "0" << std::endl;
        else
            std::cout << "1" << std::endl;
    }
    else
    {
        std::cout << "Invalid operation" << std::endl;
        return FAILURE;
    }

    return SUCCESS;
}