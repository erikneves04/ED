#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

typedef struct s_edge
{
    int u;
    int v;
    int custo;
} Aresta;

typedef struct s_subset
{
    int representante;
    int rank;
} Subconjunto;

class UnionFind
{
    private:
        int tamanho;
        

    public:
        Subconjunto* subconjuntos;
        UnionFind(int quantidade_subconjuntos);
        ~UnionFind();

        void Make(int x);
        int Find(int x);
        void Union(int x, int y);
};

#endif