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
        LinkedList<Vertex*>* (*_ordererMethod)(LinkedList<Vertex*>* list);

        static LinkedList<Vertex*>* BubbleSort(LinkedList<Vertex*>* list);
        static LinkedList<Vertex*>* SelectionSort(LinkedList<Vertex*>* list);
        static LinkedList<Vertex*>* InsertionSort(LinkedList<Vertex*>* list);
        static LinkedList<Vertex*>* QuickSort(LinkedList<Vertex*>* list);
        static LinkedList<Vertex*>* MergeSort(LinkedList<Vertex*>* list);
        static LinkedList<Vertex*>* HeadSort(LinkedList<Vertex*>* list);
        static LinkedList<Vertex*>* CustomSort(LinkedList<Vertex*>* list);

    public:
        GraphOrderer(char option);
        LinkedList<Vertex*>* Sort(LinkedList<Vertex*>* list);
};

#endif