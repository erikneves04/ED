#pragma once

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "LinkedList.hpp"

#define UNDEFINED_COLOR (-1)

/**
 * @brief Exceção lançada quando uma é feita uma alteração inválida nas cores de um vértice.
 * Essas alterações incluem atribuir um valor menor que zero.
 */
class invalid_color_change_exception
{};

/**
 * @brief Exceção lançada quando existe uma tentativa de atribuir uma cor a um vértice que
 * já é adijacente a outro com essa mesma coloração.
 */
class unavailable_color_exception
{};

/**
 * @brief Estrutura que representa um vértice e suas dependências(como id, adjacências e coloração).
 */
class Vertex
{
    private:
        int _id;
        int _color;
        LinkedList<Vertex*>* _adjacentVertices;

    public:
        /**
         * @brief Construtor padrão da classe Vextex.
         *
         * Cria um novo vértice com dados default e um id.
         */
        Vertex(int id);

        /**
         * @brief Destrutor da classe Vextex.
         *
         * Responsável por liberar a memória alocada por esse vértice.
         */
        ~Vertex();

        /**
         * @brief Retorna o id do vértice.
         *
         * @return O identificador desse vértice.
         */
        int GetId();

        /**
         * @brief Atualiza a cor desse vértice.
         *
         * @param color A nova coloração.
         */
        void SetColor(int color);

        /**
         * @brief Retorna a cor do vértice.
         *
         * @return A coloração atual desse vértice.
         */
        int GetColor();

        /**
         * @brief Adiciona uma arestra entre o vértice atual e outro vértice.
         *
         * @param vertex O vertice de destino da arestra.
         */
        void AddAdjacentVertex(Vertex* vertex);
        
        /**
         * @brief Checa se um segundo vértice é adjacente a esse.
         *
         * @param vertex Um ponteiro pro vetor para checagem.
         * 
         * @return true caso seja adjacente, false caso contrário.
         */
        bool IsAdjacent(Vertex* vertex);
        
        /**
         * @brief Checa se um dos vértices adjancentes possui a cor especificada.
         *
         * @param color A coloração buscada.
         * 
         * @return true caso possua, false caso contrário.
         */
        bool HasAdjacentColor(int color);

        /**
         * @brief Retorna os vértices adjacentes a esse.
         * 
         * @return Um ponteiro para a lista encadeada de adjacências.
         */
        LinkedList<Vertex*>* GetAdjacentVertices();

        /**
         * @brief Checa se esse é um vértice "guloso". Ou seja, verifica se esse vértice é adjacente
         * a pelo menos um representante de todas as cores menores do que a dele.
         * 
         * @return true caso seja guloso, false caso contrário.
         */
        bool IsGreedy();

        /**
         * @brief Compara dois vértices, inicialmente com base na cor e usa o identificador como critério
         * de desempate.
         * 
         * @return true caso esse vértice seja "maior" que o outro, false caso contrário.
         */
        bool IsBiggerThan(Vertex* other);

        /**
         * @brief Compara dois vértices, inicialmente com base na cor e usa o identificador como critério
         * de desempate.
         * 
         * @return true caso esse vértice seja "menor" que o outro, false caso contrário.
         */
        bool IsLessThan(Vertex* other);

        /**
         * @brief Compara dois vértices, inicialmente com base no identificador como critério.
         * 
         * @return true caso esse vértice seja "igual" ao outro, false caso contrário.
         */
        bool Equals(Vertex* other);

        /**
         * @brief Compara dois vértices, inicialmente com base na cor e usa o identificador como critério
         * de desempate.
         * 
         * @return true caso esse vértice seja "maior ou igual" ao outro, false caso contrário.
         */
        bool IsBiggerThanOrEqual(Vertex* other);

        /**
         * @brief Compara dois vértices, inicialmente com base na cor e usa o identificador como critério
         * de desempate.
         * 
         * @return true caso esse vértice seja "menor ou igual" ao outro, false caso contrário.
         */
        bool IsLessThanOrEqual(Vertex* other);
};

#endif