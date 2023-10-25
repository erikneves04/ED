#pragma once

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>

#include "Vertex.hpp"
#include "LinkedList.hpp"
#include "GraphOrderer.hpp"

class Graph
{
    private:
        LinkedList<Vertex*>* _vertices;
        GraphOrderer* _orderer;

    public:
        Graph(char sortOption);
        ~Graph();

        void AddVertex(Vertex* vertex);
        void AddEdge(Vertex* vertex1, Vertex* vertex2);

        LinkedList<Vertex*>* GetVertices();
        Vertex* GetVertex(int index);

        bool IsGreedy();
        std::string OrderedVertices();

        void SetVertexColor(int index, int color);

        int VertexCount();
        int EdgeCount();

        static Graph* BuildFromIoStream();

        void Print();
};

#endif