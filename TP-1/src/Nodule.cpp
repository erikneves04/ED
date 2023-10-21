#include <string>
#include "Nodule.hpp"

Nodule::Nodule()
{
    _value = '0';
    _type = NoduleType::INPUT;
}

Nodule::Nodule(std::string value, NoduleType type)
{
    _value = value;
    _type = type;
}

NoduleType Nodule::GetType()
{
    return _type;
}

std::string Nodule::GetValue()
{
    return _value;
}