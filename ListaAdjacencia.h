#ifndef _LISTA_ADJACENTE_H_
#define _LISTA_ADJACENTE_H_

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

#include "Grafo.h"

class ListaAdjacencia : public Grafo
{
private:
    std::vector<std::vector<Aresta>> adj;
    bool direcionado;
    Vertex vertices;

    void DFS_interno(Vertex v, Vertex *visitado);
    void ot_interno(Vertex v, Vertex *visitado, std::stack<Vertex> &Pilha);

public:
    ListaAdjacencia(Vertex, bool);
    ~ListaAdjacencia();
    void adicionarVertice();
    void adicionarAresta(Vertex u, Vertex v, Weight w);
    void imprimir();
    void removerAresta(Vertex u, Vertex v);
    void grauVertice(Vertex v);
    void DFS(Vertex v);
    void BFS(Vertex v);
    void ordenacao_topologica();
    void MTSPrim();
    void MTSKruskal();
    int peso(Vertex u, Vertex v);
};

ListaAdjacencia::ListaAdjacencia(Vertex v, bool direcionado = false) : vertices(v), direcionado(direcionado)
{
    this->adj.resize(v);
}

ListaAdjacencia::~ListaAdjacencia()
{
}

void ListaAdjacencia::adicionarVertice()
{
    this->adj.resize(++this->vertices);
}

void ListaAdjacencia::adicionarAresta(Vertex u, Vertex v, Weight w = 1)
{
    Aresta aresta;
    aresta.origem = u;
    aresta.destino = v;
    aresta.peso = w;
    this->adj[u].push_back(aresta);
    if (!this->direcionado && u != v)
    {
        aresta.origem = v;
        aresta.destino = u;
        this->adj[v].push_back(aresta);
    }
}

void ListaAdjacencia::imprimir()
{
    for (int i = 0; i < this->vertices; i++)
    {
        std::cout << "v[" << i << "] = ";
        for (int j = 0; j < this->adj[i].size(); j++)
        {
            std::cout << this->adj[i][j].destino << "(" << this->adj[i][j].peso << ")";
            if (j != this->adj[i].size() - 1)
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }
}

void ListaAdjacencia::removerAresta(Vertex u, Vertex v)
{
    for (int i = 0; i < this->adj[u].size(); i++)
    {
        if (this->adj[u][i].destino == v)
        {
            this->adj[u].erase(this->adj[u].begin() + i);
            break;
        }
    }

    if (!this->direcionado && u != v)
    {
        for (int i = 0; i < this->adj[v].size(); i++)
        {
            if (this->adj[v][i].destino == u)
            {
                this->adj[v].erase(this->adj[v].begin() + i);
                break;
            }
        }
    }
}

void ListaAdjacencia::grauVertice(Vertex v)
{
    if (this->direcionado)
    {
        int grau_entrada = 0;
        for (int j = 0; j < this->adj.size(); j++)
        {
            std::vector<Aresta>::iterator i;
            for (i = adj[j].begin(); i != adj[j].end(); ++i)
            {
                if (i->destino == v)
                {
                    grau_entrada++;
                }
            }
        }

        std::cout << "grau entrada: " << grau_entrada << " grau saida: " << this->adj[v].size() << std::endl;
    }
    else
    {
        std::cout << "grau vertice: " << this->adj[v].size() << std::endl;
    }
}

void ListaAdjacencia::DFS(Vertex v)
{
    Vertex *visitado = new Vertex[this->vertices + 1]();
    std::cout << "Caminho (DFS): ";
    DFS_interno(v, visitado);
    std::cout << std::endl;
    delete[] visitado;
}

void ListaAdjacencia::DFS_interno(Vertex v, Vertex *visitado)
{

    visitado[v] = 1;

    std::cout << v << " ";

    std::vector<Aresta>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visitado[i->destino])
            DFS_interno(i->destino, visitado);
}

void ListaAdjacencia::BFS(Vertex v)
{
    Vertex *visitado = new Vertex[this->vertices + 1]();

    std::list<Vertex> fila;

    visitado[v] = true;
    fila.push_back(v);

    std::vector<Aresta>::iterator i;

    std::cout << "Caminho (BFS): ";

    while (!fila.empty())
    {
        v = fila.front();
        std::cout << v << " ";
        fila.pop_front();

        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if (!visitado[i->destino])
            {
                visitado[i->destino] = true;
                fila.push_back(i->destino);
            }
        }
    }

    std::cout << std::endl;
    delete[] visitado;
}

void ListaAdjacencia::ot_interno(Vertex v, Vertex *visitado, std::stack<Vertex> &Pilha)
{
    visitado[v] = true;

    std::vector<Aresta>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visitado[i->destino])
            ot_interno(i->destino, visitado, Pilha);

    Pilha.push(v);
}

void ListaAdjacencia::ordenacao_topologica()
{
    std::stack<int> Pilha;
    Vertex *visitado = new Vertex[this->vertices + 1]();

    for (int i = 0; i < this->vertices; i++)
        if (visitado[i] == false)
            ot_interno(i, visitado, Pilha);

    std::cout << "Caminho (OT): ";
    while (Pilha.empty() == false)
    {
        std::cout << Pilha.top() << " ";
        Pilha.pop();
    }
    std::cout << std::endl;

    delete[] visitado;
}

void ListaAdjacencia::MTSPrim()
{
    bool tree[1000];
    int preco[1000];
    Vertex *pa = new Vertex[this->vertices + 1]();

    for (int i = 0; i < this->vertices; i++)
    {
        pa[i] = -1;
        tree[i] = false;
        preco[i] = INFINITY;
    }

    pa[0] = 0, tree[0] = true;

    std::vector<Aresta>::iterator i;
    for (i = adj[0].begin(); i != adj[0].end(); ++i)
    {
        pa[i->destino] = 0, preco[i->destino] = i->peso;
    }

    while (true)
    {
        int min = INFINITY;
        Vertex y;
        for (int w = 0; w < this->vertices; ++w)
        {
            if (tree[w])
                continue;
            if (preco[w] < min)
                min = preco[w], y = w;
        }
        tree[y] = true;
        if (min == INFINITY)
            break;

        for (i = adj[y].begin(); i != adj[y].end(); ++i)
        {
            Vertex w = i->destino;
            if (tree[w])
                continue;
            int cst = i->peso;
            if (cst < preco[w])
            {
                preco[w] = cst;
                pa[w] = y;
            }
        }
    }

    int sum = 0;
    ListaAdjacencia lista(this->vertices);
    for (int i = 0; i < this->vertices; i++)
    {
        int peso = this->peso(i, pa[i]);
        sum += peso;
        lista.adicionarAresta(i, pa[i], peso);
    }
    lista.removerAresta(0, 0);
    std::cout << "MST peso total " << sum << " :" << std::endl;
    lista.imprimir();
}

int ListaAdjacencia::peso(Vertex v, Vertex u)
{
    std::vector<Aresta>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (i->destino == u)
        {
            return i->peso;
        }
    }
    return 0;
}

void ListaAdjacencia::MTSKruskal()
{
    std::vector<Aresta> arestas;
    std::vector<Aresta> mst;

    int pai[this->vertices];
    int peso[10000];

    std::vector<Aresta>::iterator i;
    for (int v = 0; v < this->vertices; v++)
    {
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            arestas.push_back(*i);
        }
    }

    for (int i = 0; i <= this->vertices; i++)
    {
        pai[i] = i;
    }

    sort(arestas.begin(), arestas.end(), comp);

    int size = 0;
    for (int i = 0; i < arestas.size(); i++)
    {

        if (busca(arestas[i].origem, pai) != busca(arestas[i].destino, pai))
        { // se estiverem em componentes distintos
            uniao(arestas[i].origem, arestas[i].destino, peso, pai);

            mst.push_back(arestas[i]);
        }
    }

    ListaAdjacencia grafo(this->vertices);

    for (i = mst.begin(); i != mst.end(); ++i)
    {
        grafo.adicionarAresta(i->origem, i->destino, i->peso);
    }
    std::cout << "MTS Kruskal: " << std::endl;
    grafo.imprimir();
}

#endif