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

bool OperationNodule::PerformOperation(InputNodule left, InputNodule right)
{
    if (_value == OR)
        return left.GetValue() || right.GetValue();

    if (_value == AND)
        return left.GetValue() && right.GetValue();

    throw invalid_operation_format_exception();
}

bool OperationNodule::PerformOperation(InputNodule value)
{
    if (_value == NOT)
        return !value.GetValue();

    throw invalid_operation_format_exception();
}