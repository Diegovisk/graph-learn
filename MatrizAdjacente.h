#ifndef _MATRIZ_ADJACENTE_H_
#define _MATRIZ_ADJACENTE_H_

#include <iostream>
#include <iomanip>

#define NUMVERTICES 100

#include "Grafo.h"

class MatrizAdjacente : public Grafo
{
private:
    bool direcionado;
    Vertex vertices;
    Weight mat[NUMVERTICES + 1][NUMVERTICES + 1];
    void DFS_interno(Vertex v, Vertex* visitado);

public:
    MatrizAdjacente(Vertex v, bool direcionado = false);
    ~MatrizAdjacente();
    void adicionarVertice();
    void adicionarAresta(Vertex u, Vertex v, Weight w);
    void imprimir();
    void removerAresta(Vertex u, Vertex v);
    int grauVertice(Vertex v);
    void DFS(Vertex v);
    void BFS(Vertex v);
};

MatrizAdjacente::MatrizAdjacente(Vertex v, bool direcionado) : vertices(v), direcionado(direcionado)
{
    for (int i = 0; i <= this->vertices; i++)
    {
        for (int j = 0; j < this->vertices; j++)
        {
            this->mat[i][j] = 0;
        }
    }
}

void MatrizAdjacente::adicionarVertice()
{
    this->vertices++;
}

void MatrizAdjacente::adicionarAresta(Vertex u, Vertex v, Weight w = 1)
{
    this->mat[u][v] = w;
    if (!this->direcionado)
        this->mat[v][u] = w;
}

void MatrizAdjacente::removerAresta(Vertex u, Vertex v)
{
    this->mat[u][v] = 0;
    if (!this->direcionado)
        this->mat[v][u] = 0;
}

int MatrizAdjacente::grauVertice(Vertex v)
{
    int sum = 0;
    for (int i = 0; i <= this->vertices; i++)
    {
        sum += this->mat[v][i];
    }
    return sum;
}

void MatrizAdjacente::imprimir()
{
    int k = 3; // largura de campo
    std::cout << "    ";
    for (int j = 0; j < this->vertices; j++)
        std::cout << std::setw(k) << j;
    std::cout << std::endl;
    for (int j = 0; j < this->vertices * k + 3; j++)
        std::cout << "-";
    std::cout << std::endl;
    for (int i = 0; i < this->vertices; i++)
    {
        std::cout << std::setw(2) << i;
        std::cout << " |";
        for (int j = 0; j < this->vertices; j++)
            std::cout << std::setw(k) << this->mat[i][j];
        std::cout << std::endl;
    }
}

MatrizAdjacente::~MatrizAdjacente()
{
}

void MatrizAdjacente::DFS(Vertex v)
{
    Vertex* visitado = new Vertex[this->vertices+1] ();
    std::cout << "Caminho: ";
    DFS_interno(v,visitado);
    delete[] visitado;
}

void MatrizAdjacente::DFS_interno(Vertex v, Vertex* visitado)
{

    visitado[v] = 1;

    std::cout << v << " ";
    
    for (int i = 0; i < this->vertices; i++) 
        if (this->mat[v][i] != 0 && !visitado[i]) 
            DFS_interno(i, visitado); 
}

void MatrizAdjacente::BFS(Vertex v)
{
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
  
        for (int i = 0; i < this->vertices; i++) 
        { 
            if (this->mat[v][i] != 0 && !visitado[i]) 
            { 
                visitado[i] = true; 
                fila.push_back(i); 
            } 
        } 
    } 

    std::cout << std::endl;
    delete[] visitado;
}

#endif