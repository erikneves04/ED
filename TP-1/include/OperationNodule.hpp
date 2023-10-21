#pragma once

#ifndef OPRATIONNODULE_HPP
#define OPRATIONNODULE_HPP

#include <string>

#include "Nodule.hpp"
#include "InputNodule.hpp"

#define OR ("|")
#define AND ("&")
#define NOT ("~")

/**
 * @brief Exceção lançada quando um formato de operação é inválido.
 *
 * Esta exceção é lançada quando ocorre uma tentativa de executar uma operação com um formato inválido.
 */
class invalid_operation_format_exception
{};

/**
 * @brief Classe que representa um nódulo de operação em uma expressão.
 *
 * Esta classe é uma extensão da classe Nodule e representa um nódulo de operação em uma expressão booleana.
 * Ela pode executar operações com outros nódulos de entrada ou outros nódulos de operação, desde que o formato da
 * operação seja válido.
 */
class OperationNodule
    : public Nodule
{
    public:
        /**
         * @brief Construtor da classe OperationNodule.
         *
         * Cria uma instância de OperationNodule associada a um valor.
         *
         * @param value O valor associado ao nódulo de operação.
         */
        OperationNodule(std::string value);

        /**
         * @brief Executa a operação com dois nódulos de entrada.
         *
         * @param left O nódulo de entrada esquerdo.
         * @param right O nódulo de entrada direito.
         * @return true se a operação for bem-sucedida, false caso contrário.
         * @throw invalid_operation_format_exception Se o formato da operação for inválido.
         */
        bool PerformOperation(InputNodule* left, InputNodule* right);

        /**
         * @brief Executa a operação com um único nódulo de entrada.
         *
         * @param value O nódulo de entrada para a operação.
         * @return true se a operação for bem-sucedida, false caso contrário.
         * @throw invalid_operation_format_exception Se o formato da operação for inválido.
         */
        bool PerformOperation(InputNodule* value);

        /**
         * @brief Verifica se o nódulo de operação tem precedência maior do que outro nódulo de operação.
         *
         * @param other O nódulo de operação a ser comparado.
         * @return true se o nódulo de operação atual tiver precedência maior, false caso contrário.
         */
        bool HasAGreaterPrecedenceThan(OperationNodule* other);
};

/**
 * @brief Classe que representa um nódulo de parênteses em uma expressão.
 *
 * Esta classe é uma extensão da classe Nodule e representa um nódulo de parênteses (início ou fim) em uma expressão matemática.
 * Ela é usada para delimitar grupos de operações com prioridade ou para indicar início e fim de expressões aninhadas.
 */
class ParenthesesNodule
    : public Nodule
{
    public:
        ParenthesesNodule* _end;

        /**
         * @brief Construtor da classe ParenthesesNodule.
         *
         * Cria uma instância de ParenthesesNodule associada a um valor e um tipo específico.
         *
         * @param value O valor associado ao nódulo de parênteses.
         * @param type O tipo do nódulo de parênteses (START_PARENTHESES ou END_PARENTHESES).
         */
        ParenthesesNodule(std::string value, NoduleType type);
};

#endif