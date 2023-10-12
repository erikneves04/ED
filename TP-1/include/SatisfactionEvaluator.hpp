#pragma once

#ifndef SATISFACTIONEVALUATOR_HPP
#define SATISFACTIONEVALUATOR_HPP

#include <string>

#include "InputNodule.hpp"
#include "DataStructures/LinkedList.hpp"

#define EXISTS ("e")
#define FOR_ALL ("a")

#define SOLUTION_IRRELEVANT_OUTPUT ('a')

class SatisfactionEvaluator
{
    private:
        std::string _expression;
        std::string _input;
        
        LinkedList<int>* _variablesIndex;
        LinkedList<LinkedList<InputValue>*> _allInputsCombination;

        LinkedList<LinkedList<InputValue>*>* _asserts;
        LinkedList<LinkedList<InputValue>*>* _fails;

        bool ForAllAssert(int index);
        bool ExistsAssert(int index);

        void SetupVariablesIndex();
        bool HasVariableForIndex(int index);

        bool IsVariableIrreleant(std::string& result, int index, LinkedList<std::string>* solutions, LinkedList<std::string>* fails);
        bool IsExistsIrrelevant(std::string& result, int index, LinkedList<std::string>* solutions, LinkedList<std::string>* fails);
        bool IsForAllIrrelevant(std::string& result, int index, LinkedList<std::string>* solutions, LinkedList<std::string>* fails);

        void ExecuteAllInputsCombination();
    public:
        SatisfactionEvaluator(std::string expression, std::string input);
        ~SatisfactionEvaluator();

        bool HasSolution();
        std::string GetSolution();

};

#endif
