#pragma once

#ifndef NODE_HPP
#define NODE_HPP

/**
 * @brief Exceção lançada quando uma operação é executada em uma lista vazia, ou acesso
 * inválido a algum item.
 *
 * Esta classe representa uma exceção personalizada que é lançada quando uma operação
 * é realizada em uma lista vazia, onde a operação não é válida em tal contexto.
 */
class empty_set_exception
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

#endif
