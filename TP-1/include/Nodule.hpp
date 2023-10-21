#pragma once

#ifndef NODULE_HPP
#define NODULE_HPP

#include <string>

/**
 * @brief Enumeração que representa os tipos de nódulos em uma expressão.
 *
 * Esta enumeração define os tipos de nódulos que podem ocorrer em uma expressão booleana.
 * Os tipos incluem entrada, operador, início de parênteses e fim de parênteses.
 */
enum class NoduleType
{
    INPUT,
    OPERATOR,
    START_PARENTHESES,
    END_PARENTHESES
};

/**
 * @brief Classe que representa um nódulo em uma expressão.
 *
 * Esta classe representa um item em uma expressão booleana. Ela pode ser de vários tipos,
 * incluindo entrada (variável), operador, início de parênteses e fim de parênteses. Cada nódulo
 * possui um valor e um tipo associados a ele.
 */
class Nodule
{
    protected:
        NoduleType _type;
        std::string _value;

    public:
        /**
         * @brief Construtor padrão da classe Nodule.
         *
         * Cria uma instância de Nodule sem um valor ou tipo especificado.
         */
        Nodule();

        /**
         * @brief Construtor da classe Nodule.
         *
         * Cria uma instância de Nodule associada a um valor e um tipo específico.
         *
         * @param value O valor associado ao nódulo.
         * @param type O tipo do nódulo (NoduleType).
         */
        Nodule(std::string value, NoduleType type);

        /**
         * @brief Obtém o tipo do nódulo.
         *
         * @return O tipo do nódulo (NoduleType).
         */
        NoduleType GetType();

        /**
         * @brief Obtém o valor do nódulo.
         *
         * @return O valor associado ao nódulo.
         */
        std::string GetValue();
};

#endif