#include <iostream>
#include <fstream>
#include <sstream>

#include "../third_party/doctest.h"
#include "Graph.hpp"

std::streambuf* original_cin = nullptr;
std::ifstream input_file;

void RedirectInputStream(std::string testCase)
{   
    std::string path = "tests//Inputs//" + testCase + ".txt";

    input_file = std::ifstream(path);
    REQUIRE(input_file.is_open());

    original_cin = std::cin.rdbuf();
    std::cin.rdbuf(input_file.rdbuf());
}

void RestoreInputStream()
{
    std::cin.rdbuf(original_cin);
    input_file.close();
}

void BaseTest(std::string testCase, bool isGreedy, std::string orderedVertices = "")
{
    RedirectInputStream(testCase);

    try
    {
        Graph* graph = Graph::BuildFromIoStream();
        bool isGreedyResult = graph->IsGreedy();

        CHECK(isGreedyResult == isGreedy);

        if (isGreedy)
        {
            std::string orderedVerticesResult = graph->OrderedVertices();
            CHECK(orderedVerticesResult == orderedVertices);
        }

        delete graph;
    }
    catch(element_not_found_exception)
    {
        std::cout << "Houve uma tentativa inválida de acesso a um item da lista encadeada!" << std::endl;
        CHECK(false);
    }
    catch(invalid_orderer_option_exception)
    {
        std::cout << "O método de ordenação escolhido é inválido!" << std::endl;
        CHECK(false);
    }
    catch(unavailable_color_exception)
    {
        std::cout << "Coloração indisponível. Houve uma tentativa de atribuir uma cor indisponível a um vértice!" << std::endl;
        CHECK(false);
    }
    catch(invalid_color_change_exception)
    {
        std::cout << "Coloração inválida. Houve uma tentativa de atribuir uma cor fora do padrão a um vértice!" << std::endl;
        CHECK(false);
    }
    catch(...)
    {
        std::cout << "Houve um erro não identificado!" << std::endl;
        CHECK(false);
    }
    
    RestoreInputStream();
}

TEST_CASE("#01")
{
    BaseTest("01", true, "0 4 5 1 3 2");
}

TEST_CASE("#02")
{
    BaseTest("02", false);
}

TEST_CASE("#03")
{
    BaseTest("03", true, "0 2 1 4 3");
}

TEST_CASE("#04")
{
    BaseTest("04", false);
}

TEST_CASE("#05")
{
    BaseTest("05", true, "1 2 4 5 6 3 7 8 9 0");
}

TEST_CASE("#06")
{
    BaseTest("06", true, "0 4 5 1 3 2");
}

TEST_CASE("#07")
{
    BaseTest("07", false);
}

TEST_CASE("#08")
{
    BaseTest("08", true, "0 2 1 4 3");
}

TEST_CASE("#09")
{
    BaseTest("09", false);
}

TEST_CASE("#10")
{
    BaseTest("10", true, "0 3 1 2 4");
}

TEST_CASE("#11")
{
    BaseTest("11", false);
}

TEST_CASE("#12")
{
    BaseTest("12", false);
}

TEST_CASE("#13")
{
    BaseTest("13", false);
}

TEST_CASE("#14")
{
    BaseTest("14", true, "0 1 2 4 3");
}