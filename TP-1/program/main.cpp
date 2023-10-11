#include <iostream>

#include "Expression.hpp"
#include "SatisfactionEvaluator.hpp"

#define SUCCESS (00)
#define FAILURE (01)

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        std::cout << "Usage: -function -expression -input" << std::endl;
        return FAILURE;
    }    

    std::string function(argv[1]);
    std::string expressionBase(argv[2]);
    std::string input(argv[3]);

    try
    {
        if (function == "−a" || function == "-a")
        {
            Expression expression = Expression(expressionBase, input);
            std::cout << expression.Evaluate() << std::endl;
        }
    
        if (function == "−s" || function == "-s")
        {
            SatisfactionEvaluator satisfactionEvaluator = SatisfactionEvaluator(expressionBase, input);
            std::cout << satisfactionEvaluator.HasSolution() << std::endl;
        }
    }
    catch (...)
    {
        std::cout << "The parameters entered are invalid." << std::endl;
        std::cout << "Function: " << function << std::endl;
        std::cout << "Expression: " << expressionBase << std::endl;
        std::cout << "Input: " << input << std::endl;

        return FAILURE;
    }

    return SUCCESS;
}