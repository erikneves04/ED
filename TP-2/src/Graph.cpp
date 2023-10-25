#include <iostream>

#include "Graph.hpp"
#include "Vertex.hpp"
#include "LinkedList.hpp"

Graph::Graph()
{
    _vertices = new LinkedList<Vertex*>();
}

Graph::~Graph()
{
    delete _vertices;
}

void Graph::AddVertex(Vertex* vertex)
{
    _vertices->Insert(vertex);
}

void Graph::AddEdge(Vertex* origin, Vertex* destiny)
{
    origin->AddAdjacentVertex(destiny);
}

LinkedList<Vertex*>* Graph::GetVertices()
{
    return _vertices;
}

Vertex* Graph::GetVertex(int index)
{
    return _vertices->Get(index);
}

bool Graph::IsGreedy()
{
    for (int i = 0; i < _vertices->Length(); i++)
    {
        if (!_vertices->Get(i)->IsGreedy())
            return false;
    }

    return true;
}

void Graph::SetVertexColor(int index, int color)
{
    _vertices->Get(index)->SetColor(color);
}

int Graph::VertexCount()
{
    return _vertices->Length();
}

int Graph::EdgeCount()
{
    int count = 0;

    for (int i = 0; i < _vertices->Length(); i++)
    {
        count += _vertices->Get(i)->GetAdjacentVertices()->Length();
    }

    return count / 2;
}

Graph* Graph::BuildFromIoStream()
{
    int verticesCount, edgesCount, id, color;

    std::cin >> verticesCount;

    Graph* graph = new Graph();

    for(int i = 0; i < verticesCount; i++)
    {
        graph->AddVertex(new Vertex(i));
    }

    for(int i = 0; i < verticesCount; i++)
    {
        std::cin >> edgesCount;

        Vertex* origin = graph->GetVertex(i);
        for(int j = 0; j < edgesCount; j++)
        {
            std::cin >> id;
            Vertex* destiny = graph->GetVertex(id);
            graph->AddEdge(origin, destiny);
        }
    }

    for(int i = 0; i < verticesCount; i++)
    {
        std::cin >> color;
        graph->SetVertexColor(i, color);
    }

    return graph;
}

void Graph::Print()
{
    for(int i = 0; i < _vertices->Length(); i++)
    {
        Vertex* current = _vertices->Get(i);

        std::cout << "Vertex " << current->GetId() << " color: " << current->GetColor() << std::endl;

        for(int j = 0; j < current->GetAdjacentVertices()->Length(); j++)
        {
            std::cout << "    Adjacent vertex " << current->GetAdjacentVertices()->Get(j)->GetId() << std::endl;
        }
        std::cout << "    Is greedy: " << current->IsGreedy() << std::endl;
    }
}