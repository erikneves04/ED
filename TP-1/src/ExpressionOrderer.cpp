#include <string>

#include "InputNodule.hpp"
#include "OperationNodule.hpp"
#include "ParenthesesNodule.hpp"
#include "ExpressionOrderer.hpp"

#include "DataStructures/Stack.hpp"
#include "DataStructures/LinkedList.hpp"

bool ExpressionOrderer::Perform(LinkedList<Nodule*> nodules)
{
    for (int i = 0; i < nodules.Length(); i++)
    {
        auto current = nodules.Get(i);
        if (current->GetType() == NoduleType::INPUT)
        {
            _inputStack.Insert((InputNodule*)current);
            continue;
        }

        if (current->GetType() == NoduleType::START_PARENTHESES)
        {
            _operationStack.Insert(current);
            continue;
        }

        if (current->GetType() == NoduleType::END_PARENTHESES)
        {
            while(_operationStack.OnTop()->GetType() != NoduleType::START_PARENTHESES)
            {
                auto operation = (OperationNodule*)_operationStack.Remove();
                auto input1 = _inputStack.Remove();
                auto input2 = _inputStack.Remove();

                auto result = operation->PerformOperation(input1, input2);
                auto resultNodule = new InputNodule("result", result);
                _inputStack.Insert(resultNodule);
            }

            _operationStack.Remove();
            continue;
        }

        if (current->GetType() == NoduleType::OPERATOR)
        {
            auto thisOp = (OperationNodule*)current;

            while(!_operationStack.Empty() && ((OperationNodule*)_operationStack.OnTop())->HasAGreaterPrecedenceThan(thisOp))
            {
                auto currentOperation = (OperationNodule*)_operationStack.Remove();

                if (currentOperation->GetValue() == NOT)
                {
                    auto input = _inputStack.Remove();
                    auto result = currentOperation->PerformOperation(input);
                    auto resultNodule = new InputNodule("result", result);
                    _inputStack.Insert(resultNodule);
                }
                else
                {
                    auto input1 = _inputStack.Remove();
                    auto input2 = _inputStack.Remove();

                    auto result = currentOperation->PerformOperation(input1, input2);
                    auto resultNodule = new InputNodule("result", result);

                    _inputStack.Insert(resultNodule);
                }
            }

            _operationStack.Insert(current);
        }
    }

    while(!_operationStack.Empty())
    {
        auto currentOperation = (OperationNodule*)_operationStack.Remove();

        if (currentOperation->GetValue() == NOT)
        {
            auto input = _inputStack.Remove();
            auto result = currentOperation->PerformOperation(input);
            auto resultNodule = new InputNodule("result", result);
            _inputStack.Insert(resultNodule);
        }
        else
        {
            auto input1 = _inputStack.Remove();
            auto input2 = _inputStack.Remove();

            auto result = currentOperation->PerformOperation(input1, input2);
            auto resultNodule = new InputNodule("result", result);

            _inputStack.Insert(resultNodule);
        }
    }

    auto lastValue = _inputStack.Remove();
    return lastValue->GetCurrentValue();
}