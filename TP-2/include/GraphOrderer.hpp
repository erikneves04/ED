#pragma once

#ifndef LISTORDERER_HPP
#define LISTORDERER_HPP

#include "Vertex.hpp"
#include "LinkedList.hpp"

class invalid_orderer_option_exception
{ };

class GraphOrderer
{
    private:
        char _option;
        LinkedList<Vertex*>* (GraphOrderer::*_ordererMethod)(LinkedList<Vertex*>* list);

        LinkedList<Vertex*>* BubbleSort(LinkedList<Vertex*>* list);
        LinkedList<Vertex*>* SelectionSort(LinkedList<Vertex*>* list);
        LinkedList<Vertex*>* InsertionSort(LinkedList<Vertex*>* list);
        LinkedList<Vertex*>* QuickSort(LinkedList<Vertex*>* list);
        LinkedList<Vertex*>* MergeSort(LinkedList<Vertex*>* list);
        LinkedList<Vertex*>* HeadSort(LinkedList<Vertex*>* list);
        LinkedList<Vertex*>* CustomSort(LinkedList<Vertex*>* list);

    public:
        GraphOrderer(char option);
        LinkedList<Vertex*>* Sort(LinkedList<Vertex*>* list);
};

#endif