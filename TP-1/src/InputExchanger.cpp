#include <string>

#include "InputNodule.hpp"
#include "InputExchanger.hpp"

#include "DataStructures/Queue.hpp"
#include "DataStructures/LinkedList.hpp"

InputExchanger::InputExchanger(std::string input)
{
    _input = input;
    SetupVariablesIndex();
}

Queue<LinkedList<InputValue>*> InputExchanger::GetAllInputsCombination()
{
    Queue<LinkedList<InputValue>*> queue;
    LinkedList<std::string> combinations = GenerateBinaryCombinations(_variablesIndex.Length());

    for(int i = 0; i < combinations.Length(); i++)
    {
        LinkedList<InputValue>* input = new LinkedList<InputValue>();
        
        int currentCombinationIndex = 0;
        std::string currentCombination = combinations.Get(i);

        for(int j = 0; j < _input.length(); j++)
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
                std::string index = std::to_string(i);
                std::string value(1, _input[j]);

                input->Insert(InputValue(index, value == "1"));
            }
        }
        queue.Insert(input);
    }
    
    return queue;
}

void InputExchanger::SetupVariablesIndex()
{
    for (int i = 0; i < _input.length(); i++)
    {
        std::string input(1, _input[i]);
        if (input == EXISTS || input == FOR_ALL)
            _variablesIndex.Insert(i);
    } 
}

bool InputExchanger::HasVariableForIndex(int index)
{
    for (int i = 0; i < _variablesIndex.Length(); i++)
    {
        if (_variablesIndex.Get(i) == index)
            return true;
    }

    return false;
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