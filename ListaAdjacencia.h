#ifndef _LISTA_ADJACENTE_H_
#define _LISTA_ADJACENTE_H_

#include <iostream>
#include <vector>
#include <list>
#include <stack>

#include "Grafo.h"

class ListaAdjacencia : public Grafo
{
private:
    std::vector<std::vector<Vertex> > adj;
    bool direcionado;
    Vertex vertices;
    
    void DFS_interno(Vertex v, Vertex* visitado);
    void ot_interno(Vertex v, Vertex* visitado, std::stack<Vertex> &Pilha);

public:
    ListaAdjacencia(Vertex, bool);
    ~ListaAdjacencia();
    void adicionarVertice();
    void adicionarAresta(Vertex u, Vertex v, Weight w);
    void imprimir();
    void removerAresta(Vertex u, Vertex v);
    int grauVertice(Vertex v);
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

void ListaAdjacencia::adicionarAresta(Vertex u, Vertex v, Weight w = 0)
{
    this->adj[u].push_back(v);
    if (!this->direcionado && u != v)
        this->adj[v].push_back(u);
}

void ListaAdjacencia::imprimir()
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

void ListaAdjacencia::removerAresta(Vertex u, Vertex v)
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

int ListaAdjacencia::grauVertice(Vertex v)
{
    return this->adj[v].size();
}

void ListaAdjacencia::DFS(Vertex v)
{
    Vertex* visitado = new Vertex[this->vertices+1] ();
    std::cout << "Caminho (DFS): ";
    DFS_interno(v,visitado);
    std::cout << std::endl;
    delete[] visitado;
}

void ListaAdjacencia::DFS_interno(Vertex v, Vertex* visitado)
{
    
    visitado[v] = 1;

    std::cout << v << " ";
    
    std::vector<Vertex>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visitado[*i]) 
            DFS_interno(*i, visitado); 
    	
}

void ListaAdjacencia::BFS(Vertex v)
{
    Vertex* visitado = new Vertex[this->vertices+1] ();

    std::list<Vertex> fila; 
  
    visitado[v] = true; 
    fila.push_back(v); 
  
    std::vector<Vertex>::iterator i; 

    std::cout << "Caminho (BFS): ";
  
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

void ListaAdjacencia::ot_interno(Vertex v, Vertex* visitado, std::stack<Vertex> &Pilha) 
{ 
    visitado[v] = true; 
  
    std::vector<Vertex>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visitado[*i]) 
            ot_interno(*i, visitado, Pilha); 
  
    Pilha.push(v); 
} 
  
void ListaAdjacencia::ordenacao_topologica() 
{ 
    std::stack<int> Pilha; 
    Vertex* visitado = new Vertex[this->vertices+1] ();    
  
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