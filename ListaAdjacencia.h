#ifndef _LISTA_ADJACENTE_H_
#define _LISTA_ADJACENTE_H_

#include <iostream>
#include <vector>
#include <list>
#include <stack>

#include "Grafo.h"

struct Aresta
{
    Vertex destino;
    Weight peso;
};

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
    aresta.destino = v;
    aresta.peso = w;
    this->adj[u].push_back(aresta);
    if (!this->direcionado && u != v)
    {
        aresta.destino = u;
        this->adj[v].push_back(aresta);
    }
}

void ListaAdjacencia::imprimir()
{
    for (int i = 0; i <= this->vertices; i++)
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

#endif