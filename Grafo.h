#ifndef _Grafo_H__
#define _Grafo_H__

typedef int Vertex;
typedef int Weight;

class Grafo
{

public:
    virtual void adicionarVertice() = 0;
    virtual void adicionarAresta(Vertex, Vertex, Weight) = 0;
    virtual void removerAresta(Vertex, Vertex) = 0;
    virtual int grauVertice(Vertex) = 0;
    virtual void imprimir() = 0;
    virtual void DFS(Vertex v) = 0;
    virtual void BFS(Vertex v) = 0;
    virtual void ordenacao_topologica() = 0;
protected:
    virtual void DFS_interno(Vertex v, Vertex* visitado) = 0;
    virtual void ot_interno(Vertex v, Vertex* visitado, std::stack<Vertex> &Pilha) = 0;
};

#endif