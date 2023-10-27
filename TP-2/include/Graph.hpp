#pragma once

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>

#include "Vertex.hpp"
#include "LinkedList.hpp"
#include "GraphOrderer.hpp"

/**
 * @brief Estrutura que representa um grafo, e suas dependências(como vértices e demais propriedades).
 */
class Graph
{
    private:
        LinkedList<Vertex*>* _vertices;
        GraphOrderer* _orderer;

    public:
        /**
         * @brief Construtor padrão da classe Graph.
         * @param sortOption Caracter que define o método de ordenação a ser utilizado.
         */
        Graph(char sortOption);

        /**
         * @brief Destrutor responsável por liberar a memória alocada por um grafo.
        */
        ~Graph();

        /**
         * @brief Adiciona um novo vértice a esse grafo.
         *
         * @param vertex Um ponteiro para o novo vértice.
         */
        void AddVertex(Vertex* vertex);

        /**
         * @brief Adiciona ama arestra entre dois vértices do grafo.
         *
         * @param vertex1 Um ponteiro para o primeiro vértice.
         * @param vertex2 Um ponteiro para o segundo vértice.
         */
        void AddEdge(Vertex* vertex1, Vertex* vertex2);

        /**
         * @brief Retorna os vértices pertencentes a esse grafo.
         * 
         * @return Um ponteiro para a lista encadeada com os vértices.
         */
        LinkedList<Vertex*>* GetVertices();

        /**
         * @brief Retorna o vértice na posição especificada.
         * 
         * @param index Posição buscada.
         * 
         * @return Um ponteiro para o vértice buscado.
         */
        Vertex* GetVertex(int index);

        /**
         * @brief Checa se esse grafo é "guloso". Ou seja, todos os vértices possuem conexão
         * com todas as cores menores que a própria coloração.
         * 
         * @return true caso seja "guloso", false caso contrário.
         */
        bool IsGreedy();

        /**
         * @brief Retorna uma string com os vértices ordenados de acordo com o método de ordenação selecionado.
         * 
         * @return Uma string com os vértices ordenados.
        */
        std::string OrderedVertices();

        /**
         * @brief Atualiza a coloração de um determinado vértice do grafo.
         *
         * @param index Posição alvo.
         * @param color Nova coloração.
         */
        void SetVertexColor(int index, int color);

        /**
         * @brief Conta os vértices desse grafo.
         *
         * @return O número de vértices presentes.
         */
        int VertexCount();

        /**
         * @brief Conta as arestras de todos os vértices desse grafo.
         *
         * @return O número de arestras presentes.
         */
        int EdgeCount();

        /**
         * @brief Constrói um grafo com base nas informações fornecidas pela entrada padrão, 
         * seguindo a estrutura da documentação provida.
         *
         * @return Um ponteiro para o vértice com as novas informações.
         */
        static Graph* BuildFromIoStream();

        /**
         * @brief Imprime as informações do grafo na saída padrão.
         */
        void Print();
};

#endif