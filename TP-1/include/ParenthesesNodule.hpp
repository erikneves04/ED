#pragma once

#ifndef PARENTHESESNODULE_HPP
#define PARENTHESESNODULE_HPP

#include <string>

#include "Nodule.hpp"

class ParenthesesNodule
    : public Nodule
{
    public:
        ParenthesesNodule* _end;
        ParenthesesNodule(std::string value, NoduleType type);
};

#endif
