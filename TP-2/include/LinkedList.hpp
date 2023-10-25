#pragma once

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

/**
 * @brief Exceção lançada quando uma operação é executada em uma lista vazia, ou acesso
 * inválido a algum item.
 *
 * Esta classe representa uma exceção personalizada que é lançada quando uma operação
 * é realizada em uma lista vazia, onde a operação não é válida em tal contexto.
 */
class element_not_found_exception
{   };

/**
 * @brief Estrutura que representa um nó em uma estrutura de dados(compartilhado com lista, fila e pilha).
 *
 * Esta estrutura é utilizada para criar nós em uma estrutura. Cada nó contém um elemento
 * de dados do tipo DataType, uma referência para o próximo nó e uma referência para o nó anterior
 * na lista.
 *
 * @tparam DataType O tipo de dados a ser armazenado em um nó.
 */
template <class DataType> 
struct Node
{
    DataType data;
    Node* next;
    Node* previous;
};

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
    friend class GraphOrderer;

    protected:
        Node<DataType>* _head;
        Node<DataType>* _tail;

        int _size;

        int _lastGetIndex = -1;
        Node<DataType>* _lastGetNode = nullptr;

        /**
         * @brief Obtém o elemento na posição especificada da lista, com uma busca linar
         * que pode ser iniciada tanto do primeiro elemento quanto do último, a depender
         * do caminho mais eficiente.
         *
         * @param index A posição do elemento desejado na lista.
         * @return O nódulo do elemento na posição especificada.
         */
        Node<DataType>* LinearGet(int index)
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

            return current;
        }

        /**
         * @brief Obtém o elemento na posição especificada da lista.
         * 
         * @param index A posição do elemento desejado na lista.
         * @return O nódulo do elemento na posição especificada.
        */
        Node<DataType>* GetNode(int index)
        {
            if (index < 0 || index >= _size)
                throw element_not_found_exception();

            if (_lastGetIndex == -1)
                return LinearGet(index);

            if (_lastGetIndex == index - 1)
            {
                _lastGetIndex = index;
                _lastGetNode = _lastGetNode->next;

                return _lastGetNode;
            }

            if (_lastGetIndex == index + 1)
            {
                _lastGetIndex = index;
                _lastGetNode = _lastGetNode->previous;

                return _lastGetNode;
            }
            
            return LinearGet(index);
        }

        /**
         * @brief Inverte o conteúdo de dois nódulos.
         *
         * @param first O primeiro nó.
         * @param second O segundo nó.
         */
        void InvertNodeContent(Node<DataType>* first, Node<DataType>* second)
        {
            if (first == nullptr || second == nullptr)
                return;

            DataType temp = first->data;

            first->data = second->data;
            second->data = temp;
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
         * @brief Obtém o elemento na posição especificada da lista. Esse método faz um
         * gerênciamento interno visando melhorar a performance de acesso aos elementos,
         * avaliando de que ponto da lista é mais viável começar a busca e armazenando
         * informações em um formato similar ao cache para permitir que iterações tenham
         * complexidade O(1).
         *
         * @param index A posição do elemento desejado na lista.
         * @return O elemento na posição especificada.
         * @throw element_not_found_exception Se a lista estiver vazia, ou o indice seja inválido.
         */
        DataType Get(int index)
        {
            return GetNode(index)->data;
        }

        /**
         * @brief Retorna o último elemento da lista.
         *
         * @return O último elemento na lista.
         * @throw element_not_found_exception Se a lista estiver vazia.
         */
        DataType Last()
        {
            if (Empty())
                throw element_not_found_exception();

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