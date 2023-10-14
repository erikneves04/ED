#pragma once

#ifndef EXPRESSIONORDERER_HPP
#define EXPRESSIONORDERER_HPP

#include <string>

#include "InputNodule.hpp"
#include "OperationNodule.hpp"

#include "DataStructures/LinkedList.hpp"
#include "DataStructures/Stack.hpp"

#define RESULT_NODULE_NAME ("result")

/**
 * @file ExpressionOrderer.hpp
 * @brief Classe responsável por ordenar e avaliar uma lista de nódulos de expressão.
 *
 * Esta classe é usada para ordenar e avaliar uma lista de nódulos de expressão booleana. Ela mantém
 * duas pilhas, uma para operações e outra para valores de entrada, a fim de calcular a expressão de
 * acordo com as regras de precedência e respeitando a ordem dos parênteses.
 */
class ExpressionOrderer
{
    private:
        Stack<InputNodule*>* _inputStack;
        Stack<Nodule*>* _operationStack;

        /**
         * @brief Executa as operações pendentes na pilha de operações.
         */
        void ExecutePendingOperations();

        /**
         * @brief Executa operações de acordo com a precedência especificada.
         *
         * @param operation O nódulo de operação que define a precedência.
         */
        void ExecutePrecedenceOperations(OperationNodule* operation);

        /**
         * @brief Executa todas as operações até que seja encontrado um 
         * parêntestes de abertura.
         */
        void ExecuteAllParenthesesNodules();

        /**
         * @brief Executa um nódulo de operação.
         *
         * @param operation O nódulo de operação a ser executado.
         */
        void ExecuteOperationNodule(OperationNodule* operation);

        /**
         * @brief Remove e retorna o último valor de entrada da pilha de valores de entrada.
         *
         * @return true se o valor de entrada foi removido com sucesso, false caso contrário.
         */
        bool TakeLastInputValue();
    public:
        /**
         * @brief Construtor da classe ExpressionOrderer.
         *
         * Cria uma instância de ExpressionOrderer com pilhas vazias para operações e valores de entrada.
         */
        ExpressionOrderer();

        /**
         * @brief Destrutor da classe ExpressionOrderer.
         *
         * Libera a memória alocada durante a execução da classe ExpressionOrderer.
         */
        ~ExpressionOrderer();

        /**
         * @brief Executa a ordenação e avaliação de uma lista de nódulos de expressão.
         *
         * @param nodules Uma lista de nódulos de expressão a ser ordenada e avaliada.
         * @return true se a ordenação e avaliação forem bem-sucedidas, false caso contrário.
         */
        bool Perform(LinkedList<Nodule*>* nodules);
};

#endif