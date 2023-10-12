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

    delete _variablesIndex;
}

void SatisfactionEvaluator::SetupVariablesIndex()
{
    _variablesIndex = new LinkedList<int>();

    for (unsigned int i = 0; i < _input.length(); i++)
    {
        std::string input(1, _input[i]);
        if (input == EXISTS || input == FOR_ALL)
            _variablesIndex->Insert(i);
    } 
}

bool SatisfactionEvaluator::HasVariableForIndex(int index)
{
    std::string value(1, _input[index]);
    return (value == EXISTS || value == FOR_ALL);
}

void SatisfactionEvaluator::ExecuteAllInputsCombination()
{
    auto expression = new Expression(_expression);

    auto inputExchanger = new InputExchanger(_input, _variablesIndex);
    auto allInputsCombination = inputExchanger->GetAllInputsCombination();

    while(!allInputsCombination->Empty())
    {

        auto inputList = allInputsCombination->Remove();
        _allInputsCombination.Insert(inputList);

        auto result = expression->Evaluate(inputList);

        if (!result)            
            continue;
        
        _asserts.Insert(inputList);
    }

    delete allInputsCombination;
    delete inputExchanger;
    delete expression;
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
    for(size_t i = 0; i < _input.length(); i++)
    {
        std::string input(1, _input[i]);
        
        if (input == EXISTS && !ExistsAssert(i))
            return false;

        else if (input == FOR_ALL && !ForAllAssert(i))
            return false;
    }

    return true;
}

std::string ConvertValueListIntoString(LinkedList<InputValue>* values)
{
    std::string result = "";

    for(int i = 0; i < values->Length(); i++)
    {
        InputValue value = values->Get(i);
        result += std::to_string(value.value);
    }

    return result;
}

std::string SatisfactionEvaluator::GetSolution()
{
    if (_asserts.Length() == 1)
        return ConvertValueListIntoString(_asserts.Get(0));

    LinkedList<std::string> solutions;
    for(int i = 0; i < _asserts.Length(); i++)
    {
        LinkedList<InputValue>* values = _asserts.Get(i);
        std::string solution = ConvertValueListIntoString(values);
        solutions.Insert(solution);
    }

    std::string result = solutions.Get(0);

    for(unsigned int i = 0; i < _input.length(); i++)
    {
        std::string input(1, _input[i]);
        
        if (input == EXISTS || input == FOR_ALL)
        {
            std::string withOtherValue = result;
            withOtherValue[i] = (result[i] == '0') ? '1' : '0';
            
            if (solutions.Contains(withOtherValue))
                result[i] = 'a';
        }
    }

    return result;
}