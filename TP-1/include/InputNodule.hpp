#pragma once

#ifndef INPUTNODULE_HPP
#define INPUTNODULE_HPP

#include <string>

#include "Nodule.hpp"
#include "DataStructures/LinkedList.hpp"

class InputValue
{
    public:
        std::string key;
        bool value;

        InputValue();
        InputValue(std::string key, bool value);
};

class InputNodule
    : public Nodule
{
    protected:
        LinkedList<InputValue> _values;

    public:
        InputNodule();
        InputNodule(std::string value, LinkedList<InputValue> values);
        bool GetValue();
};

#endif
