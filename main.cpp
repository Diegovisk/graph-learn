#include "ListaAdjacencia.h"
#include <iostream>
#include <vector>
#include "MatrizAdjacencia.h"

int main(int argc, char const *argv[])
{

    ListaAdjacencia lista(6);
    lista.adicionarVertice();
    lista.adicionarAresta(0, 1, 7);
    lista.adicionarAresta(0, 3, 5);
    lista.adicionarAresta(1, 2, 8);
    lista.adicionarAresta(1, 3, 9);
    lista.adicionarAresta(1, 4, 7);
    lista.adicionarAresta(2, 4, 5);
    lista.adicionarAresta(3, 4, 15);
    lista.adicionarAresta(3, 5, 6);
    lista.adicionarAresta(4, 5, 8);
    lista.adicionarAresta(4, 6, 9);
    lista.adicionarAresta(5, 6, 11);
    lista.imprimir();
    lista.BFS(1);
    lista.DFS(1);
    lista.ordenacao_topologica();
    lista.grauVertice(2);
    lista.MTSPrim();
    lista.MTSKruskal();

    std::cout << std::endl;

    MatrizAdjacencia matriz(6);
    matriz.adicionarAresta(0, 1, 7);
    matriz.adicionarAresta(0, 3, 5);
    matriz.adicionarAresta(1, 2, 8);
    matriz.adicionarAresta(1, 3, 9);
    matriz.adicionarAresta(1, 4, 7);
    matriz.adicionarAresta(2, 4, 5);
    matriz.adicionarAresta(3, 4, 15);
    matriz.adicionarAresta(3, 5, 6);
    matriz.adicionarAresta(4, 5, 8);
    matriz.adicionarAresta(4, 6, 9);
    matriz.adicionarAresta(5, 6, 11);
    matriz.imprimir();
    matriz.BFS(1);
    matriz.DFS(1);
    matriz.ordenacao_topologica();

    matriz.grauVertice(1);
    matriz.MTSPrim();
    matriz.MTSKruskal();

    return 0;
}
