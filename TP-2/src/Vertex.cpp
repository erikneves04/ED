#include "Vertex.hpp"

Vertex::Vertex(int id)
{
    _id = id;
    _color = UNDEFINED_COLOR;

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
    if (_color == UNDEFINED_COLOR)
        return false;

    if (_color == 1)
        return true;

    if (_adjacentVertices->Empty())
        return false;

    bool* expectedColors = new bool[_color - 1];

    for(int i = 0; i < _adjacentVertices->Length(); i++)
    {
        Vertex* current = _adjacentVertices->Get(i);

        if (current->GetColor() == UNDEFINED_COLOR || current->GetColor() >= _color)
            continue;

        expectedColors[current->GetColor()] = true;
    }

    for(int i = 1; i < _color; i++)
    {
        if (!expectedColors[i])
        {
            delete[] expectedColors;
            return false;
        }
    }

    delete[] expectedColors;
    return true;
}

bool Vertex::operator>(const Vertex& other)
{
    if (other._color == _color)
        return _id > other._id;

    return _color > other._color;
}