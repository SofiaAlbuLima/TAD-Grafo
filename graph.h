#ifndef GRAPH_H
    #include <stdio.h>
    #include <stdbool.h>

    typedef struct grafo_ GRAFO;

    GRAFO* grafo_criar(int n_vertices);
    bool aresta_inserir(GRAFO* g, int a, int b, int peso);

    bool aresta_verificar(GRAFO* g, int a, int b); //verificar se existe determinada aresta no grafo
    bool aresta_remover(GRAFO* g, int a, int b);
    
    void vertice_adjacentes(GRAFO* g, int vertice); //obter lista dos vertices adjacentes a determinado vertice
    int vertice_total(); //obter o número total de vértices do grafo
    
    GRAFO transposto_obter(); //obter o transposto de um grafo direcionado
    void grafo_imprimir();


#endif