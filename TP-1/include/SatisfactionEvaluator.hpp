#pragma once

#ifndef SATISFACTIONEVALUATOR_HPP
#define SATISFACTIONEVALUATOR_HPP

#include <string>

#include "InputNodule.hpp"
#include "DataStructures/LinkedList.hpp"

#define EXISTS ("e")
#define FOR_ALL ("a")

class SatisfactionEvaluator
{
    private:
        std::string _expression;
        std::string _input;
        
        LinkedList<int> _variablesIndex;
        LinkedList<LinkedList<InputValue>*> _allInputsCombination;
        LinkedList<LinkedList<InputValue>*> _asserts;

        bool ForAllAssert(int index);
        bool ExistsAssert(int index);

        void SetupVariablesIndex();
        bool HasVariableForIndex(int index);
        
        void InsertInputListIntoAsserts(int index, LinkedList<InputValue>* inputList);
        void ExecuteAllInputsCombination();
        void SetupAssertsIntersection();
    public:
        SatisfactionEvaluator(std::string expression, std::string input);
        ~SatisfactionEvaluator();

        bool HasSolution();

};

#endif
