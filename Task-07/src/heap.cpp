#include "heap.hpp"
#include <iostream>

Heap::Heap(int maxsize) : tamanho(0), maxsize(maxsize)
{
    data = new int[maxsize];
}

Heap::~Heap()
{
    delete[] data;
}

void Heap::Inserir(int x)
{
    if (tamanho >= maxsize)
    {
        return;
    }

    int posicao = tamanho;
    data[posicao] = x;
    tamanho++;

    HeapifyPorCima(posicao);
}

int Heap::Remover()
{
    if (Vazio())
    {
        return -1;
    }

    int raiz = data[0];
    tamanho--;

    if (tamanho > 0)
    {
        data[0] = data[tamanho];
        HeapifyPorBaixo(0);
    }

    return raiz;
}

bool Heap::Vazio()
{
    return tamanho == 0;
}

int Heap::GetAncestral(int posicao)
{
    return (posicao - 1) / 2;
}

int Heap::GetSucessorEsq(int posicao)
{
    return 2 * posicao + 1;
}

int Heap::GetSucessorDir(int posicao)
{
    return 2 * posicao + 2;
}

void Heap::HeapifyPorBaixo(int posicao)
{
    int esquerda = GetSucessorEsq(posicao);
    int direita = GetSucessorDir(posicao);
    int menor = posicao;

    if (esquerda < tamanho && data[esquerda] < data[menor])
    {
        menor = esquerda;
    }

    if (direita < tamanho && data[direita] < data[menor])
    {
        menor = direita;
    }

    if (menor != posicao)
    {
        std::swap(data[posicao], data[menor]);
        HeapifyPorBaixo(menor);
    }
}

void Heap::HeapifyPorCima(int posicao)
{
    while (posicao > 0)
    {
        int ancestral = GetAncestral(posicao);

        if (data[posicao] < data[ancestral])
        {
            std::swap(data[posicao], data[ancestral]);
            posicao = ancestral;
        }
        else
        {
            break;
        }
    }
}