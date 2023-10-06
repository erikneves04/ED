#pragma once

#ifndef INPUTNODULE_HPP
#define INPUTNODULE_HPP

#include <string>
#include "Nodule.hpp"

class value_not_set_exception
{};

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
        bool _currentValue;
        bool _currentValueIsSet = false;

    public:
        InputNodule();
        InputNodule(std::string value);
        InputNodule(std::string value, bool currentValue);

        bool GetCurrentValue();
        void SetCurrentValue(bool newValue);
};

#endif
