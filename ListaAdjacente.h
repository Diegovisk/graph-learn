#ifndef _LISTA_ADJACENTE_H_
#define _LISTA_ADJACENTE_H_

#include <iostream>
#include <vector>
#include <list>

#include "Grafo.h"

class ListaAdjacente : public Grafo
{
private:
    std::vector<std::vector<Vertex> > adj;
    bool direcionado;
    Vertex vertices;

public:
    ListaAdjacente(Vertex, bool);
    ~ListaAdjacente();
    void adicionarVertice();
    void adicionarAresta(Vertex u, Vertex v, Weight w);
    void imprimir();
    void removerAresta(Vertex u, Vertex v);
    int grauVertice(Vertex v);
    void DFS(Vertex v);
    void BFS(Vertex v);
private:
    void DFS_interno(Vertex v, Vertex* visitado);
};

ListaAdjacente::ListaAdjacente(Vertex v, bool direcionado = false) : vertices(v), direcionado(direcionado)
{
    this->adj.resize(v);
}

ListaAdjacente::~ListaAdjacente()
{
}

void ListaAdjacente::adicionarVertice()
{
    this->adj.resize(++this->vertices);
}

void ListaAdjacente::adicionarAresta(Vertex u, Vertex v, Weight w = 0)
{
    this->adj[u].push_back(v);
    if (!this->direcionado && u != v)
        this->adj[v].push_back(u);
}

void ListaAdjacente::imprimir()
{
    for (int i = 0; i <= this->vertices; i++)
    {
        std::cout << "v[" << i << "] = ";
        for (int j = 0; j < this->adj[i].size(); j++)
        {
            std::cout << this->adj[i][j];
            if (j != this->adj[i].size() - 1)
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }
}

void ListaAdjacente::removerAresta(Vertex u, Vertex v)
{
    for (int i = 0; i < this->adj[u].size(); i++)
    {
        if (this->adj[u][i] == v)
        {
            this->adj[u].erase(this->adj[u].begin() + i);
            break;
        }
    }

    if (!this->direcionado && u != v)
    {
        for (int i = 0; i < this->adj[v].size(); i++)
        {
            if (this->adj[v][i] == u)
            {
                this->adj[v].erase(this->adj[v].begin() + i);
                break;
            }
        }
    }
}

int ListaAdjacente::grauVertice(Vertex v)
{
    return this->adj[v].size();
}

void ListaAdjacente::DFS(Vertex v)
{
    Vertex* visitado = new Vertex[this->vertices+1] ();
    std::cout << "Caminho: ";
    DFS_interno(v,visitado);
    std::cout << std::endl;
    delete[] visitado;
}

void ListaAdjacente::DFS_interno(Vertex v, Vertex* visitado)
{
    
    visitado[v] = 1;

    std::cout << v << " ";
    
    std::vector<Vertex>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visitado[*i]) 
            DFS_interno(*i, visitado); 
    	
}

void ListaAdjacente::BFS(Vertex v){
    Vertex* visitado = new Vertex[this->vertices+1] ();

    std::list<Vertex> fila; 
  
    visitado[v] = true; 
    fila.push_back(v); 
  
    std::vector<Vertex>::iterator i; 

    std::cout << "Caminho: ";
  
    while(!fila.empty()) 
    { 
        v = fila.front(); 
        std::cout << v << " "; 
        fila.pop_front(); 
  
        for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        { 
            if (!visitado[*i]) 
            { 
                visitado[*i] = true; 
                fila.push_back(*i); 
            } 
        } 
    } 

    std::cout << std::endl;
    delete[] visitado;
}

#endif