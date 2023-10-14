#pragma once

#ifndef STACK_HPP
#define STACK_HPP

#include "Node.hpp"

/**
 * @file Stack.hpp
 * @brief Classe que representa uma pilha (stack) em C++.
 *
 * Esta classe implementa uma estrutura de dados de pilha, onde os elementos são inseridos e
 * removidos do topo da pilha (LIFO - Last-In, First-Out). A pilha permite inserção, remoção,
 * acesso ao elemento no topo e verificação se está vazia.
 *
 * @tparam DataType O tipo de dados dos elementos da pilha.
 */
template <class DataType> 
class Stack
{
    protected:
        Node<DataType>* _first;
        Node<DataType>* _last;

        int _size;

    public:
        /**
         * @brief Construtor padrão da classe Stack.
         *
         * Cria uma nova instância de pilha vazia.
         */
        Stack()
        {
            _first = nullptr;
            _last = nullptr;
            _size = 0;
        };

        /**
         * @brief Destrutor da classe Stack.
         *
         * Libera a memória alocada para os elementos da pilha e destrói a instância da pilha.
         */
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

        /**
         * @brief Insere um novo elemento no topo da pilha.
         *
         * @param data O elemento a ser inserido na pilha.
         */
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

        /**
         * @brief Remove e retorna o elemento no topo da pilha.
         *
         * @return O elemento removido do topo da pilha.
         * @throw empty_set_exception Se a pilha estiver vazia.
         */
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

        /**
         * @brief Retorna o elemento no topo da pilha sem removê-lo.
         *
         * @return O elemento no topo da pilha.
         */
        DataType OnTop()
        {
            return _first->data;
        }

        /**
         * @brief Verifica se a pilha está vazia.
         *
         * @return true se a pilha estiver vazia, false caso contrário.
         */
        bool Empty()
        {
            return _size == 0;
        }
};

#endif