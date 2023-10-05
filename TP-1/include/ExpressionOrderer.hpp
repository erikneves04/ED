#pragma once

#ifndef EXPRESSIONORDERER_HPP
#define EXPRESSIONORDERER_HPP

#include <string>

#include "InputNodule.hpp"
#include "OperationNodule.hpp"
#include "ParenthesesNodule.hpp"

#include "DataStructures/LinkedList.hpp"
#include "DataStructures/Stack.hpp"

class ExpressionOrderer
{
    private:
        Stack<InputNodule*> _inputStack;
        Stack<Nodule*> _operationStack;

    public:
        bool Perform(LinkedList<Nodule*> nodules);
};

#endif