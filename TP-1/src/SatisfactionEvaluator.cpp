#include <string>
#include <iostream>

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

        if (result)        
            _asserts.Insert(inputList);
        else
            _fails.Insert(inputList);
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

bool IsExistsDeterminant(char value, std::string& result, int index, LinkedList<std::string>* solutions, LinkedList<std::string>* fails)
{
    bool isDeterminant = false;

    for(int i = 0; i < solutions->Length(); i++)
    {
        std::string solution = solutions->Get(i);
        solution[index] = value;
        
        if (fails->Contains(solution))
            break;
        else if (i == solutions->Length() - 1)
        {
            isDeterminant = true;
            break;
        }
    }

    if (isDeterminant)
        result[index] = value;        

    return isDeterminant;
}

bool SatisfactionEvaluator::IsExistsIrrelevant(std::string& result, int index, LinkedList<std::string>* solutions, LinkedList<std::string>* fails)
{
    bool zeroIsDeterminant = IsExistsDeterminant('0', result, index, solutions, fails);
    bool oneIsDeterminant = IsExistsDeterminant('1', result, index, solutions, fails);

    if (zeroIsDeterminant && oneIsDeterminant)
        return true;
    else
        return false;
}

bool SatisfactionEvaluator::IsForAllIrrelevant(std::string& result, int index, LinkedList<std::string>* solutions, LinkedList<std::string>* fails)
{
    std::string withOtherValue = result;
    withOtherValue[index] = (result[index] == '0') ? '1' : '0';
    
    if (solutions->Contains(withOtherValue))
        return true;

    for(unsigned int i = 0; i < (unsigned int)solutions->Length(); i++)
    {
        auto solution = solutions->Get(i);

        for(unsigned int j = 0; j < result.length(); j++)
        {
            if (solution[j] == SOLUTION_IRRELEVANT_OUTPUT || result[j] == SOLUTION_IRRELEVANT_OUTPUT || solution[j] == result[j])
            {
                if (j == solution.length() - 1)
                    return true;
                else
                    continue;
            }

            if (solution[j] != result[j])
                break; 

            if (j == solution.length() - 1)
                return true;
        }
    }
    
    return false;
}

bool SatisfactionEvaluator::IsVariableIrreleant(std::string& result, int index, LinkedList<std::string>* solutions, LinkedList<std::string>* fails)
{
    std::string input(1, _input[index]);

    if (input == EXISTS)
        return IsExistsIrrelevant(result, index, solutions, fails);
    else if (input == FOR_ALL)
        return IsForAllIrrelevant(result, index, solutions, fails);

    return false;
}

LinkedList<std::string>* ConvertValueListIntoStringList(LinkedList<LinkedList<InputValue>*> values)
{
    LinkedList<std::string>* result = new LinkedList<std::string>();
    
    for(int i = 0; i < values.Length(); i++)
    {
        LinkedList<InputValue>* value = values.Get(i);
        std::string solution = ConvertValueListIntoString(value);
        result->Insert(solution);
    }

    return result;
}

std::string SatisfactionEvaluator::GetSolution()
{
    if (!HasSolution())
        return "";

    if (_asserts.Length() == 1)
        return ConvertValueListIntoString(_asserts.Get(0));

    LinkedList<std::string>* solutions = ConvertValueListIntoStringList(_asserts);
    LinkedList<std::string>* fails = ConvertValueListIntoStringList(_fails);

    std::string result = solutions->Get(0);

    for(unsigned int i = 0; i < _input.length(); i++)
    {
        std::string input(1, _input[i]);
        
        if (input == EXISTS || input == FOR_ALL)
        {
            if (IsVariableIrreleant(result, i, solutions, fails))
            {
                result[i] = SOLUTION_IRRELEVANT_OUTPUT;

                if (!solutions->Contains(result))
                    solutions->Insert(result);
            }
                
        }
    }

    //delete solutions;
    //delete fails;

    return result;
}