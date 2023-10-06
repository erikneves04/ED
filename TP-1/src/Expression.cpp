#include <string>
#include <vector>

#include <iostream>

#include "DataStructures/LinkedList.hpp"
#include "DataStructures/Stack.hpp"

#include "Nodule.hpp"
#include "InputNodule.hpp"
#include "OperationNodule.hpp"
#include "ParenthesesNodule.hpp"

#include "Expression.hpp"
#include "ExpressionOrderer.hpp"

Expression::Expression(std::string expression, std::string values)
{
    SetupValues(values);
    SetupExpression(expression);
}

Expression::Expression(std::string expression)
{
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

    if (_valuesWasSet)
        delete _values;
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

std::vector<std::string> ParseExpressionString(std::string expression)
{
    std::vector<std::string> tokens;
    std::string currentToken;

    for (char ch : expression) 
    {
        if (ch == ' ') 
        {
            if (!currentToken.empty()) 
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        } else 
        {
            currentToken += ch;
        }
    }
    
    if (!currentToken.empty()) 
    {
        tokens.push_back(currentToken);
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

    for (int i = 0; i < values->Length(); i++)
    {
        auto pair = values->Get(i);
        if(pair.key == key)
            return pair.value;
    }

    throw value_not_set_exception();
}

bool Expression::FindValue(std::string key)
{
    return FindValue(key, _values);
}

void Expression::SetupExpression(std::string expression)
{
    _expression = new LinkedList<Nodule*>();

    auto tokens = ParseExpressionString(expression);
    auto startParentheses = Stack<ParenthesesNodule*>();

    for (std::size_t i = 0; i < tokens.size(); i++)
    {
        auto value = tokens[i];
        if(value.empty())
            continue;

        if (value == ")" || value == "(")
        {
            auto nodule = ParseParenthesesNodule(value, startParentheses);
            _expression->Insert(nodule);
            continue;
        }

        if (value == NOT)
        {
            auto next = tokens[i + 1];
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
    }

    if (_valuesWasSet && _values->Length() != _inputCount)
        throw difference_between_inputs_and_variable_count_exception();
}

bool Expression::Evaluate()
{
    if (!_valuesWasSet)
        throw value_not_set_exception();

    return ExpressionOrderer().Perform(_expression);
}

bool Expression::Evaluate(LinkedList<InputValue>* values)
{
    if (values->Length() != _inputCount)
        throw difference_between_inputs_and_variable_count_exception();

    _valuesWasSet = true;

    if (_values != nullptr)
        delete _values;

    _values = values;

    for(int i = 0; i < _expression->Length(); i++)
    {
        auto nodule = _expression->Get(i);
        if(nodule->GetType() == NoduleType::INPUT)
        {
            auto input = (InputNodule*)nodule;
            auto newValue = FindValue(input->GetValue(), values);
            input->SetCurrentValue(newValue);
        }
    }

    return Evaluate();
}