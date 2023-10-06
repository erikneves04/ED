#include <string>

#include "InputNodule.hpp"
#include "DataStructures/LinkedList.hpp"

InputValue::InputValue()
{
    key = '0';
    value = false;
}

InputValue::InputValue(std::string key, bool value)
{
    this->key = key;
    this->value = value;
}

InputNodule::InputNodule(std::string value)
    : Nodule(value, NoduleType::INPUT)
{
    _currentValueIsSet = false;
}

InputNodule::InputNodule(std::string value, bool currentValue)
    : Nodule(value, NoduleType::INPUT)
{
    _currentValue = currentValue;
    _currentValueIsSet = true;
}

bool InputNodule::GetCurrentValue()
{
    if (!_currentValueIsSet)
        throw value_not_set_exception();
    
    return _currentValue;
}

void InputNodule::SetCurrentValue(bool newValue)
{
    _currentValue = newValue;
    _currentValueIsSet = true;
}