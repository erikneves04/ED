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

        LinkedList<LinkedList<InputValue>*>* _trueCombinations;
        LinkedList<LinkedList<InputValue>*>* _falseCombinations;

        LinkedList<std::string>* _solutions;
        LinkedList<std::string>* _fails;

        bool ForAllAssert(int index);
        bool ExistsAssert(int index);

        void SetupVariablesIndex();
        bool HasVariableForIndex(int index);

        bool IsVariableIrreleant(std::string& result, int index);
        bool IsExistsIrrelevant(std::string& result, int index);
        bool IsForAllIrrelevant(std::string& result, int index);

        void ExecuteAllInputsCombination();

        std::string ConvertValueListIntoString(LinkedList<InputValue>* values);
        LinkedList<std::string>* ConvertValueListIntoStringList(LinkedList<LinkedList<InputValue>*>* values);
    public:
        SatisfactionEvaluator(std::string expression, std::string input);
        ~SatisfactionEvaluator();

        bool HasSolution();
        std::string GetSolution();

};

#endif
