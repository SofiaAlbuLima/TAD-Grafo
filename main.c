#include <stdio.h>
#include "graph.h"

int main(void) {
    int opcao_menu;
    int numero_vertices, a, b, peso;

    printf("Seja bem vindo(a) ao TAD Grafo!\nVamos criar um grafo, quantos vertices voce deseja?\n");
    scanf("%d", &numero_vertices);

    GRAFO* g = grafo_criar(numero_vertices);
    if(g == NULL || numero_vertices <= 0){
        printf("Erro ao criar grafo\n");
        return 1;
    }

    printf("Grafo criado com sucesso!\n");
    
    int i = 1;
    while(i > 0){

        printf("\nEscolha o que voce deseja fazer:\n");
    
        printf("[1] Adicionar aresta\n");
        printf("[2] Imprimir matriz\n");
        printf("[3] Imprimir vertices e arestas\n");
        printf("[4] Imprimir vertices adjacentes de outro vertice\n");
        printf("[5] Imprimir vertice com maior quantidade de vizinhos\n");
        printf("[0] Destruir grafo e finalizar programa\n\n");
    
        scanf("%d", &opcao_menu);
        
        switch (opcao_menu){
            case 1:
                printf("Por favor, informe na seguinte ordem: [vertice a, verice b, peso da aresta]\n");
                    scanf("%d", &a);
                    scanf("%d", &b);
                    scanf("%d", &peso);
                aresta_inserir(g, a, b, peso);

                if(aresta_verificar(g,a,b)){
                    printf("Aresta adicionada ao grafo!\n");
                }else{
                    printf("Erro ao adicionar aresta\n");
                }
                break;
            case 2:
                printf("\nMatriz de adjacência:\n");
                matriz_imprimir(g);
                break;
            case 3:
                printf("\nVertices(V) e Arestas(E):\n");
                vertices_arestas_imprimir(g);
                break;
            case 4: { //chaves para escopo local
                printf("\nEscolha um vertice para descobrir seus vizinhos: ");
                int adj; scanf("%d", &adj);
                printf("\nVertices Adjacentes:\n");
                // vertices_adjacentes(g, adj);
                break;
            }
            case 5: 
                printf("\nVertice com maior quantidade de vizinhos: %d\n", vertice_com_mais_vizinhos(g));
                break;
            case 0:
                if(grafo_destruir(g)){
                    g = NULL;
                    printf("\nPrograma finalizando...\n");
                    i = 0;
                }else{
                    printf("Erro: grafo inexistente\n");
                    return 1;
                }
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    }

    return 0;
}
