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

InputNodule::InputNodule(std::string value, LinkedList<InputValue> values)
    : Nodule(value, NoduleType::INPUT)
{
    _values = values;
}

bool InputNodule::GetValue()
{
    for (int i = 0; i < _values.Length(); i++)
    {
        auto current = _values.Get(i);
        if (current.key == _value)
        {
            return current.value;
        }
    }
    return false;
}