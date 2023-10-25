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

void Graph::AddEdge(Vertex* vertex1, Vertex* vertex2)
{
    vertex1->AddAdjacentVertex(vertex2);
    vertex2->AddAdjacentVertex(vertex1);
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
    int verticesCount, edgesCount, vertex1, vertex2, color;

    std::cin >> verticesCount;

    Graph* graph = new Graph();

    for(int i = 0; i < verticesCount; i++)
    {
        graph->AddVertex(new Vertex(i));
    }

    for(int i = 0; i < verticesCount; i++)
    {
        std::cin >> edgesCount;

        for(int j = 0; j < edgesCount; j++)
        {
            std::cin >> vertex1;
            std::cin >> vertex2;

            graph->AddEdge(graph->GetVertex(vertex1), graph->GetVertex(vertex2));
        }
    }

    for(int i = 0; i < verticesCount; i++)
    {
        std::cin >> color;
        graph->SetVertexColor(i, color);
    }

    return graph;
}