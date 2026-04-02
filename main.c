/*
Trabalho 1 de Grafos (SCC0216)

ALUNAS:
Lorena Moreira Borges - 16883652
Sofia Albuquerque Lima - 16900810
*/

// começa o arquivo graph.h

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

    void grafo_destruir(GRAFO **g);

#endif

// começa o arquivo graph.c

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

        // inicializando arestas com valor "-1", aproveitando da sua alocação linear
        for(int i=0; i < (n*n); i++){ // n*n é o tamanho de espaços da matriz, e comprimento do array
            matriz[0][i] = -1;
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

// desaloca o espaço dedicado aos dados e ao array de vetores, além de deixar o vetor da matriz nulo
void destruir_matriz (int ***ponteiro_matriz) {
    if(*ponteiro_matriz != NULL) {
        free((*ponteiro_matriz)[0]); // libera o array longo que corresponde ao conteúdo da matriz, alocado no primeiro ponteiro do array de ponteiros
        free(*ponteiro_matriz); // libera a memória do array de ponteiros
        *ponteiro_matriz = NULL;
    }
    return;
}

// retorna verdadeiro se a aresta foi incluida e falso caso contrário. Sobreescreve, caso já haja uma aresta
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

// verifica se a aresta existe comparando-a com -1. Devolve verdadeiro caso exista, senão devolve falso
bool aresta_verificar(GRAFO* g, int a, int b){
    if(g == NULL){ return false; }

    a--; b--;

    if(
        (a >= 0 && a < g->n_vertices) && 
        (b >= 0 && b < g->n_vertices)
    ){
        if(g->matriz[a][b] != -1){ // verificar "g->matriz[b][a] != -1" é redundante pela matriz ser simétrica
            return true;
        }
    }
    return false;
}

// remove uma aresta, colocando -1. Devolve verdadeiro, se bem sucedido, e falso caso contrário
bool aresta_remover(GRAFO* g, int a, int b){
    if(g == NULL){ return false; }

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

// dado um grafo e um vértice específico, devolve os adjacentes. O terceiro parâmetro serve para devolver o tamanho desse vetor, para que seja possível fazer operações nele
int *criar_vetor_vertices_adjacentes(GRAFO* g, int vertice, int *tam_adjacentes) {
    if(g == NULL) return 0;

    int cont=0;
    int temp[(g->n_vertices)-1]; // g->n_vertices-1 por ser o tamanho máximo que o vetor final pode assumir: o de uma linha ou coluna inteira sem o pŕoprio vértice
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

// desaloca o vetor de vértices adjacentes, deixando o ponteiro do usuário apontando pra nulo
void destruir_vetor_vertices_adjacentes(int **vetor) {
    if (vetor == NULL) return;
    if (*vetor == NULL) return;

    free(*vetor);
    *vetor = NULL;
    
    return;
}

// devolve o primeiro vértice com mais vizinhos
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

// imprime os vértices e as arestas na formatação pedida
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

    for(int k = 0; k < g->n_vertices; k++){
        for(int j = 0; j < k; j++){ //até k para não repetir arestas
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

// imprime a matriz diretamente, sem precisar pedir uma cópia da matriz
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

// obtém uma cópia da matriz do grafo, uma vez que a original não pode ser passada para que não haja como alterá-la diretamente
int **obter_copia_matriz(GRAFO* g) {
    int **matriz = criar_matriz(g->n_vertices);
    // fazendo a cópia da matriz do grafo inicial, aproveitando da sua alocação linear:
    if(matriz != NULL) {
        for(int i=0; i < (g->n_vertices)*(g->n_vertices); i++) { // (g->n_vertices)*(g->n_vertices) por ser o tamanho total do array
            matriz[0][i] = g->matriz[0][i];
        }
    }

    return matriz;
}

// desaloca a matriz chamando a função interna especializada para desocação de matriz. O vetor do usuário passa a apontar para nulo com ela também
void destruir_copia_matriz(int ***ponteiro_copia) {
    destruir_matriz(ponteiro_copia);
    return;
}

// desaloca o espaço do grafo e torna o ponteiro do usuário nulo
void grafo_destruir(GRAFO **g){
    if(g == NULL) return;
    if((*g) == NULL) return;

    destruir_matriz(&(*g)->matriz);
    free(*g);
    *g = NULL;

    return;
}

// começa o arquivo main.c

int main(void) {
    int opcao_menu = 8, ultima_opcao_menu = -1; // primeiro número que cai no caso default, para que, se algo der errado, o programa rode de novo sem executar nada
    int numero_vertices, a, b;
    GRAFO* g;

    while (opcao_menu != -1) {
    
        scanf("%d", &opcao_menu);
        
        switch (opcao_menu){
            case 0: // criar grafo baseando-se na quantidade de vértices
            ultima_opcao_menu = 0;

            scanf(" %d", &numero_vertices);

                g = grafo_criar(numero_vertices);
                if(g == NULL || numero_vertices <= 0){
                    return 1;
                }

                break;
            case 1: // adicionar aresta
            { // chaves para a variável ser de escopo local (deletada assim que sair do escopo)
                ultima_opcao_menu = 1;
                
                int peso;
                scanf("%d", &a);
                scanf("%d", &b);
                scanf("%d", &peso);

                aresta_inserir(g, a, b, peso);
                    
                break;
            }

            case 2:  // checar existência de aresta
                ultima_opcao_menu = 2;
            
                scanf(" %d", &a);
                scanf(" %d", &b);

                if (aresta_verificar(g, a, b)) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;

            case 3: // imprimir vértices adjacentes de outro vértice
            { //chaves para as variáveis serem de escopo local
                ultima_opcao_menu = 3;
                
                int vertice;
                scanf("%d", &vertice);
                
                int tam_adjacentes;
                int *vetor_adjacentes = criar_vetor_vertices_adjacentes(g, vertice, &tam_adjacentes);

                if (vetor_adjacentes != NULL) {
                    // imprimindo vértices adjacentes usando o array devolvido:
                    for(int i=0; i<tam_adjacentes; i++) {
                        printf("%d ", vetor_adjacentes[i]);
                    }

                    destruir_vetor_vertices_adjacentes(&vetor_adjacentes);
                }

                break;
            }

            case 4: // tirar aresta
                ultima_opcao_menu = 4;

                scanf(" %d %d", &a, &b); // a e b são os vértices extremos da aresta a ser removida

                // a operação de aresta_remover está no último switch case para printar a saída, pois apenas caso retorne verdadeiro que os vértices e arestas são impressos

                break;

            case 5: // imprimir matriz de adjacência
                ultima_opcao_menu = 5;
            {
                int **copia_matriz = obter_copia_matriz(g);

                // imprime a cópia da matriz com a formatação pedida:
                printf("Adjacency Matrix:\n");
                for(int i=0; i<numero_vertices; i++) {
                    for(int j=0; j<numero_vertices; j++) {
                        if(j == 0) {
                            if (copia_matriz[i][j] == -1)
                                printf("%3d", 0);
                            else
                                printf("%3d", copia_matriz[i][j]);
                        }
                        else {
                            if (copia_matriz[i][j] == -1)
                                printf("%4d", 0);
                            else
                                printf("%4d", copia_matriz[i][j]);
                        }
                    }
                    printf("\n");
                }

                destruir_copia_matriz(&copia_matriz);

                break;
            }
            
            case 6: // imprimir vertice com maior quantidade de vizinhos
                ultima_opcao_menu = 6;
            {
                int vertice = vertice_com_mais_vizinhos(g);
                if (vertice != -1){
                    printf("max vertex: %d\n", vertice);
                }
                break;
            }
        }
    }

    switch (ultima_opcao_menu) {
        case 4: if(aresta_remover(g, a, b) == false) { // essa função já imprime -1 caso a aresta não exista.
                    break;
                }
        case 1:
        case 0: vertices_arestas_imprimir(g);
                break;
    }

    grafo_destruir(&g);

    return 0;
}