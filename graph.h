#ifndef GRAPH_H
    #include <stdio.h>
    #include <stdbool.h>

    typedef struct grafo_ GRAFO;
    typedef struct aresta_ ARESTA;

    GRAFO* grafo_criar(int n_vertices);
    ARESTA* aresta_inserir(GRAFO* g, int a, int b, int peso);

    bool aresta_verificar(); //verificar se existe determinada aresta no grafo
    bool aresta_remover();
    ARESTA aresta_menor_obter(); //obter aresta de menor peso do grafo
    
    void vertice_adjacentes(); //obter lista dos vertices adjacentes a determinado vertice
    int vertice_total(); //obter o número total de vértices do grafo
    
    GRAFO transposto_obter(); //obter o transposto de um grafo direcionado
    void grafo_imprimir();


#endif