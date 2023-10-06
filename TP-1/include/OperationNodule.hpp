#pragma once

#ifndef OPRATIONNODULE_HPP
#define OPRATIONNODULE_HPP

#include <string>

#include "Nodule.hpp"
#include "InputNodule.hpp"

#define OR ("|")
#define AND ("&")
#define NOT ("~")

class invalid_operation_format_exception
{};

class OperationNodule
    : public Nodule
{
    public:
        OperationNodule(std::string value);
        bool PerformOperation(InputNodule* left, InputNodule* right);
        bool PerformOperation(InputNodule* value);
        bool HasAGreaterPrecedenceThan(OperationNodule* other);
};

#endif
