#include "Nodule.hpp"
#include "OperationNodule.hpp"

OperationNodule::OperationNodule(std::string value)
    : Nodule(value, NoduleType::OPERATOR)
{
    if (value != OR && value != AND && value != NOT)
    {
        throw invalid_operation_format_exception();
    }
}

bool OperationNodule::PerformOperation(InputNodule* left, InputNodule* right)
{
    if (_value == OR)
        return left->GetCurrentValue() || right->GetCurrentValue();

    if (_value == AND)
        return left->GetCurrentValue() && right->GetCurrentValue();

    throw invalid_operation_format_exception();
}

bool OperationNodule::PerformOperation(InputNodule* value)
{
    if (_value == NOT)
        return !value->GetCurrentValue();

    throw invalid_operation_format_exception();
}

bool OperationNodule::HasAGreaterPrecedenceThan(OperationNodule* other)
{
    if (_value == NOT)
        return true;

    if (_value == AND && other->_value == OR)
        return true;

    return false;
}