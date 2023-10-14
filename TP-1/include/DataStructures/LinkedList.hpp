#pragma once

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "Node.hpp"

/**
 * @file LinkedList.hpp
 * @brief Classe que representa uma lista encadeada em C++.
 *
 * Esta classe implementa uma lista duplamente encadeada para armazenar dados do tipo DataType.
 * A lista pode crescer dinamicamente e permite inserir, remover, acessar e verificar a presença
 * de elementos. Ela mantém controle do tamanho e armazena referências para o início e o fim
 * da lista.
 *
 * @tparam DataType O tipo de dados dos elementos da lista.
 */
template <class DataType> 
class LinkedList
{
    protected:
        Node<DataType>* _head;
        Node<DataType>* _tail;

        int _size;

        int _lastGetIndex = -1;
        Node<DataType>* _lastGetNode = nullptr;

        DataType LinearGet(int index)
        {
            Node<DataType>* current;

            if (index <= _size / 2)
            {
                current = _head;
                for (int i = 0; i < index; i++)
                {
                    current = current->next;
                }
            }
            else
            {
                current = _tail;
                for (int i = _size - 1; i > index; i--)
                {
                    current = current->previous;
                }
            }

            _lastGetIndex = index;
            _lastGetNode = current;

            return current->data;
        }

    public:

        /**
         * @brief Construtor padrão da classe LinkedList.
         *
         * Cria uma nova instância de LinkedList com a lista vazia.
         */
        LinkedList()
        {
            _head = nullptr;
            _tail = nullptr;
            _size = 0;
        };


        /**
         * @brief Destrutor da classe LinkedList.
         *
         * Libera a memória alocada para os elementos da lista e destrói a instância da lista.
         */
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

        /**
         * @brief Retorna o tamanho atual da lista.
         *
         * @return O número de elementos na lista.
         */
        int Length()
        {
            return _size;
        }

        /**
         * @brief Insere um novo elemento no final da lista.
         *
         * @param data O elemento a ser inserido na lista.
         */
        void Insert(DataType data)
        {
            Node<DataType>* newNode = new Node<DataType>();
            newNode->data = data;

            newNode->next = nullptr;
            newNode->previous = _tail;

            if (_size == 0)
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

        /**
         * @brief Remove a primeira ocorrência de um elemento da lista.
         *
         * @param data O elemento a ser removido da lista, se presente.
         */
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

        /**
         * @brief Obtém o elemento na posição especificada da lista.
         *
         * @param index A posição do elemento desejado na lista.
         * @return O elemento na posição especificada.
         * @throw empty_set_exception Se a lista estiver vazia, ou o indice seja inválido.
         */
        DataType Get(int index)
        {
            if (index < 0 || index >= _size)
                throw empty_set_exception();

            if (_lastGetIndex == -1)
                return LinearGet(index);

            if (_lastGetIndex == index - 1)
            {
                _lastGetIndex = index;
                _lastGetNode = _lastGetNode->next;

                return _lastGetNode->data;
            }

            if (_lastGetIndex == index + 1)
            {
                _lastGetIndex = index;
                _lastGetNode = _lastGetNode->previous;

                return _lastGetNode->data;
            }

            if (_lastGetIndex < index)
            {
                auto current = _lastGetNode;
                for(int i = index; i < index; i++)
                {
                    current = current->next;
                }

                _lastGetIndex = index;
                _lastGetNode = current;

                return current->data;
            }
            
            return LinearGet(index);
        }

        /**
         * @brief Retorna o último elemento da lista.
         *
         * @return O último elemento na lista.
         * @throw empty_set_exception Se a lista estiver vazia.
         */
        DataType Last()
        {
            if (Empty())
                throw empty_set_exception();

            return _tail->data;
        }

        /**
         * @brief Verifica se a lista está vazia.
         *
         * @return true se a lista estiver vazia, false caso contrário.
         */
        bool Empty()
        {
            return _size == 0;
        }

        /**
         * @brief Verifica se a lista contém um determinado elemento.
         *
         * @param data O elemento a ser procurado na lista.
         * @return true se o elemento estiver presente na lista, false caso contrário.
         */
        bool Contains(DataType data)
        {
            auto current = _head;

            while (current != nullptr)
            {
                if (current->data == data)
                    return true;

                current = current->next;
            }

            return false;
        }
};

#endif