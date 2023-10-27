#include "Graph.hpp"
#include "Vertex.hpp"
#include "LinkedList.hpp"
#include "GraphOrderer.hpp"

GraphOrderer::GraphOrderer(char option)
{
    _option = option;
    SelectSortMethod(option);
}

void GraphOrderer::SelectSortMethod(char option)
{
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
            _ordererMethod = &HeapSort;
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

            if (vertex1->data->IsBiggerThan(vertex2->data)) 
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
    Node<Vertex*>* min = nullptr;

    for (int i = 0; i < (list->Length() - 1); i++)
    {
        Node<Vertex*>* current = list->GetNode(i);
        min = current;

        for (int j = i; j < list->Length(); j++)
        {
            Node<Vertex*>* current_j = list->GetNode(j);
            if (current_j->data->IsLessThan(min->data))
                min = current_j;
        }

        list->InvertNodeContent(current, min);
    }

    return list;
}

LinkedList<Vertex*>* GraphOrderer::InsertionSort(LinkedList<Vertex*>* list)
{
    Vertex* aux = nullptr;

    for(int i = 0; i < list->Length(); i++)
    {
        aux = list->Get(i);
        
        int j = i - 1;
        while((j >= 0) && aux->IsLessThan(list->GetNode(j)->data))
        {
            list->InvertNodeContent(list->GetNode(j+1), list->GetNode(j));
            j--;
        }
        list->SetNodeContent(list->GetNode(j+1), aux);
    }

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

LinkedList<Vertex*>* GraphOrderer::HeapSort(LinkedList<Vertex*>* list)
{
    return list;
}

LinkedList<Vertex*>* GraphOrderer::CustomSort(LinkedList<Vertex*>* list)
{
    return list;
}