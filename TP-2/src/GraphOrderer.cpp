#include "Graph.hpp"
#include "Vertex.hpp"
#include "LinkedList.hpp"
#include "GraphOrderer.hpp"

#include "memlog.h"

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

int QuickSortPartition(LinkedList<Vertex*>* list, int start, int end)
{
    auto pivot = list->Get(start);
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) 
    {
        auto current = list->Get(i);
        if (current->IsLessThanOrEqual(pivot))
            count++;
    }
 
    int pivotIndex = start + count;
    auto toChange_1 = list->GetNode(pivotIndex);
    auto toChange_2 = list->GetNode(start);

    list->InvertNodeContent(toChange_1, toChange_2);
 
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) 
    {
 
        while (list->Get(i)->IsLessThanOrEqual(pivot)) 
        {
            i++;
        }
 
        while (list->Get(j)->IsBiggerThan(pivot)) 
        {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) 
        {
            auto i_index = i++;
            auto j_index = j--;

            toChange_1 = list->GetNode(i_index);
            toChange_2 = list->GetNode(j_index);

            list->InvertNodeContent(toChange_1, toChange_2);
        }
    }
 
    return pivotIndex;
}

void QuickSortRecursive(LinkedList<Vertex*>* list, int start, int end)
{
    if (start >= end)
        return;

    int pivotIndex = QuickSortPartition(list, start, end);

    QuickSortRecursive(list, start, pivotIndex - 1);
    QuickSortRecursive(list, pivotIndex + 1, end);
}

LinkedList<Vertex*>* GraphOrderer::QuickSort(LinkedList<Vertex*>* list)
{
    QuickSortRecursive(list, 0, list->Length() - 1);
    return list;
}

void Merge(LinkedList<Vertex*>* list, int left, int mid, int right)
{
    int subArrayOne = mid - left + 1;
    int subArrayTwo = right - mid;
 
    Vertex** leftArray = new Vertex*[subArrayOne];
    Vertex** rightArray = new Vertex*[subArrayTwo];
 
    for (int i = 0; i < subArrayOne; i++)
    {
        leftArray[i] = list->Get(left + i);
        ESCREVEMEMLOG((long int)(&(leftArray[i])), sizeof(Vertex*), 1);
    }
        
        
    for (int j = 0; j < subArrayTwo; j++)
    {
        rightArray[j] = list->Get(mid + 1 + j);
        ESCREVEMEMLOG((long int)(&(rightArray[j])), sizeof(Vertex*), 2);
    }
        
    int indexOfSubArrayOne = 0;
    int indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;
 
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
    {
        LEMEMLOG((long int)(&(leftArray[indexOfSubArrayOne])),sizeof(Vertex*),1);
        LEMEMLOG((long int)(&(rightArray[indexOfSubArrayTwo])),sizeof(Vertex*),2);

        if (leftArray[indexOfSubArrayOne]->IsLessThanOrEqual(rightArray[indexOfSubArrayTwo])) 
        {
            list->SetNodeContent(list->GetNode(indexOfMergedArray), leftArray[indexOfSubArrayOne]);
            indexOfSubArrayOne++;
        }
        else 
        {
            list->SetNodeContent(list->GetNode(indexOfMergedArray), rightArray[indexOfSubArrayTwo]);
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
 
    while (indexOfSubArrayOne < subArrayOne) 
    {
        LEMEMLOG((long int)(&(leftArray[indexOfSubArrayOne])),sizeof(Vertex*),1);
        list->SetNodeContent(list->GetNode(indexOfMergedArray), leftArray[indexOfSubArrayOne]);
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
 
    while (indexOfSubArrayTwo < subArrayTwo) 
    {
        LEMEMLOG((long int)(&(rightArray[indexOfSubArrayTwo])),sizeof(Vertex*),2);
        list->SetNodeContent(list->GetNode(indexOfMergedArray), rightArray[indexOfSubArrayTwo]);
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

    delete[] leftArray;
    delete[] rightArray;
}

void MergeSortRecursive(LinkedList<Vertex*>* list, int const begin, int const end)
{
    if (begin >= end)
        return;
 
    int mid = begin + (end - begin) / 2;

    MergeSortRecursive(list, begin, mid);
    MergeSortRecursive(list, mid + 1, end);

    Merge(list, begin, mid, end);
}

LinkedList<Vertex*>* GraphOrderer::MergeSort(LinkedList<Vertex*>* list)
{
    MergeSortRecursive(list, 0, list->Length() - 1);
    return list;
}

void Heapify(LinkedList<Vertex*>* list, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
 
    if (l < n && list->Get(l)->IsBiggerThan(list->Get(largest)))
        largest = l;
 
    if (r < n && list->Get(r)->IsBiggerThan(list->Get(largest)))
        largest = r;
 
    if (largest != i) 
    {
        auto firstNode = list->GetNode(i);
        auto secondNode = list->GetNode(largest);

        list->InvertNodeContent(firstNode, secondNode);

        Heapify(list, n, largest);
    }
}

LinkedList<Vertex*>* GraphOrderer::HeapSort(LinkedList<Vertex*>* list)
{
    for (int i = list->Length() / 2 - 1; i >= 0; i--)
        Heapify(list, list->Length(), i);
 
    for (int i = list->Length() - 1; i >= 0; i--) 
    {
        auto firstNode = list->GetNode(0);
        auto secondNode = list->GetNode(i);

        list->InvertNodeContent(firstNode, secondNode);
 
        Heapify(list, i, 0);
    }

    return list;
}

LinkedList<Vertex*>* GraphOrderer::CustomSort(LinkedList<Vertex*>* list)
{
    LinkedList<int>* fixedIndexes = new LinkedList<int>(1);

    int currentIndex = 0;
    while(fixedIndexes->Length() < list->Length())
    {
        if (fixedIndexes->Contains(currentIndex))
        {
            currentIndex++;
            continue;
        }

        auto currentNode = list->GetNode(currentIndex);

        int biggerThan = 0;
        for(int i = 0; i < list->Length(); i++)
        {
            if (currentNode->data->IsBiggerThan(list->Get(i)))
                biggerThan++;
        }

        int destinyIndex = biggerThan;
        if (currentIndex != destinyIndex)
        {
            auto destinyNode = list->GetNode(destinyIndex);
            list->InvertNodeContent(currentNode, destinyNode);
        }
        
        fixedIndexes->Insert(currentIndex);

        currentIndex++;
    }

    delete fixedIndexes;

    return list;
}