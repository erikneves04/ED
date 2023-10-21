#pragma once

#ifndef INPUTNODULE_HPP
#define INPUTNODULE_HPP

#include <string>
#include "Nodule.hpp"

/**
 * @brief Exceção lançada quando um valor não foi definido corretamente.
 *
 * Esta exceção é lançada quando ocorre uma tentativa de acesso a um valor que não foi definido.
 */
class value_not_set_exception
{};

/**
 * @brief Classe que representa um valor de entrada booleano.
 *
 * Esta classe representa um valor de entrada booleano que é associado a uma chave ou variável.
 */
class InputValue
{
    public:
        std::string key;
        bool value;

        /**
         * @brief Construtor padrão da classe InputValue.
         *
         * Cria uma instância de InputValue com valores padrão (chave vazia e valor falso).
         */
        InputValue();

        /**
         * @brief Construtor da classe InputValue.
         *
         * Cria uma instância de InputValue associada a uma chave e um valor booleano.
         *
         * @param key A chave ou variável associada ao valor.
         * @param value O valor booleano a ser associado à chave.
         */
        InputValue(std::string key, bool value);
};

/**
 * @brief Classe que representa um nódulo de entrada booleano.
 *
 * Esta classe é uma extensão da classe Nodule e representa um nódulo de entrada booleano que pode
 * conter um valor atual. Ela é usada para representar variáveis booleanas na expressão.
 */
class InputNodule
    : public Nodule
{
    protected:
        bool _currentValue;
        bool _currentValueIsSet = false;

    public:
        /**
         * @brief Construtor padrão da classe InputNodule.
         *
         * Cria uma instância de InputNodule sem um valor atual definido.
         */
        InputNodule();

        /**
         * @brief Construtor da classe InputNodule.
         *
         * Cria uma instância de InputNodule associada a uma chave e um valor atual.
         *
         * @param value A chave ou variável associada ao nódulo de entrada.
         */
        InputNodule(std::string value);

        /**
         * @brief Construtor da classe InputNodule.
         *
         * Cria uma instância de InputNodule associada a uma chave e um valor atual.
         *
         * @param value A chave ou variável associada ao nódulo de entrada.
         * @param currentValue O valor atual associado ao nódulo de entrada.
         */
        InputNodule(std::string value, bool currentValue);

        /**
         * @brief Obtém o valor atual do nódulo de entrada.
         *
         * @return O valor atual do nódulo de entrada.
         * @throw value_not_set_exception Se o valor atual não foi definido.
         */
        bool GetCurrentValue();

        /**
         * @brief Define um novo valor atual para o nódulo de entrada.
         *
         * @param newValue O novo valor atual a ser associado ao nódulo de entrada.
         */
        void SetCurrentValue(bool newValue);
};

#endif