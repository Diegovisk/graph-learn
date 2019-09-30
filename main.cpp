#include "ListaAdjacente.h"
#include <iostream>
#include <vector>
#include "MatrizAdjacente.h"

int main(int argc, char const *argv[])
{
    MatrizAdjacente matriz(5);
    matriz.adicionarVertice();
    matriz.adicionarAresta(1, 2);
    matriz.adicionarAresta(2, 2);
    matriz.adicionarAresta(2, 4);
    matriz.adicionarAresta(1, 3);
    matriz.adicionarAresta(1, 5);
    matriz.adicionarAresta(5, 0);
    matriz.imprimir();
    matriz.DFS(1);

    std::cout << std::endl;

    ListaAdjacente lista(4);
    lista.adicionarVertice();
    lista.adicionarAresta(1, 2);
    lista.adicionarAresta(2, 2);
    lista.adicionarAresta(2, 4);
    lista.adicionarAresta(1, 3);
    lista.adicionarAresta(1, 5);
    lista.adicionarAresta(5, 0);
    // lista.removerAresta(2, 2);
    lista.imprimir();
    lista.DFS(1);

    return 0;
}
