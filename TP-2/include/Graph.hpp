#pragma once

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Vertex.hpp"
#include "LinkedList.hpp"

class Graph
{
    private:
        LinkedList<Vertex*>* _vertices;

    public:
        Graph();
        ~Graph();

        void AddVertex(Vertex* vertex);
        void AddEdge(Vertex* vertex1, Vertex* vertex2);

        LinkedList<Vertex*>* GetVertices();
        Vertex* GetVertex(int index);

        bool IsGreedy();
        void SetVertexColor(int index, int color);

        int VertexCount();
        int EdgeCount();

        static Graph* BuildFromIoStream();
};

#endif