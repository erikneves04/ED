#include <string>

#include "DataStructures/LinkedList.hpp"
#include "DataStructures/Stack.hpp"

#include "Nodule.hpp"
#include "InputNodule.hpp"
#include "OperationNodule.hpp"

#include "Expression.hpp"
#include "ExpressionOrderer.hpp"

Expression::Expression(std::string expression, std::string values)
{
    SetupValues(values);
    SetupExpression(expression);
}

Expression::Expression(std::string expression)
{
    _variableNodules = new LinkedList<InputNodule*>();
    SetupExpression(expression);
}

Expression::~Expression()
{
    for (int i = 0; i < _expression->Length(); i++)
    {
        auto nodule = _expression->Get(i);
        delete nodule;
    }

    delete _expression;

    if (_valuesWasSet && !_disableValuesMemoryDelete)
        delete _values;

    if (_valuesMemory != nullptr)
        delete[] _valuesMemory;

    if (_variableNodules != nullptr)
        delete _variableNodules;
}

void Expression::SetupValues(std::string values)
{
    _values = new LinkedList<InputValue>();

    for (std::size_t i = 0; i < values.length(); i++)
    {
        auto value = values[i];
        std::string index = std::to_string(i);

        auto input = InputValue(index, value == '1');
        _values->Insert(input);
    }

    _valuesWasSet = true;
}

LinkedList<std::string>* ParseExpressionString(std::string expression)
{
    LinkedList<std::string>* tokens = new LinkedList<std::string>();
    std::string currentToken = "";

    expression += " ";

    for(unsigned int i = 0; i < expression.length(); i++)
    {
        std::string current(1, expression[i]);
        if (current == " " && i == 0)
            continue;

        if (current == " ")
        {
            if (currentToken != "")
            {
                tokens->Insert(currentToken);
                currentToken = "";
            }
        }
        else
        {
            currentToken += current;
        }
    }

    return tokens;
}

ParenthesesNodule* ParseParenthesesNodule(std::string value, Stack<ParenthesesNodule*>& startParentheses)
{
    if(value == "(")
    {
        ParenthesesNodule* parentheses = new ParenthesesNodule(value, NoduleType::START_PARENTHESES);
        startParentheses.Insert(parentheses);

        return parentheses;
    }
    else
    {
        ParenthesesNodule* parentheses = new ParenthesesNodule(value, NoduleType::END_PARENTHESES);
        auto start_reference = startParentheses.Remove();
        start_reference->_end = parentheses;
        
        return parentheses;
    }
}

bool Expression::FindValue(std::string key, LinkedList<InputValue>* values)
{
    if(!_valuesWasSet)
        throw value_not_set_exception();

    if (_valuesMemory == nullptr)
    {    for (int i = 0; i < values->Length(); i++)
        {
            auto pair = values->Get(i);
            if(pair.key == key)
                return pair.value;
        }

        throw value_not_set_exception();
    }

    int keyIndex = stoi(key);
    
    if (keyIndex >= _inputCount || keyIndex < 0)
        throw value_not_set_exception();        

    return _valuesMemory[keyIndex];
}

void Expression::SetupMemoryValues(std::string input)
{
    unsigned int len = input.length();
    
    _valuesWasSet = true;
    _valuesMemory = new bool[len];
    
    for (unsigned int i = 0; i < len; i++)
    {
        auto value = input[i];
        std::string index = std::to_string(i);

        _valuesMemory[i] = value == '1';
    }

    for(int i = 0; i < _expression->Length(); i++)
    {   
        auto nodule = _expression->Get(i);
        if(nodule->GetType() == NoduleType::INPUT)
        {
            auto input = (InputNodule*)nodule;
            auto newValue = FindValue(input->GetValue());

            input->SetCurrentValue(newValue);
        }
    }
}

void Expression::SetMemoryValue(LinkedList<InputValue>* values)
{
    for (int i = 0; i < values->Length(); i++)
    {
        auto value = values->Get(i);
        auto index = stoi(value.key);

        _valuesMemory[index] = value.value;
    }
}

bool Expression::FindValue(std::string key)
{
    return FindValue(key, _values);
}

void Expression::SetupExpression(std::string expression)
{
    _differentVariablesOnExpression = 0;
    LinkedList<std::string> variables;

    _expression = new LinkedList<Nodule*>();

    auto tokens = ParseExpressionString(expression);
    auto startParentheses = Stack<ParenthesesNodule*>();
    
    for (int i = 0; i < tokens->Length(); i++)
    {
        auto value = tokens->Get(i);
        if (value == ")" || value == "(")
        {
            if (value == ")" && startParentheses.Empty())
                continue;

            auto nodule = ParseParenthesesNodule(value, startParentheses);
            _expression->Insert(nodule);
            continue;
        }
       
        if (value == NOT)
        {
            auto next = tokens->Get(i + 1);
            if (next == NOT)
            {
                i++;
                continue;
            }
        }

        if (value == OR || value == AND || value == NOT)
        {
            auto nodule = new OperationNodule(value);
            _expression->Insert(nodule);
            continue;
        }

        _inputCount++;
        if (_valuesWasSet)
        {
            auto nodule = new InputNodule(value, FindValue(value));
            _expression->Insert(nodule);
        }
        else
        {
            auto nodule = new InputNodule(value);
            _expression->Insert(nodule);
        }

        if (!variables.Contains(value))
        {
            variables.Insert(value);
            _differentVariablesOnExpression++;
        }
    }

    delete tokens;

    if (_valuesWasSet && _values->Length() < _differentVariablesOnExpression)
        throw difference_between_inputs_and_variable_count_exception();
}

void Expression::SetupVariableNodules(std::string input)
{
    for(int i = 0; i < _expression->Length(); i++)
    {
        auto nodule = _expression->Get(i);
        if(nodule->GetType() == NoduleType::INPUT)
        {
            auto inputNodule = (InputNodule*)nodule;
            
            auto index = stoi(inputNodule->GetValue());
            auto flag = input[index];

            if(!(flag == '0' || flag == '1'))
                _variableNodules->Insert(inputNodule);
        }
    }
}

bool Expression::Evaluate()
{
    if (!_valuesWasSet)
        throw value_not_set_exception();
        
    return ExpressionOrderer().Perform(_expression);
}

bool Expression::Evaluate(LinkedList<InputValue>* values)
{       
    _valuesWasSet = true;
    _disableValuesMemoryDelete = true;

    SetMemoryValue(values);
    
    for(int i = 0; i < _variableNodules->Length(); i++)
    {   
        auto nodule = _variableNodules->Get(i);
        if(nodule->GetType() == NoduleType::INPUT)
        {
            auto input = (InputNodule*)nodule;
            auto newValue = FindValue(input->GetValue(), values);

            input->SetCurrentValue(newValue);
        }
    }
    
    return Evaluate();
}