#pragma once

#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>

#include "DataStructures/LinkedList.hpp"

#include "Nodule.hpp"
#include "InputNodule.hpp"

/**
 * @brief Exceção lançada quando o número de entradas fornecidas é diferente do número de variáveis na expressão.
 *
 * Esta classe representa uma exceção personalizada que é lançada quando o número de entradas fornecidas 
 * é diferente do número de variáveis na expressão, o que impossibilita a avaliação correta do resultado.
 */
class difference_between_inputs_and_variable_count_exception
{ };

/**
 * @file Expression.hpp
 * @brief Classe que representa uma expressão booleana em C++.
 *
 * Esta classe permite a criação e avaliação de expressões booleanas. Ela é capaz de analisar
 * a expressão e calcular seu valor com base em valores de entrada fornecidos. A classe também
 * suporta a definição de variáveis e seus valores associados.
 */
class Expression
{
    private:
        bool _disableValuesMemoryDelete = false;
        bool _valuesWasSet = false;
        int _inputCount = 0;
        int _differentVariablesOnExpression = 0;

        LinkedList<Nodule*>* _expression = nullptr;
        LinkedList<InputValue>* _values = nullptr;
        LinkedList<InputNodule*>* _variableNodules = nullptr;

        bool* _valuesMemory = nullptr;
        
        /**
         * @brief Faz a leitura de uma string de entrada e a converte para 
         * valores que serão atribuidos aos nódulos posteriormente.
         */
        void SetupValues(std::string values);

        /**
         * @brief Faz a leitura de uma string com a expressão booleana e a
         * converte para os nódulos que serão manipulaods pela classe.
         */
        void SetupExpression(std::string expression);

        /**
         * @brief Busca o valor de um nódulo com base em sua chave no conjunto
         * de valores de entrada.
         */
        bool FindValue(std::string key);

        /**
         * @brief Busca o valor de um nódulo com base em sua chave no conjunto
         * de valores fornecidos.
         */
        bool FindValue(std::string key, LinkedList<InputValue>* values);

        /**
         * @brief Atualiza os valores de entrada para as variáveis na expressão.
         *
         * @param values Uma lista de valores de entrada para as variáveis na expressão.
         */
        void SetMemoryValue(LinkedList<InputValue>* values);
    public:
        /**
         * @brief Construtor que aceita uma expressão e valores iniciais.
         *
         * Cria uma instância da classe Expression com uma expressão booleana e valores iniciais.
         *
         * @param expression A expressão booleana a ser avaliada.
         * @param values Uma string que representa os valores iniciais para as variáveis na expressão.
         */
        Expression(std::string expression, std::string values);
        
        /**
         * @brief Construtor que aceita apenas uma expressão.
         *
         * Cria uma instância da classe Expression com uma expressão booleana. Os valores das variáveis
         * devem ser definidos posteriormente.
         *
         * @param expression A expressão booleana a ser avaliada.
         */
        Expression(std::string expression);

        /**
         * @brief Destrutor da classe Expression.
         *
         * Libera a memória alocada durante a execução da classe Expression.
         */
        ~Expression();

        /**
         * @brief Avalia a expressão com base nos valores definidos.
         *
         * @return true se a avaliação for bem-sucedida, false caso contrário.
         */
        bool Evaluate();
        
        /**
         * @brief Avalia a expressão com base em valores fornecidos, os valores fornecidos podem ser
         * parciais, desde que anteriormente o método SetupMemoryValue tenha sido utilizados para atribuir
         * valores para as demais entradas.
         *
         * @param values Uma lista de valores de entrada para as variáveis na expressão.
         * @return true se a avaliação for bem-sucedida, false caso contrário.
         */
        bool Evaluate(LinkedList<InputValue>* values);

        /**
         * @brief Define os valores iniciais para as variáveis na expressão, visando rapidez no acesso, portanto
         * são usados vetores dinâmicos para armazenar e acessar esses dados.
         *
         * @param input Uma string que representa os valores iniciais para as variáveis na expressão.
         */
        void SetupMemoryValues(std::string input);
        
        /**
         * @brief Define os nódulos variáveis na expressão.
         *
         * @param input Uma string que descreve os nodos variáveis na expressão.
         */
        void SetupVariableNodules(std::string input);
};

#endif