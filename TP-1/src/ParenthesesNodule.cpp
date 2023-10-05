#include "ParenthesesNodule.hpp"

ParenthesesNodule::ParenthesesNodule(std::string value, NoduleType type)
    : Nodule(value, type)
{
    _end = nullptr;
}