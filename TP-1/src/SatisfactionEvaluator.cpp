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

    _trueCombinations = new LinkedList<LinkedList<InputValue>*>();
    _falseCombinations = new LinkedList<LinkedList<InputValue>*>();

    SetupVariablesIndex();
    ExecuteAllInputsCombination();

    _solutions = ConvertValueListIntoStringList(_trueCombinations);
    _fails = ConvertValueListIntoStringList(_falseCombinations);
}

SatisfactionEvaluator::~SatisfactionEvaluator()
{
    delete _trueCombinations;
    delete _falseCombinations;
    
    delete _solutions;
    delete _fails;
    
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

std::string SatisfactionEvaluator::ConvertValueListIntoString(LinkedList<InputValue>* values)
{
    std::string result = "";

    for(int i = 0; i < values->Length(); i++)
    {
        InputValue value = values->Get(i);
        result += std::to_string(value.value);
    }

    return result;
}

LinkedList<std::string>* SatisfactionEvaluator::ConvertValueListIntoStringList(LinkedList<LinkedList<InputValue>*>* values)
{
    LinkedList<std::string>* result = new LinkedList<std::string>();
    
    for(int i = 0; i < values->Length(); i++)
    {
        LinkedList<InputValue>* value = values->Get(i);
        std::string solution = ConvertValueListIntoString(value);
        result->Insert(solution);
    }

    return result;
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
            _trueCombinations->Insert(inputList); 
        else
            _falseCombinations->Insert(inputList);
    }

    delete allInputsCombination;
    delete inputExchanger;
    delete expression;
}

bool SatisfactionEvaluator::ForAllAssert(int index)
{
    bool found = true;
    for (int i = 0; i < _trueCombinations->Length(); i++)
    {
        std::string assert = _solutions->Get(i);
        char newChar = assert[index] == '0' ? '1' : '0';
        assert[index] = newChar;

        if (!_solutions->Contains(assert))
        {
            found = false;
            break;
        }
    }
    
    if (found)
        return true;

    return false;
}

bool SatisfactionEvaluator::ExistsAssert(int index)
{
    if (_trueCombinations->Length() == _allInputsCombination.Length() || _falseCombinations->Length() == 0)
        return true;

    for(int i = 0; i < _fails->Length(); i++)
    {
        auto fail = _fails->Get(i);
        char newChar = fail[index] == '0' ? '1' : '0';
        fail[index] = newChar;

        if (_solutions->Contains(fail))
            return true;
    }

    for(int i = 0; i < _solutions->Length(); i++)
    {
        auto assert = _solutions->Get(i);
        char newChar = assert[index] == '0' ? '1' : '0';
        assert[index] = newChar;

        if (_solutions->Contains(assert) || _fails->Contains(assert))
            return true;
    }

    return false;
}

bool SatisfactionEvaluator::HasSolution()
{
    if (_falseCombinations->Length() == _allInputsCombination.Length())
        return false;

    if (_trueCombinations->Length() == _allInputsCombination.Length())
        return true;

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

bool SatisfactionEvaluator::IsExistsIrrelevant(std::string& result, int index)
{
    bool zeroIsDeterminant = IsExistsDeterminant('0', result, index, _solutions, _fails);
    bool oneIsDeterminant = IsExistsDeterminant('1', result, index, _solutions, _fails);

    if (zeroIsDeterminant && oneIsDeterminant)
        return true;
    else
        return false;
}

bool SatisfactionEvaluator::IsForAllIrrelevant(std::string& result, int index)
{
    std::string withOtherValue = result;
    withOtherValue[index] = (result[index] == '0') ? '1' : '0';
    
    if (_solutions->Contains(withOtherValue))
        return true;

    for(unsigned int i = 0; i < (unsigned int)_solutions->Length(); i++)
    {
        auto solution = _solutions->Get(i);

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

bool SatisfactionEvaluator::IsVariableIrreleant(std::string& result, int index)
{
    std::string input(1, _input[index]);

    if (input == EXISTS)
        return IsExistsIrrelevant(result, index);
    else if (input == FOR_ALL)
        return IsForAllIrrelevant(result, index);

    return false;
}

std::string SatisfactionEvaluator::GetSolution()
{
    if (!HasSolution())
        return "";

    if (_trueCombinations->Length() == 1)
        return ConvertValueListIntoString(_trueCombinations->Get(0));

    std::string result = _solutions->Get(0);

    for(unsigned int i = 0; i < _input.length(); i++)
    {
        std::string input(1, _input[i]);
        
        if ((input == EXISTS || input == FOR_ALL) && IsVariableIrreleant(result, i))
            result[i] = SOLUTION_IRRELEVANT_OUTPUT;
    }

    return result;
}