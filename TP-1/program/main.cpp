#define SUCCESS (00)

#include "DataStructures/LinkedList.hpp"
#include "DataStructures/Stack.hpp"
#include "DataStructures/Queue.hpp"

#include "Expression.hpp"
#include "InputNodule.hpp"

#include <iostream>

int main(int argc, char const *argv[])
{
    Expression expression = Expression("~ ( 0 | 1 ) & 2");

    LinkedList<InputValue>* values = new LinkedList<InputValue>();

    values->Insert(InputValue("0", true));
    values->Insert(InputValue("1", false));
    values->Insert(InputValue("2", true));

    std::cout << expression.Evaluate(values) << std::endl;

    return SUCCESS;
}