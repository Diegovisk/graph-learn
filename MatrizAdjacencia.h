#ifndef _MATRIZ_ADJACENTE_H_
#define _MATRIZ_ADJACENTE_H_

#include <iostream>
#include <iomanip>
#include <list>
#include <stack>

#define NUMVERTICES 100

#include "Grafo.h"

class MatrizAdjacencia : public Grafo
{
private:
    bool direcionado;
    Vertex vertices;
    Weight mat[NUMVERTICES + 1][NUMVERTICES + 1];

    void DFS_interno(Vertex v, Vertex *visitado);
    void ot_interno(Vertex v, Vertex *visitado, std::stack<Vertex> &Pilha);

public:
    MatrizAdjacencia(Vertex v, bool direcionado = false);
    ~MatrizAdjacencia();
    void adicionarVertice();
    void adicionarAresta(Vertex u, Vertex v, Weight w);
    void imprimir();
    void removerAresta(Vertex u, Vertex v);
    void grauVertice(Vertex v);
    void DFS(Vertex v);
    void BFS(Vertex v);
    void ordenacao_topologica();
    void MTSPrim();
};

MatrizAdjacencia::MatrizAdjacencia(Vertex v, bool direcionado) : vertices(v), direcionado(direcionado)
{
    for (int i = 0; i < this->vertices; i++)
    {
        for (int j = 0; j < this->vertices; j++)
        {
            this->mat[i][j] = 0;
        }
    }
}

void MatrizAdjacencia::adicionarVertice()
{
    this->vertices++;
}

void MatrizAdjacencia::adicionarAresta(Vertex u, Vertex v, Weight w = 1)
{
    this->mat[u][v] = w;
    if (!this->direcionado)
        this->mat[v][u] = w;
}

void MatrizAdjacencia::removerAresta(Vertex u, Vertex v)
{
    this->mat[u][v] = 0;
    if (!this->direcionado)
        this->mat[v][u] = 0;
}

void MatrizAdjacencia::grauVertice(Vertex v)
{
    if (this->direcionado)
    {
        int grau_saida = 0;
        for (int i = 0; i < this->vertices; i++)
        {
            grau_saida += (this->mat[v][i] > 0 ? 1 : 0);
        }

        int grau_entrada = 0;
        for (int i = 0; i < this->vertices; i++)
        {
            grau_entrada += (this->mat[i][v] > 0 ? 1 : 0);
        }

        std::cout << "grau entrada: " << grau_entrada << " | grau saida: " << grau_saida << std::endl;
    }
    else
    {

        int sum = 0;
        for (int i = 0; i < this->vertices; i++)
        {
            sum += (this->mat[v][i] > 0 ? 1 : 0);
        }

        std::cout << "grau vertice: " << sum << std::endl;
    }
}

void MatrizAdjacencia::imprimir()
{
    int k = 3; // largura de campo
    std::cout << "    ";
    for (int j = 0; j <= this->vertices; j++)
        std::cout << std::setw(k) << j;
    std::cout << std::endl;
    for (int j = 0; j <= this->vertices * k + 6; j++)
        std::cout << "-";
    std::cout << std::endl;
    for (int i = 0; i <= this->vertices; i++)
    {
        std::cout << std::setw(2) << i;
        std::cout << " |";
        for (int j = 0; j <= this->vertices; j++)
            std::cout << std::setw(k) << this->mat[i][j];
        std::cout << std::endl;
    }
}

MatrizAdjacencia::~MatrizAdjacencia()
{
}

void MatrizAdjacencia::DFS(Vertex v)
{
    Vertex *visitado = new Vertex[this->vertices + 1]();
    std::cout << "Caminho (DFS): ";
    DFS_interno(v, visitado);
    std::cout << std::endl;
    delete[] visitado;
}

void MatrizAdjacencia::DFS_interno(Vertex v, Vertex *visitado)
{

    visitado[v] = 1;

    std::cout << v << " ";

    for (int i = 0; i < this->vertices; i++)
        if (this->mat[v][i] != 0 && !visitado[i])
            DFS_interno(i, visitado);
}

void MatrizAdjacencia::BFS(Vertex v)
{
    Vertex *visitado = new Vertex[this->vertices + 1]();

    std::list<Vertex> fila;

    visitado[v] = true;
    fila.push_back(v);

    std::cout << "Caminho (BFS): ";

    while (!fila.empty())
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

void MatrizAdjacencia::ot_interno(Vertex v, Vertex *visitado, std::stack<Vertex> &Pilha)
{
    visitado[v] = true;

    for (int i = 0; i < this->vertices; i++)
        if (this->mat[v][i] != 0 && !visitado[i])
            ot_interno(i, visitado, Pilha);

    Pilha.push(v);
}

void MatrizAdjacencia::ordenacao_topologica()
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

void MatrizAdjacencia::MTSPrim()
{
    bool tree[1000];
    int preco[1000];

    Vertex *pa = new Vertex[this->vertices + 1]();

    for (int i = 0; i <= this->vertices; i++)
    {
        pa[i] = -1;
        tree[i] = false;
        preco[i] = INFINITY;
    }

    pa[0] = 0, tree[0] = true;

    for (int i = 0; i <= this->vertices; ++i)
    {
        if (this->mat[0][i] > 0)
        {
            pa[i] = 0, preco[i] = this->mat[0][i];
        }
    }

    while (true)
    {
        int min = INFINITY;
        Vertex y;
        for (int w = 0; w <= this->vertices; ++w)
        {
            if (tree[w])
                continue;
            if (preco[w] < min)
                min = preco[w], y = w;
        }
        tree[y] = true;
        if (min == INFINITY)
            break;

        for (int i = 0; i <= this->vertices; i++)
        {
            if (this->mat[y][i] > 0)
            {
                Vertex w = i;
                if (tree[w])
                    continue;
                int cst = this->mat[y][i];
                if (cst < preco[w])
                {
                    preco[w] = cst;
                    pa[w] = y;
                }
            }
        }
    }

    int sum = 0;
    MatrizAdjacencia grafo(this->vertices);
    for (int i = 0; i <= this->vertices; i++)
    {
        int peso = this->mat[i][pa[i]];
        sum += peso;
        grafo.adicionarAresta(i, pa[i], peso);
    }

    std::cout << "MST peso total " << sum << " :" << std::endl;
    grafo.imprimir();
}

#endif