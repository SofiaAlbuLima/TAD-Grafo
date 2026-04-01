#include "graph.h"

struct grafo_{
    int n_vertices;
    int **matriz;
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

int **criar_matriz(int n){ //método de criação de matriz: vetor de ponteiros de linhas contíguas
    int **matriz = malloc(sizeof(int*) * n); //vetor de ponteiro (Cada posição desse vetor será o inicio de cada linha da matriz)
        if(matriz != NULL){
            matriz[0] = malloc(sizeof(int) * n * n); // aloca um vetor com todos os elementos da matriz
            
            if(matriz[0] != NULL){
                for(int i = 1; i < n; i++){ // ajusta os demais ponteiros de linhas (i > 0). i = 0, a posição matriz[0] já está ajustada
                    matriz[i] = matriz[0] + i * n;
                }
            }else{
                free(matriz);
                return NULL;
            }
        }else{
            return NULL;
        }
    return matriz;
}

bool aresta_inserir(GRAFO* g, int a, int b, int peso){
    if(g == NULL){ return 0; }

    a--; b--;

    if(
        (a >= 0 && a < g->n_vertices) && 
        (b >= 0 && b < g->n_vertices)
    ){
        g->matriz[a][b] = peso;
        g->matriz[b][a] = peso;

        return 1;
    }
    return 0;
}

bool aresta_verificar(GRAFO* g, int a, int b){
    if(g == NULL){ return 0; }

    a--; b--;

    if(
        (a >= 0 && a < g->n_vertices) && 
        (b >= 0 && b < g->n_vertices)
    ){
        if(g->matriz[a][b] != -1){ // verificar "g->matriz[b][a] != -1" é redundante
            return 1;
        }
    }
    return 0;
}

bool aresta_remover(GRAFO* g, int a, int b){
    if(g == NULL){ return 0; }

    a--; b--;

    if(
        a >= 0 && a < g->n_vertices && 
        b >= 0 && b < g->n_vertices
    ){
        g->matriz[a][b] = -1;
        g->matriz[b][a] = -1;

        return true;
    }
    printf("-1\n");
    return false;
}

int *criar_vetor_vertices_adjacentes(GRAFO* g, int vertice, int *tam_adjacentes) {
    if(g == NULL) return 0;

    int cont=0;
    int temp[g->n_vertices-1]; // g->n_vertices-1 por ser o tamanho máximo que o vetor final pode assumir: o de uma linha ou coluna inteira sem o pŕoprio vértice
    vertice--;

    // contando a quantidade de espaço a ser alocado enquanto guarda os vértices adjacentes num array estático temporário
    for (int i=0; i < g->n_vertices; i++) {
        if (g->matriz[i][vertice] != -1 && i!=vertice) {
            temp[cont] = i+1;
            cont++;
        }
    }

    // aloca o vetor definitivo
    int *vetor = malloc(sizeof(int)*cont);

    if (vetor != NULL) {
        // passa as informações do vetor temporário para o definitivo
        for (int i=0; i<cont; i++) {
            vetor[i] = temp[i];
        }
    }

    *tam_adjacentes = cont;
    return vetor; // se vetor for NULL, então devolve NULL. Caso contrário, devolve seu endereço.
}

void destruir_vetor_vertices_adjacentes(int **vetor) {
    if (vetor == NULL) return;
    if (*vetor == NULL) return;

    free(*vetor);
    *vetor = NULL;
    
    return;
}
    
int vertice_com_mais_vizinhos(GRAFO* g){
    if(g == NULL){ return -1; }

    int v = 0; //vertice com mais vizinhos atual
    int v_n = -1; //quantidade de vizinhos do vertice com mais vizinhos

    int i = 0; //contador de vizinhos

    for(int j = 0; j < g->n_vertices; j++){
        i = 0;
        for(int k = 0; k < g->n_vertices; k++){
            if(j != k && g->matriz[j][k] != -1){
                i++;
            }
        }
        if(i > v_n){
            v = j;
            v_n = i;
        }
    }

    return(v + 1);
}

void vertices_arestas_imprimir(GRAFO* g){
    if(g == NULL){ return; }

    printf("V = [");
    if(g->n_vertices == 1){ printf("1]\n"); }
    else{ 
        for (int i = 1; i <= g->n_vertices; i++){
            if(i == 1){
                printf("%d,", i);
            }else if(i == g->n_vertices){
                printf(" %d]\n", i);
            }else{
                printf(" %d,", i);
            }
        }
    }

    printf("E = [");

    int primeira = 1; //formatacao das arestas separadas por virgula

    for(int j = 0; j < g->n_vertices; j++){
        for(int k = j + 1; k < g->n_vertices; k++){ //"j+1" para nao repetir arestas
            if(g->matriz[j][k] != -1){

                if(!primeira){
                    printf(", ");
                }

                printf("(%d, %d)", j+1, k+1);
                primeira = 0;
            }
        }
    }

    printf("]\n");
    return;
}

void matriz_imprimir(GRAFO* g){
    if(g == NULL){ return; }

    printf("   ");

    for (int i = 1; i <= g->n_vertices; i++){
        printf("  %d", i);
    }
    printf("\n---");

    for (int i = 1; i <= g->n_vertices; i++){
        printf("---");
    }
    printf("\n");
    
    for (int i = 1; i <= g->n_vertices; i++){
        printf("%d |", i);
        for(int j = 0; j < g->n_vertices; j++){
            if(g->matriz[i-1][j] < 0){
                printf("   ");
            }else if(g->matriz[i-1][j] < 10){
                printf("  %d", g->matriz[i-1][j]);
            }else{
                printf(" %d", g->matriz[i-1][j]);
            }
        }
        printf("\n");
    }

    return;
    // Exemplo da Matriz do enunciado
    //      1  2  3  4  5  6  7  8 
    // ----------------------------
    // 1 |     1  4              3 
    // 2 |  1     5  6           2 
    // 3 |  4  5     9  8          
    // 4 |     6  9     7 10 11
    // 5 |        8  7       
    // 6 |          10      
    // 7 |          11      
    // 8 |  3  2             
}

int **obter_copia_matriz(GRAFO* g) {
    
}

void destruir_copia_matriz(int **copia) {

}

bool grafo_destruir(GRAFO **g){
    if(g == NULL) return false;
    if((*g) == NULL) return false;

    if((*g)->matriz != NULL){
        free((*g)->matriz[0]); // libera os dados
        free((*g)->matriz);    // libera os ponteiros
    }

    free(*g);
    *g = NULL;
    return true;
}