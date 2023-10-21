#include <string>

#include "InputNodule.hpp"
#include "InputExchanger.hpp"

#include "DataStructures/Queue.hpp"
#include "DataStructures/LinkedList.hpp"

InputExchanger::InputExchanger(std::string input, LinkedList<int>* variablesIndex)
{
    _input = input;
    _variablesIndex = variablesIndex;
}

bool InputExchanger::HasVariableForIndex(int index)
{
    for (int i = 0; i < _variablesIndex->Length(); i++)
    {
        if (_variablesIndex->Get(i) == index)
            return true;
    }

    return false;
}

Queue<LinkedList<InputValue>*>* InputExchanger::GetAllInputsCombination()
{
    Queue<LinkedList<InputValue>*>* queue = new Queue<LinkedList<InputValue>*>();
    LinkedList<std::string> combinations = GenerateBinaryCombinations(_variablesIndex->Length());

    for(int i = 0; i < combinations.Length(); i++)
    {
        LinkedList<InputValue>* input = new LinkedList<InputValue>();
        
        int currentCombinationIndex = 0;
        std::string currentCombination = combinations.Get(i);
        for(size_t j = 0; j < _input.length(); j++)
        {
            if (HasVariableForIndex(j))
            {
                std::string index = std::to_string(j);
                std::string value(1, currentCombination[currentCombinationIndex]);
                input->Insert(InputValue(index, value == "1"));

                currentCombinationIndex++;
            }
            else
            {
                std::string index = std::to_string(j);
                std::string value(1, _input[j]);

                input->Insert(InputValue(index, value == "1"));
            }
        }
        queue->Insert(input);
    }
    
    return queue;
}

LinkedList<std::string> InputExchanger::GenerateBinaryCombinations(int bitsCount) 
{
    LinkedList<std::string> combinations;
    int maxCombinations = 1 << bitsCount; 

    for (int i = 0; i < maxCombinations; i++) 
    {
        std::string binaryString;
        for (int j = bitsCount - 1; j >= 0; j--) 
        {
            char bit = ((i >> j) & 1) ? '1' : '0';
            binaryString += bit;
        }
        combinations.Insert(binaryString);
    }

    return combinations;
}