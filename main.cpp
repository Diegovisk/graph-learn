#include "ListaAdjacencia.h"
#include <iostream>
#include <vector>
#include "MatrizAdjacencia.h"

int main(int argc, char const *argv[])
{

    ListaAdjacencia lista(4);
    lista.adicionarVertice();
    lista.adicionarAresta(1, 2);
    lista.adicionarAresta(2, 2);
    lista.adicionarAresta(2, 4);
    lista.adicionarAresta(1, 3);
    lista.adicionarAresta(1, 5);
    lista.adicionarAresta(5, 0);
    // lista.removerAresta(2, 2);
    lista.imprimir();
    lista.BFS(1);
    lista.DFS(1);
    lista.ordenacao_topologica();

    std::cout << std::endl;

    MatrizAdjacencia matriz(5);
    matriz.adicionarVertice();
    matriz.adicionarAresta(1, 2);
    matriz.adicionarAresta(2, 2);
    matriz.adicionarAresta(2, 4);
    matriz.adicionarAresta(1, 3);
    matriz.adicionarAresta(1, 5);
    matriz.adicionarAresta(5, 0);
    matriz.imprimir();
    matriz.BFS(1);
    matriz.DFS(1);
    matriz.ordenacao_topologica();

    return 0;
}
