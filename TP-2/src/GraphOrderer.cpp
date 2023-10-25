#include "Graph.hpp"
#include "Vertex.hpp"
#include "LinkedList.hpp"
#include "GraphOrderer.hpp"

GraphOrderer::GraphOrderer(char option)
{
    _option = option;

    switch (option)
    {
        case 'b':
            _ordererMethod = &BubbleSort;
        break;
        case 's':
            _ordererMethod = &SelectionSort;
        break;
        case 'i':
            _ordererMethod = &InsertionSort;
        break;
        case 'q':
            _ordererMethod = &QuickSort;
        break;
        case 'm':
            _ordererMethod = &MergeSort;
        break;
        case 'p':
            _ordererMethod = &HeadSort;
        break;
        case 'y':
            _ordererMethod = &CustomSort;
        break;
        default:
            throw invalid_orderer_option_exception();
        break;
    }
}

LinkedList<Vertex*>* GraphOrderer::Sort(LinkedList<Vertex*>* list)
{
    return _ordererMethod(list);
}

LinkedList<Vertex*>* GraphOrderer::BubbleSort(LinkedList<Vertex*>* list)
{
    bool swapped;

    for (int i = 0; i < list->Length() - 1; i++) 
    {
        swapped = false;
        for (int j = 0; j < list->Length() - i - 1; j++) 
        {
            auto vertex1 = list->GetNode(j);
            auto vertex2 = list->GetNode(j + 1);

            if (vertex1->data > vertex2->data) 
            {
                list->InvertNodeContent(vertex1, vertex2);
                swapped = true;
            }
        }
 
        if (swapped == false)
            break;
    }

    return list;
}

LinkedList<Vertex*>* GraphOrderer::SelectionSort(LinkedList<Vertex*>* list)
{
    return list;
}

LinkedList<Vertex*>* GraphOrderer::InsertionSort(LinkedList<Vertex*>* list)
{
    return list;
}

LinkedList<Vertex*>* GraphOrderer::QuickSort(LinkedList<Vertex*>* list)
{
    return list;
}

LinkedList<Vertex*>* GraphOrderer::MergeSort(LinkedList<Vertex*>* list)
{
    return list;
}

LinkedList<Vertex*>* GraphOrderer::HeadSort(LinkedList<Vertex*>* list)
{
    return list;
}

LinkedList<Vertex*>* GraphOrderer::CustomSort(LinkedList<Vertex*>* list)
{
    return list;
}