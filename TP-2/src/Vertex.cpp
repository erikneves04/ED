#include "Vertex.hpp"

Vertex::Vertex(int id)
{
    _id = id;
    _color = -1;

    _adjacentVertices = new LinkedList<Vertex*>();
}

Vertex::~Vertex()
{
    delete _adjacentVertices;
}

int Vertex::GetId()
{
    return _id;
}

void Vertex::SetColor(int color)
{
    if (color < 0 || _color != -1)
        throw invalid_color_change_exception();

    _color = color;
}

int Vertex::GetColor()
{
    return _color;
}

void Vertex::AddAdjacentVertex(Vertex* vertex)
{
    if (IsAdjacent(vertex))
        return;

    _adjacentVertices->Insert(vertex);
}

bool Vertex::IsAdjacent(Vertex* vertex)
{
    return _adjacentVertices->Contains(vertex);
}

LinkedList<Vertex*>* Vertex::GetAdjacentVertices()
{
    return _adjacentVertices;
}

bool Vertex::IsGreedy()
{
    if (_color == -1)
        return false;

    if (_color == 0)
        return true;

    if (_adjacentVertices->Empty() == 0)
        return false;

    bool* expectedColors = new bool[_color];

    for(int i = 0; i < _adjacentVertices->Length(); i++)
    {
        Vertex* current = _adjacentVertices->Get(i);

        if (current->GetColor() == -1 || current->GetColor() >= _color)
            continue;

        expectedColors[current->GetColor()] = true;
    }

    for(int i = 0; i < _color; i++)
    {
        if (expectedColors[i] == false)
            return false;
    }

    return true;
}