#include <string>
#include <iostream>

#include "Graph.hpp"

#define SUCCESS (00)
#define FAILURE (01)

int main(int argc, char const *argv[])
{
    // Construção do grafo com os dados da entrada padrão
    Graph* graph = Graph::BuildFromIoStream();

    bool isGreedy = graph->IsGreedy();
    std::cout << isGreedy;

    if (isGreedy)
    {
        std::cout << " " << graph->OrderedVertices();
    }

    std::cout << std::endl;

    std::cout << "Print graph:" << std::endl;
    graph->Print();

    // Limpeza da memória alocada
    delete graph;
    
    // Encerramento do código com sucesso
    return SUCCESS;
}