#pragma once

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "LinkedList.hpp"

#define UNDEFINED_COLOR (-1)

class invalid_color_change_exception
{};

class Vertex
{
    private:
        int _id;
        int _color;
        LinkedList<Vertex*>* _adjacentVertices;

    public:
        Vertex(int id);
        ~Vertex();

        int GetId();

        void SetColor(int color);
        int GetColor();

        void AddAdjacentVertex(Vertex* vertex);
        bool IsAdjacent(Vertex* vertex);
        LinkedList<Vertex*>* GetAdjacentVertices();

        bool IsGreedy();
};

#endif