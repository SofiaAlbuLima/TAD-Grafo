#ifndef GRAPH_H
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>

    typedef struct grafo_ GRAFO;

    GRAFO* grafo_criar(int n_vertices);

    bool aresta_inserir(GRAFO* g, int a, int b, int peso);
    bool aresta_verificar(GRAFO* g, int a, int b); //verificar se existe determinada aresta no grafo
    bool aresta_remover(GRAFO* g, int a, int b);
    
    int *criar_vetor_vertices_adjacentes(GRAFO* g, int vertice, int *tam_adjacentes); //obter array dos vertices adjacentes a determinado vertice
    void destruir_vetor_vertices_adjacentes(int **vetor);
    int vertice_com_mais_vizinhos(GRAFO* g);

    void vertices_arestas_imprimir(GRAFO* g); //imprimir lista de vértices e lista de arestas
    void matriz_imprimir(GRAFO* g);
    // obtém uma cópia da matriz do grafo, uma vez que a original não pode ser passada para que não haja como alterá-la diretamente
    int **obter_copia_matriz(GRAFO* g);
    void destruir_copia_matriz(int ***copia);

    bool grafo_destruir(GRAFO **g);

#endif