#ifndef GRAPH_H
    #include <stdio.h>
    #include <stdbool.h>

    typedef struct grafo_ GRAFO;

    GRAFO* grafo_criar(int n_vertices);
    bool aresta_inserir(GRAFO* g, int a, int b, int peso);

    bool aresta_verificar(GRAFO* g, int a, int b); //verificar se existe determinada aresta no grafo
    bool aresta_remover(GRAFO* g, int a, int b);
    
    void vertices_adjacentes(GRAFO* g, int vertice); //obter array dos vertices adjacentes a determinado vertice
    int vertice_com_mais_vizinhos(GRAFO* g);

    void vertices_arestas_imprimir(GRAFO* g); //imprimir lista de vértices e lista de arestas
    void matriz_imprimir(GRAFO* g);

    bool grafo_destruir(GRAFO *g);

#endif