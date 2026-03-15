#include <stdio.h>
#include "graph.h"

struct grafo_{
    int n_vertices;
    int **matriz;
};

struct aresta_{
    int extremo_a;
    int extremo_b;
    int peso;
};

int **criar_matriz(int n); //função auxiliar do grafo_criar

GRAFO* grafo_criar(int n){ //A função retorna ponteiro para grafo
    GRAFO *grafo = (GRAFO*) malloc(sizeof(GRAFO)); //criando struct, grafo é um ponteiro dizendo onde ela está

    if(grafo != NULL){
        //Criando Matriz de Adjacência
        int **matriz = criar_matriz(n);
        if(matriz == NULL){
            free(grafo);
            return NULL;
        }

        //inicializando arestas com valor "-1"
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                matriz[j][k] = -1;
            }
        }

        //Completando Struct
        grafo->n_vertices = n;
        grafo->matriz = matriz;

        return grafo;
    }else{
        return NULL;
    }
}

int **criar_matriz(int n){
    int **matriz = malloc(sizeof(int*) * n); //vetor de ponteiro (Cada posição desse vetor será uma linha da matriz)
        if(matriz != NULL){
            for(int i = 0; i < n; i++){ //criando as linhas da matriz
                matriz[i] = malloc(sizeof(int) * n);
                if(matriz[i] == NULL){ //evitando memory leak
                    for(int j = 0; j < i; j++){
                            free(matriz[j]);
                    }
                    free(matriz);
                    return NULL;
                }
            }
        }else{
            return NULL;
        }
    return matriz;
}

ARESTA* aresta_inserir(GRAFO* g, int a, int b, int peso){
    
}