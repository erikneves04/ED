#pragma once

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Node.hpp"

/**
 * @file Queue.hpp
 * @brief Classe que representa uma fila (queue) em C++.
 *
 * Esta classe implementa uma estrutura de dados de fila, onde os elementos são adicionados
 * no final da fila e removidos do início da fila (FIFO - First-In, First-Out). A fila permite
 * inserção, remoção e verificação se está vazia.
 *
 * @tparam DataType O tipo de dados dos elementos da fila.
 */
template <class DataType> 
class Queue
{
    protected:
        Node<DataType>* _first;
        Node<DataType>* _last;

        int _size;

    public:
        /**
         * @brief Construtor padrão da classe Queue.
         *
         * Cria uma nova instância de fila vazia.
         */
        Queue()
        {
            _first = nullptr;
            _last = nullptr;
            _size = 0;
        };

        /**
         * @brief Destrutor da classe Queue.
         *
         * Libera a memória alocada para os elementos da fila e destrói a instância da fila.
         */
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

        /**
         * @brief Insere um novo elemento no final da fila.
         *
         * @param data O elemento a ser inserido na fila.
         */
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

        /**
         * @brief Remove e retorna o elemento do início da fila.
         *
         * @return O elemento removido do início da fila.
         * @throw empty_set_exception Se a fila estiver vazia.
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
         * @brief Verifica se a fila está vazia.
         *
         * @return true se a fila estiver vazia, false caso contrário.
         */
        bool Empty()
        {
            return _size == 0;
        }
};

#endif