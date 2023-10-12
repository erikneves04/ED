#pragma once

#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>

#include "DataStructures/LinkedList.hpp"

#include "Nodule.hpp"
#include "InputNodule.hpp"

class difference_between_inputs_and_variable_count_exception
{ };

class Expression
{
    private:
        bool _disableValuesMemoryDelete = false;
        bool _valuesWasSet = false;
        int _inputCount = 0;
        int _differentVariablesOnExpression = 0;

        LinkedList<Nodule*>* _expression = nullptr;
        LinkedList<InputValue>* _values = nullptr;

        void SetupValues(std::string values);
        void SetupExpression(std::string expression);

        bool FindValue(std::string key);
        bool FindValue(std::string key, LinkedList<InputValue>* values);

        void SetupVariableExpressionCount();
    public:
        Expression(std::string expression, std::string values);
        Expression(std::string expression);
        ~Expression();

        bool Evaluate();
        bool Evaluate(LinkedList<InputValue>* values);

};

#endif