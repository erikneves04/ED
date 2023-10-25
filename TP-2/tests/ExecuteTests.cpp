#include <iostream>
#include <sstream>
#include <cassert>
#include <fstream>

#include "../third_party/doctest.h"
#include "Graph.hpp"

std::string ReadFile(std::string testCase)
{
    std::string fileName = "Inputs/" + testCase + ".txt";

    std::ifstream file(fileName);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

void RedirectInputStream(std::string testCase)
{
    std::istringstream input(ReadFile(testCase));
    std::cin.rdbuf(input.rdbuf());
}

TEST_CASE("#01")
{
    RedirectInputStream("01");

    Graph* graph = Graph::BuildFromIoStream();
    bool isGreedy = graph->IsGreedy();

    CHECK(isGreedy == true);
}

TEST_CASE("#02")
{
    RedirectInputStream("02");

    Graph* graph = Graph::BuildFromIoStream();
    bool isGreedy = graph->IsGreedy();

    CHECK(isGreedy == false);
}

TEST_CASE("#03")
{
    RedirectInputStream("03");

    Graph* graph = Graph::BuildFromIoStream();
    bool isGreedy = graph->IsGreedy();

    CHECK(isGreedy == true);
}

TEST_CASE("#04")
{
    RedirectInputStream("04");

    Graph* graph = Graph::BuildFromIoStream();
    bool isGreedy = graph->IsGreedy();

    CHECK(isGreedy == false);
}