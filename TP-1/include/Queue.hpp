#pragma once

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Node.hpp"

template <class DataType> 
class Queue
{
    protected:
        Node<DataType>* _first;
        Node<DataType>* _last;

        int _size;

    public:
        Queue()
        {
            _first = nullptr;
            _last = nullptr;
            _size = 0;
        };

        ~Queue()
        {
            auto current = _first;

            while (current != nullptr)
            {
                auto next = current->next;
                delete current;
                current = next;
            }
        }

        void Insert(DataType data)
        {
            auto newNode = new Node<DataType>;
            newNode->data = data;

            newNode->next = nullptr;
            newNode->previous = _last;

            if (_first == nullptr)
            {
                _first = newNode;
                _last = newNode;
            }
            else
            {
                _last->next = newNode;
                _last = newNode;
            }

            _size++;
        }

        DataType Remove()
        {
            if (_size == 0)
                throw empty_set_exception();

            auto current = _first;
            DataType data = current->data;

            _first = _first->next;
            if (_first != nullptr)
                _first->previous = nullptr;

            delete current;

            _size--;

            return data;
        }

        bool Empty()
        {
            return _size == 0;
        }
};

#endif