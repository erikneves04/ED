#pragma once

#ifndef LISTORDERER_HPP
#define LISTORDERER_HPP

#include "Vertex.hpp"
#include "LinkedList.hpp"

/**
 * @brief Exceção lançada quando a opção que indica o método de ordenação escolhido
 * é inválida.
 */
class invalid_orderer_option_exception
{ };

/**
 * @brief Esrutura que represetnta um ordenador de grafos. Ela disponibiliza diversos métodos de
 * ordenação e um, e somente um, deles deve ser selecionado pelo caracter informado no contrutor
 * dessa classe.
 */
class GraphOrderer
{
    private:
        char _option;
        LinkedList<Vertex*>* (*_ordererMethod)(LinkedList<Vertex*>* list);

        /**
         * @brief Responsável por aplicar o método BubbleSort para ordenar uma lista.
         * 
         * @param list A lista que será ordenada.
         * @return Um ponteiro para a lista ordenada.
        */
        static LinkedList<Vertex*>* BubbleSort(LinkedList<Vertex*>* list);

        /**
         * @brief Responsável por aplicar o método SelectionSort para ordenar uma lista.
         * 
         * @param list A lista que será ordenada.
         * @return Um ponteiro para a lista ordenada.
        */
        static LinkedList<Vertex*>* SelectionSort(LinkedList<Vertex*>* list);

        /**
         * @brief Responsável por aplicar o método InsertionSort para ordenar uma lista.
         * 
         * @param list A lista que será ordenada.
         * @return Um ponteiro para a lista ordenada.
        */
        static LinkedList<Vertex*>* InsertionSort(LinkedList<Vertex*>* list);

        /**
         * @brief Responsável por aplicar o método QuickSort para ordenar uma lista.
         * 
         * @param list A lista que será ordenada.
         * @return Um ponteiro para a lista ordenada.
        */
        static LinkedList<Vertex*>* QuickSort(LinkedList<Vertex*>* list);

        /**
         * @brief Responsável por aplicar o método MergeSort para ordenar uma lista.
         * 
         * @param list A lista que será ordenada.
         * @return Um ponteiro para a lista ordenada.
        */
        static LinkedList<Vertex*>* MergeSort(LinkedList<Vertex*>* list);

        /**
         * @brief Responsável por aplicar o método HeapSort para ordenar uma lista.
         * 
         * @param list A lista que será ordenada.
         * @return Um ponteiro para a lista ordenada.
        */
        static LinkedList<Vertex*>* HeapSort(LinkedList<Vertex*>* list);

        /**
         * @brief Responsável por aplicar o método CustomSort(personalziado que pode conter elementos de diversas
         * fontes distintas) para ordenar uma lista.
         * 
         * @param list A lista que será ordenada.
         * @return Um ponteiro para a lista ordenada.
        */
        static LinkedList<Vertex*>* CustomSort(LinkedList<Vertex*>* list);

        /**
         * @brief Define o método de ordenação que será chamado pela função Sort. Ele inicializa um ponteiro
         * para função que irá receber o método escolhido.
         * 
         * @param option Método de ordenação escolhido.
        */
        void SelectSortMethod(char option);

    public:
        /**
         * @brief Construtor responsável por inicializar os dados desse ordenador.
         * 
         * @param option Método de ordenação escolhido.
        */
        GraphOrderer(char option);

        /**
         * @brief Método responsável por aplicar o método escolhido anteriormente a uma lista.
         * 
         * @param list A lista que será ordenada.
         * @return Um ponteiro para a lista ordenada.
        */
        LinkedList<Vertex*>* Sort(LinkedList<Vertex*>* list);
};

#endif