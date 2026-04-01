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

    int flag = 1;
    while(flag > 0){

        printf("\nEscolha o que voce deseja fazer:\n");
    
        printf("[1] Adicionar aresta\n");
        printf("[2] Imprimir matriz\n");
        printf("[3] Imprimir vertices e arestas\n");
        printf("[4] Imprimir vertices adjacentes de outro vertice\n");
        printf("[5] Imprimir vertice com maior quantidade de vizinhos\n");
        printf("[6] Checar existência de aresta\n");
        printf("[7] Tirar aresta\n");
        printf("[0] Destruir grafo e finalizar programa\n\n");
    
        scanf("%d", &opcao_menu);
        
        switch (opcao_menu){
            case 1:
                printf("Por favor, informe na seguinte ordem: [vertice a, verice b, peso da aresta]\n");
                    scanf("%d", &a);
                    scanf("%d", &b);
                    scanf("%d", &peso);

                if(aresta_inserir(g, a, b, peso)){
                    printf("Aresta adicionada ao grafo!\n");
                }else{
                    printf("Erro ao adicionar aresta\n");
                }
                break;

            case 2:
                printf("\nMatriz de adjacência:\n");
                matriz_imprimir(g); // acho melhor usar a função de cópia e printar aqui para dar um uso pra função que foi pedida na especificação
                break;

            case 3:
                printf("\nVertices(V) e Arestas(E):\n");
                vertices_arestas_imprimir(g);
                break;

            case 4: { //chaves para escopo local
                printf("\nEscolha um vertice para descobrir seus vizinhos: ");
                int vertice; scanf("%d", &vertice);
                
                int tam_adjacentes;
                int *vetor_adjacentes = criar_vetor_vertices_adjacentes(g, vertice, &tam_adjacentes);

                if (vetor_adjacentes == NULL) printf("\nErro de alocação de memória para o vetor adjacente. Tente novamente.\n");
                else {
                    // imprimindo vértices adjacentes usando o array devolvido:
                    printf("\nVertices Adjacentes:\n");
                    for(int i=0; i<(tam_adjacentes)-1; i++) {
                        printf("%d, ", vetor_adjacentes[i]);
                    }
                    printf("%d.\n", vetor_adjacentes[tam_adjacentes]); // para uma formatação de saída bonita

                    destruir_vetor_vertices_adjacentes(&vetor_adjacentes);
                }

                break;
            }

            case 5: 
                int vertice = vertice_com_mais_vizinhos(g);
                if (vertice == -1) printf("\nGrafo nao encontrado ou vazio.\n");
                else printf("\nVertice com maior quantidade de vizinhos: %d\n", vertice);
                break;

            case 6:
                printf("Por favor, informe na seguinte ordem: [vertice a, verice b]\n");
                    scanf(" %d", &a);
                    scanf(" %d", &b);
                if (aresta_verificar(g, a, b)) {
                    printf("\nA aresta existe.\n");
                } else {
                    printf("\nA aresta não existe.\n");
                }
                break;
            
            case 7:
                printf("Por favor, informe os vértices das extremidades da aresta a ser removida: ");
                int a, b;
                scanf(" %d %d", a, b);

                if (aresta_remover(g, a, b)) printf("\nRemocao bem sucedida.\n");
                else printf("\nNao foi possivel fazer a remocao. Tente novamente.\n");

                break;

            case 0:
                if(grafo_destruir(&g)){
                    printf("\nPrograma finalizando...\n");
                    flag = 0;
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
