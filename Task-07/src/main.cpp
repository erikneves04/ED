#include <iostream>
#include "heap.hpp"

int main()
{
    int n;
    std::cin >> n;

    Heap minHeap(n);

    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        minHeap.Inserir(x);
    }

    while (!minHeap.Vazio())
    {
        int elemento = minHeap.Remover();
        std::cout << elemento;

        if (!minHeap.Vazio())
        {
            std::cout << " ";
        }
    }

    std::cout << std::endl;

    return 0;
}