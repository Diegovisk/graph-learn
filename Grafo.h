#ifndef _Grafo_H__
#define _Grafo_H__

typedef int Vertex;
typedef int Weight;
#define INFINITY 100000000

struct Aresta
{
    Vertex origem;
    Vertex destino;
    Weight peso;
};

bool comp(Aresta a, Aresta b) { return a.peso < b.peso; }

class Grafo
{

public:
    virtual void adicionarVertice() = 0;
    virtual void adicionarAresta(Vertex, Vertex, Weight) = 0;
    virtual void removerAresta(Vertex, Vertex) = 0;
    virtual void grauVertice(Vertex) = 0;
    virtual void imprimir() = 0;
    virtual void DFS(Vertex v) = 0;
    virtual void BFS(Vertex v) = 0;
    virtual void ordenacao_topologica() = 0;
    virtual void MTSPrim() = 0;
    virtual void MTSKruskal() = 0;

protected:
    virtual void DFS_interno(Vertex v, Vertex *visitado) = 0;
    virtual void ot_interno(Vertex v, Vertex *visitado, std::stack<Vertex> &Pilha) = 0;
    int busca(Vertex x, Vertex *pai);
    void uniao(Vertex a, Vertex b, Weight *peso, Vertex *pai);
};

int Grafo::busca(Vertex x, Vertex *pai)
{
    if (pai[x] == x)
        return x;
    return pai[x] = busca(pai[x], pai);
}

void Grafo::uniao(Vertex a, Vertex b, Weight *peso, Vertex *pai)
{

    a = busca(a, pai);
    b = busca(b, pai);

    if (peso[a] < peso[b])
        pai[a] = b;
    else if (peso[b] < peso[a])
        pai[b] = a;
    else
    {
        pai[a] = b;
        peso[b]++;
    }
}

#endif