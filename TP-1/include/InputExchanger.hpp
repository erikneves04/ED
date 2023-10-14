#pragma once

#ifndef INPUTEXCHANGER_HPP
#define INPUTEXCHANGER_HPP

#include <string>

#include "InputNodule.hpp"
#include "DataStructures/Queue.hpp"
#include "DataStructures/LinkedList.hpp"

/**
 * @file InputExchanger.hpp
 * @brief Classe responsável por gerar combinações de valores para entradas de uma expressão.
 *
 * Esta classe permite gerar todas as combinações possíveis de valores para as variáveis de uma
 * expressão, com base nos índices de variáveis especificados. Isso é útil para avaliar a expressão
 * em diferentes cenários de entrada.
 */
class InputExchanger
{
    private:
        std::string _input;
        LinkedList<int>* _variablesIndex;

        /**
         * @brief Verifica se há uma variável correspondente para um índice.
         *
         * @param index O índice a ser verificado.
         * @return true se houver uma variável correspondente para o índice, false caso contrário.
         */
        bool HasVariableForIndex(int index);

        /**
         * @brief Gera todas as combinações binárias para um número de bits especificado.
         *
         * @param bitsCount O número de bits nas combinações.
         * @return Uma lista de strings que representam todas as combinações binárias possíveis.
         */
        LinkedList<std::string> GenerateBinaryCombinations(int bitsCount);
    public:
        /**
         * @brief Construtor da classe InputExchanger.
         *
         * Cria uma instância de InputExchanger com uma expressão de entrada e uma lista de índices
         * de variáveis para as quais as combinações serão geradas.
         *
         * @param input A expressão de entrada.
         * @param variablesIndex A lista de índices de variáveis.
         */
        InputExchanger(std::string input, LinkedList<int>* variablesIndex);

        /**
         * @brief Gera todas as combinações de valores para as variáveis da expressão.
         *
         * @return Uma fila contendo todas as combinações de valores para as variáveis.
         */
        Queue<LinkedList<InputValue>*>* GetAllInputsCombination();
};

#endif
