#pragma once

#ifndef SATISFACTIONEVALUATOR_HPP
#define SATISFACTIONEVALUATOR_HPP

#include <string>

#include "InputNodule.hpp"
#include "DataStructures/LinkedList.hpp"

#define EXISTS ("e")
#define FOR_ALL ("a")

#define SOLUTION_IRRELEVANT_OUTPUT ('a')

/**
 * @file SatisfactionEvaluator.hpp
 * @brief Classe para avaliação de satisfação de uma expressão com entradas variáveis.
 *
 * Esta classe é usada para avaliar se uma expressão lógica é satisfeita para diferentes combinações
 * de valores de entrada. Ela permite determinar se há soluções ou falhas na satisfação da expressão
 * e também fornece métodos para obter as soluções encontradas.
 */
class SatisfactionEvaluator
{
    private:
        std::string _expression;
        std::string _input;
        
        LinkedList<int>* _variablesIndex;
        LinkedList<LinkedList<InputValue>*> _allInputsCombination;

        LinkedList<LinkedList<InputValue>*>* _trueCombinations;
        LinkedList<LinkedList<InputValue>*>* _falseCombinations;

        LinkedList<std::string>* _solutions;
        LinkedList<std::string>* _fails;

        /**
         * @brief Verifica se uma restrição de "PARA TODO" é válida.
         *
         * @param index O índice da variável a ser verificada.
         * @return true se a condição é satisfeita, false caso contrário.
         */
        bool ForAllAssert(int index);

        /**
         * @brief Verifica se uma restrição de "EXISTE" é válida.
         *
         * @param index O índice da variável a ser verificada.
         * @return true se a condição é satisfeita, false caso contrário.
         */
        bool ExistsAssert(int index);

        /**
         * @brief Configura a lista de índices das variáveis na expressão.
         */
        void SetupVariablesIndex();

        /**
         * @brief Verifica se há uma variável correspondente para um índice.
         *
         * @param index O índice a ser verificado.
         * @return true se houver uma variável correspondente para o índice, false caso contrário.
         */
        bool HasVariableForIndex(int index);

        /**
         * @brief Verifica se uma variável é irrelevante para o resultado da expressão.
         *
         * @param result O resultado da expressão.
         * @param index O índice da variável a ser verificada.
         * @return true se a variável é irrelevante, false caso contrário.
         */
        bool IsVariableIrreleant(std::string& result, int index);

        /**
         * @brief Verifica se o operador 'exists' é irrelevante para o resultado da expressão.
         *
         * @param result O resultado da expressão.
         * @param index O índice do operador 'exists' a ser verificado.
         * @return true se o operador 'exists' é irrelevante, false caso contrário.
         */
        bool IsExistsIrrelevant(std::string& result, int index);

        /**
         * @brief Verifica se o operador 'forall' é irrelevante para o resultado da expressão.
         *
         * @param result O resultado da expressão.
         * @param index O índice do operador 'forall' a ser verificado.
         * @return true se o operador 'forall' é irrelevante, false caso contrário.
         */
        bool IsForAllIrrelevant(std::string& result, int index);

        /**
         * @brief Executa todas as combinações de valores de entrada possíveis.
         */
        void ExecuteAllInputsCombination();

        /**
         * @brief Executa uma combinação de valores de entrada.
         *
         * @param expression A expressão a ser avaliada.
         * @param values A lista de valores de entrada.
         */
        void ExecuteInputCombination(Expression* expression, LinkedList<InputValue>* inputList);

        /**
         * @brief Converte uma lista de valores de entrada em uma única string.
         *
         * @param values A lista de valores de entrada.
         * @return Uma string representando os valores de entrada.
         */
        std::string ConvertValueListIntoString(LinkedList<InputValue>* values);

        /**
         * @brief Converte uma lista de listas de valores de entrada em uma lista de strings.
         *
         * @param values A lista de listas de valores de entrada.
         * @return Uma lista de strings representando as combinações de valores de entrada.
         */
        LinkedList<std::string>* ConvertValueListIntoStringList(LinkedList<LinkedList<InputValue>*>* values);
    public:
        /**
         * @brief Construtor da classe SatisfactionEvaluator.
         *
         * Cria uma instância de SatisfactionEvaluator com uma expressão e uma representação de variáveis de entrada.
         *
         * @param expression A expressão lógica a ser avaliada.
         * @param input A representação das entradas fixas e variáveis.
         */
        SatisfactionEvaluator(std::string expression, std::string input);

        /**
         * @brief Destrutor da classe SatisfactionEvaluator.
         *
         * Libera a memória alocada durante a execução da classe SatisfactionEvaluator.
         */
        ~SatisfactionEvaluator();

        /**
         * @brief Verifica se a expressão possui alguma solução.
         *
         * @return true se houver pelo menos uma solução, false caso contrário.
         */
        bool HasSolution();

        /**
         * @brief Obtém a solução encontrada, marcando variáveis irrelevantes como 'a'.
         *
         * @return A string representando a solução que satisfaz as restrições da expressão.
         */
        std::string GetSolution();
};

#endif