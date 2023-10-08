#pragma once

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <class DataType> 
struct Node
{
    DataType data;
    Node* next;
    Node* previous;
};

template <class DataType> 
class LinkedList
{
    protected:
        Node<DataType>* _head;
        Node<DataType>* _tail;

        int _size;

    public:
        LinkedList()
        {
            _head = nullptr;
            _tail = nullptr;
            _size = 0;
        };

        ~LinkedList()
        {
            auto current = _head;

            while (current != nullptr)
            {
                auto next = current->next;
                delete current;
                current = next;
            }
        }

        int Size()
        {
            return _size;
        }

        void Insert(DataType data)
        {
            auto newNode = new Node<DataType>;
            newNode->data = data;

            newNode->next = nullptr;
            newNode->previous = _tail;

            if (_head == nullptr)
            {
                _head = newNode;
                _tail = newNode;
            }
            else
            {
                _tail->next = newNode;
                _tail = newNode;
            }

            _size++;
        }

        void Remove(DataType data)
        {
            auto current = _head;

            while (current != nullptr)
            {
                if (current->data == data)
                {
                    if (current->previous == nullptr)
                    {
                        _head = current->next;
                    }
                    else
                    {
                        current->previous->next = current->next;

                        if (current->next != nullptr)
                            current->next->previous = current->previous;

                        if (current->next == nullptr)
                            _tail = current->previous;
                    }

                    delete current;
                    _size--;
                    return;
                }

                current = current->next;
            }
        }

        DataType Get(int index)
        {
            auto current = _head;

            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }

            return current->data;
        }

        bool Empty()
        {
            return _size == 0;
        }
};

using ListaAdjacencia = LinkedList<LinkedList<int>*>*;

#endif