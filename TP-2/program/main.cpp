#include <string>
#include <iostream>

#include "Graph.hpp"
#include "LinkedList.hpp"

#define SUCCESS (00)
#define FAILURE (01)

int main(int argc, char const *argv[])
{
    // Leitura do método de ordenação
    char sortMethod;
    std::cin >> sortMethod;
    
    // Construção do grafo com os dados da entrada padrão
    Graph* graph = Graph::BuildFromIoStream();

    bool isGreedy = graph->IsGreedy();
    std::cout << isGreedy;

    if (isGreedy)
    {
        // Impressão ordenada dos vértices
        std::string sorted = "---";
        std::cout << " " << sorted;
    }

    std::cout << std::endl;

    // Limpeza da memória alocada
    delete graph;
    
    // Encerramento do código com sucesso
    return SUCCESS;
}