#include <string>

#include "InputNodule.hpp"
#include "Expression.hpp"
#include "InputExchanger.hpp"
#include "SatisfactionEvaluator.hpp"

#include "DataStructures/Queue.hpp"
#include "DataStructures/LinkedList.hpp"

SatisfactionEvaluator::SatisfactionEvaluator(std::string expression, std::string input)
{
    _input = input;
    _expression = expression;

    SetupVariablesIndex();
    ExecuteAllInputsCombination();
}

SatisfactionEvaluator::~SatisfactionEvaluator()
{
    for (int i = 0; i < _allInputsCombination.Length(); i++)
    {
        LinkedList<InputValue>* inputList = _allInputsCombination.Get(i);
        delete inputList;
    }
}

void SatisfactionEvaluator::SetupVariablesIndex()
{
    for (unsigned int i = 0; i < _input.length(); i++)
    {
        std::string input(1, _input[i]);
        if (input == EXISTS || input == FOR_ALL)
            _variablesIndex.Insert(i);
    } 
}

bool SatisfactionEvaluator::HasVariableForIndex(int index)
{
    for (int i = 0; i < _variablesIndex.Length(); i++)
    {
        if (_variablesIndex.Get(i) == index)
            return true;
    }

    return false;
}

void SatisfactionEvaluator::ExecuteAllInputsCombination()
{
    auto expression = Expression(_expression);

    auto inputExchanger = InputExchanger(_input, _variablesIndex);
    auto allInputsCombination = inputExchanger.GetAllInputsCombination();

    while(!allInputsCombination->Empty())
    {
        auto inputList = allInputsCombination->Remove();
        _allInputsCombination.Insert(inputList);

        auto result = expression.Evaluate(inputList);

        if (result)                    
            _asserts.Insert(inputList);
    }

    delete allInputsCombination;
}

bool SatisfactionEvaluator::ForAllAssert(int index)
{
    bool hasZero = false;
    bool hasOne = false;

    for (int i = 0; i < _asserts.Length(); i++)
    {
        LinkedList<InputValue>* inputList = _asserts.Get(i);
        InputValue input = inputList->Get(index);
        bool value = input.value;

        if (value == false)
            hasZero = true;
        else if (value == true)
            hasOne = true;

        if (hasZero && hasOne)
            return true;
    }

    return false;
}

bool SatisfactionEvaluator::ExistsAssert(int index)
{
    return !_asserts.Empty();
}

bool SatisfactionEvaluator::HasSolution()
{
    for(size_t i = 0; i < _expression.length(); i++)
    {
        std::string input(1, _expression[i]);
        
        if (input == EXISTS && !ExistsAssert(i))
            return false;
        else if (input == FOR_ALL && !ForAllAssert(i))
            return false;
    }

    return true;
}