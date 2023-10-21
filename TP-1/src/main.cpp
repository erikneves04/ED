#include <iostream>

#include "Expression.hpp"
#include "SatisfactionEvaluator.hpp"

#define SUCCESS (00)
#define FAILURE (01)

int main(int argc, char const *argv[])
{   
    // Verifica o número correto de argumentos da linha de comando.
    if (argc != 4)
    {
        std::cout << "Usage: -function -expression -input" << std::endl;

        // Encerra a execução do programa com falha.
        return FAILURE;
    }    

    // Extrai os argumentos da linha de comando.
    std::string function(argv[1]);
    std::string expressionBase(argv[2]);
    std::string input(argv[3]);

    try
    {   
        // Avalia a função especificada nos argumentos da linha de comando.
        if (function == "−a" || function == "-a")
        {
            Expression expression = Expression(expressionBase, input);
            std::cout << expression.Evaluate() << std::endl;
        }
        else if (function == "−s" || function == "-s")
        {
            SatisfactionEvaluator satisfactionEvaluator = SatisfactionEvaluator(expressionBase, input);
            bool hasSolution = satisfactionEvaluator.HasSolution();

            if (hasSolution)
                std::cout << hasSolution << " " << satisfactionEvaluator.GetSolution() << std::endl;
            else
                std::cout << hasSolution << std::endl;
        }
    }
    catch (...)
    {
        // Trata exceções e imprime uma mensagem de erro.
        std::cout << "The parameters entered are invalid." << std::endl;
        std::cout << "Function: " << function << std::endl;
        std::cout << "Expression: " << expressionBase << std::endl;
        std::cout << "Input: " << input << std::endl;

        // Encerra a execução do programa com falha.
        return FAILURE;
    }

    // Encerra a execução do programa com sucesso.
    return SUCCESS;
}