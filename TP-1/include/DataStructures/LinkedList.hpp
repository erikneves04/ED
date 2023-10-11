#pragma once

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "Node.hpp"

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

            for(int i = 0; i<_size; i++)
            {
                auto next = current->next;

                if (current == nullptr)
                    break;

                delete current;
                current = next;
            }
        }

        int Length()
        {
            return _size;
        }

        void Insert(DataType data)
        {
            Node<DataType>* newNode = new Node<DataType>();
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
            if (index < 0 || index >= _size)
                throw empty_set_exception();

            auto current = _head;
            
            for (int i = 1; i < index; i++)
            {
                if (current != nullptr)
                    current = current->next;
            }

            return current->data;
        }

        DataType Last()
        {
            if (Empty())
                throw empty_set_exception();

            return _tail->data;
        }

        bool Empty()
        {
            return _size == 0;
        }
};

#endif