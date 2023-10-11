#pragma once

#ifndef INPUTEXCHANGER_HPP
#define INPUTEXCHANGER_HPP

#include <string>

#include "InputNodule.hpp"
#include "DataStructures/Queue.hpp"
#include "DataStructures/LinkedList.hpp"

class InputExchanger
{
    private:
        std::string _input;
        LinkedList<int> _variablesIndex;

        bool HasVariableForIndex(int index);
        LinkedList<std::string> GenerateBinaryCombinations(int bitsCount);
    public:
        InputExchanger(std::string input, LinkedList<int> variablesIndex);
        Queue<LinkedList<InputValue>*>* GetAllInputsCombination();
};

#endif
