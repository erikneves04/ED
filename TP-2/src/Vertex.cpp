#include "Vertex.hpp"

Vertex::Vertex(int id)
{
    _id = id;
    _color = UNDEFINED_COLOR;

    _adjacentVertices = new LinkedList<Vertex*>();//id + 1);
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
    if (color < 0 || _color != UNDEFINED_COLOR)
        throw invalid_color_change_exception();

    if (HasAdjacentColor(color))
        throw unavailable_color_exception();        

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

bool Vertex::HasAdjacentColor(int color)
{
    for(int i = 0; i < _adjacentVertices->Length(); i++)
    {
        if (_adjacentVertices->Get(i)->GetColor() == color)
            return true;
    }

    return false;
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
    if (_color == 1)
        return true;

    if (_color == UNDEFINED_COLOR || _adjacentVertices->Empty())
        return false;

    unsigned int colorCount = _color - 1;    

    if ((unsigned int)_adjacentVertices->Length() < colorCount)
        return false;

    bool* expectedColors = new bool[colorCount];

    for(int i = 0; i < _adjacentVertices->Length(); i++)
    {
        Vertex* current = _adjacentVertices->Get(i);

        if (current->GetColor() == UNDEFINED_COLOR || current->GetColor() >= _color)
            continue;

        expectedColors[current->GetColor() - 1] = true;
    }

    for(unsigned int i = 0; i < colorCount; i++)
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

bool Vertex::IsBiggerThan(Vertex* other)
{
    if (other->_color == _color)
        return _id > other->_id;

    return _color > other->_color;
}

bool Vertex::IsLessThan(Vertex* other)
{
    return !IsBiggerThan(other);
}

bool Vertex::Equals(Vertex* other)
{
    return _id == other->_id;
}

bool Vertex::IsBiggerThanOrEqual(Vertex* other)
{
    return IsBiggerThan(other) || Equals(other);
}

bool Vertex::IsLessThanOrEqual(Vertex* other)
{
    return IsLessThan(other) || Equals(other);
}