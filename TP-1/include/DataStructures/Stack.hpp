#pragma once

#ifndef STACK_HPP
#define STACK_HPP

#include "Node.hpp"

template <class DataType> 
class Stack
{
    protected:
        Node<DataType>* _first;
        Node<DataType>* _last;

        int _size;

    public:
        Stack()
        {
            _first = nullptr;
            _last = nullptr;
            _size = 0;
        };

        ~Stack()
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

            newNode->next = _first;
            newNode->previous = nullptr;

            if (_first == nullptr)
            {
                _last = newNode;
                _first = newNode;
            }
            else
            {
                _first->previous = newNode;
                _first = newNode;
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
    
        DataType OnTop()
        {
            return _first->data;
        }

        bool Empty()
        {
            return _size == 0;
        }
};

#endif