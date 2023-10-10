#pragma once

#ifndef EXPRESSIONORDERER_HPP
#define EXPRESSIONORDERER_HPP

#include <string>

#include "InputNodule.hpp"
#include "OperationNodule.hpp"
#include "ParenthesesNodule.hpp"

#include "DataStructures/LinkedList.hpp"
#include "DataStructures/Stack.hpp"

#define RESULT_NODULE_NAME ("result")

class ExpressionOrderer
{
    private:
        Stack<InputNodule*>* _inputStack;
        Stack<Nodule*>* _operationStack;

        void ExecutePendingOperations();
        void ExecutePrecedenceOperations(OperationNodule* operation);
        void ExecuteAllParenthesesNodules();
        void ExecuteOperationNodule(OperationNodule* operation);
        bool TakeLastInputValue();
    public:
        ExpressionOrderer();
        ~ExpressionOrderer();

        bool Perform(LinkedList<Nodule*>* nodules);
};

#endif