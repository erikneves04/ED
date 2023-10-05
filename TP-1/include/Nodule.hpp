#pragma once

#ifndef NODULE_HPP
#define NODULE_HPP

#include <string>

enum class NoduleType
{
    INPUT,
    OPERATOR,
    START_PARENTHESES,
    END_PARENTHESES
};

class Nodule
{
    protected:
        NoduleType _type;
        std::string _value;

    public:
        Nodule();
        Nodule(std::string value, NoduleType type);

        NoduleType GetType();
        std::string GetValue();
};

#endif
