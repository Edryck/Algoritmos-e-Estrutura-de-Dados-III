#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

Grafo* criaGrafoNDirec(void) {
    Grafo *gr = cria_Grafo(4, 0); 
    insereAresta(gr, 0, 1, 0, 1.0);
    insereAresta(gr, 0, 2, 0, 1.0);
    insereAresta(gr, 1, 3, 0, 1.0);
    insereAresta(gr, 2, 3, 0, 1.0);
    return gr;
}

Grafo* criaGrafoDirec(void) {
    Grafo *gr = cria_Grafo(4, 0); 
    insereAresta(gr, 0, 1, 1, 1.0);
    insereAresta(gr, 1, 2, 1, 1.0);
    insereAresta(gr, 1, 3, 1, 1.0);
    insereAresta(gr, 3, 0, 1, 1.0);
    return gr;
}

// Renomeado para v1 para evitar conflito
Grafo* criaGrafoSeq2_v1(void) {
    Grafo *gr = cria_Grafo(8, 0);
    insereAresta(gr, 0, 1, 0, 1.0);
    insereAresta(gr, 0, 2, 0, 1.0);
    insereAresta(gr, 0, 3, 0, 1.0);
    insereAresta(gr, 0, 4, 0, 1.0);
    insereAresta(gr, 0, 5, 0, 1.0);
    insereAresta(gr, 0, 6, 0, 1.0);
    insereAresta(gr, 1, 2, 0, 1.0);
    insereAresta(gr, 1, 3, 0, 1.0);
    insereAresta(gr, 1, 4, 0, 1.0);
    insereAresta(gr, 2, 3, 0, 1.0);
    insereAresta(gr, 2, 4, 0, 1.0);
    insereAresta(gr, 5, 7, 0, 1.0);
    return gr;
}

// Renomeado para v2 para evitar conflito
Grafo* criaGrafoSeq2_v2(void) {
    Grafo *gr = cria_Grafo(8, 0);
    insereAresta(gr, 0, 1, 0, 1.0);
    insereAresta(gr, 0, 2, 0, 1.0);
    insereAresta(gr, 0, 3, 0, 1.0);
    insereAresta(gr, 0, 4, 0, 1.0);
    insereAresta(gr, 0, 5, 0, 1.0);
    insereAresta(gr, 1, 2, 0, 1.0);
    insereAresta(gr, 1, 3, 0, 1.0);
    insereAresta(gr, 1, 6, 0, 1.0);
    insereAresta(gr, 1, 7, 0, 1.0);
    insereAresta(gr, 2, 4, 0, 1.0);
    insereAresta(gr, 2, 5, 0, 1.0);
    insereAresta(gr, 2, 6, 0, 1.0);
    insereAresta(gr, 3, 7, 0, 1.0);
    insereAresta(gr, 4, 7, 0, 1.0);
    insereAresta(gr, 5, 6, 0, 1.0);
    return gr;
}

void prim(Grafo* gr, int orig, int *pai, float *peso){
    if(gr == NULL) return;
    if(orig < 0 || orig >= gr->nos) return;

    int nro_vertices = gr->nos;
    int *visitado = (int*) malloc(nro_vertices * sizeof(int));
    if(visitado == NULL) return;

    float INF = 9999999.0f;
    int i;

    for(i = 0; i < nro_vertices; i++){
        visitado[i] = 0;
        pai[i] = -1;
        peso[i] = INF;
    }

    peso[orig] = 0.0f;

    int cont;
    for(cont = 0; cont < nro_vertices - 1; cont++){
        int u = -1;
        float menor = INF;
        for(i = 0; i < nro_vertices; i++){
            if(!visitado[i] && peso[i] < menor){
                menor = peso[i];
                u = i;
            }
        }
        if(u == -1)
            break;

        visitado[u] = 1;
        No *aux = gr->vet[u];
        while(aux != NULL){
            int v = aux->destino;
            float w = aux->peso;

            if(!visitado[v] && w < peso[v]){
                peso[v] = w;
                pai[v] = u;
            }

            aux = aux->prox;
        }
    }
    free(visitado);
}

int main() {
    int opcao, orig, dest, digrafo, n_vertices, ponderado;
    float peso_aresta;
    
    int res_orig, res_dest;
    float res_peso;
    
    // Variáveis para Prim
    int *pai;
    float *peso_prim;
    int i;

    Grafo* gr = NULL; 

    do {
        printf("\n\tMENU GRAFO\n");
        printf("1  - Criar Novo Grafo Vazio\n");
        printf("2  - Inserir Aresta\n");
        printf("3  - Remover Aresta\n");
        printf("4  - Imprimir Grafo\n");
        printf("5  - Verificar se No existe\n");
        printf("6  - Buscar Menor Aresta\n");
        printf("----------------------------\n");
        printf("7  - Carregar Grafo Teste Nao Direcionado (4 nos)\n");
        printf("8  - Carregar Grafo Teste Direcionado (4 nos)\n");
        printf("9  - Carregar Grafo Sequencia 2 (v1 - 8 nos)\n");
        printf("10 - Carregar Grafo Sequencia 2 (v2 - 8 nos)\n");
        printf("11 - Executar Algoritmo de PRIM\n");
        printf("0  - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if(gr != NULL) libera_Grafo(gr);
                printf("Num de vertices: "); 
                scanf("%d", &n_vertices);
                printf("Ponderado? (1-Sim/0-Nao): "); 
                scanf("%d", &ponderado);
                gr = cria_Grafo(n_vertices, ponderado);
                printf("Grafo criado!\n");
                break;

            case 2:
                if(gr == NULL) { printf("Crie um grafo primeiro!\n"); break; }
                printf("Origem: "); 
                scanf("%d", &orig);
                printf("Destino: "); 
                scanf("%d", &dest);
                printf("Digrafo? (1-S/0-N): "); 
                scanf("%d", &digrafo);
                peso_aresta = 1.0;
                if(gr->eh_ponderado) {
                    printf("Peso: "); 
                    scanf("%f", &peso_aresta);
                }
                if(insereAresta(gr, orig, dest, digrafo, peso_aresta))
                    printf("Sucesso!\n");
                else 
                    printf("Erro (indices invalidos)!\n");
                break;

            case 3:
                if(gr == NULL) { 
                    printf("Crie um grafo primeiro!\n"); 
                    break; 
                }
                printf("Origem: "); 
                    scanf("%d", &orig);
                printf("Destino: "); 
                    scanf("%d", &dest);
                printf("Digrafo? (1-S/0-N): "); 
                    scanf("%d", &digrafo);
                removeAresta(gr, orig, dest, digrafo);
                break;

            case 4:
                imprime_Grafo(gr);
                break;

            case 5:
                if(gr == NULL) { 
                    printf("Crie um grafo primeiro!\n"); 
                    break; 
                }
                printf("No: "); 
                scanf("%d", &orig);
                if(buscaNo(gr, orig)) 
                    printf("Existe.\n");
                else 
                    printf("Nao existe.\n");
                break;

            case 6:
                if(buscaMenorAresta(gr, &res_orig, &res_dest, &res_peso))
                    printf("Menor: %d -> %d (Peso: %.2f)\n", res_orig, res_dest, res_peso);
                else 
                    printf("Sem arestas.\n");
                break;
            case 7:
                if(gr != NULL) 
                    libera_Grafo(gr);
                gr = criaGrafoNDirec();
                printf("Grafo Nao Direcionado carregado.\n");
                break;

            case 8:
                if(gr != NULL) 
                    libera_Grafo(gr);
                gr = criaGrafoDirec();
                printf("Grafo Direcionado carregado.\n");
                break;

            case 9:
                if(gr != NULL) 
                    libera_Grafo(gr);
                gr = criaGrafoSeq2_v1();
                printf("Grafo Seq2 (Versao 1) carregado.\n");
                break;

            case 10:
                if(gr != NULL) 
                    libera_Grafo(gr);
                gr = criaGrafoSeq2_v2();
                printf("Grafo Seq2 (Versao 2) carregado.\n");
                break;

            case 11:
                if(gr == NULL) {
                    printf("Carregue um grafo primeiro!\n");
                    break;
                }
                printf("Vertice inicial para Prim: ");
                scanf("%d", &orig);

                pai = (int*) malloc(gr->nos * sizeof(int));
                peso_prim = (float*) malloc(gr->nos * sizeof(float));

                if(pai != NULL && peso_prim != NULL) {
                    prim(gr, orig, pai, peso_prim);

                    printf("\n\tResultado Prim (AGM)\n");
                    for(i = 0; i < gr->nos; i++){
                        if(pai[i] != -1)
                            printf("Vertice %d: Pai: %d, Custo: %.2f\n", i, pai[i], peso_prim[i]);
                        else if (i == orig)
                            printf("Vertice %d: Raiz (Custo: %.2f)\n", i, peso_prim[i]);
                        else
                             printf("Vertice %d: Inalcancavel\n", i);
                    }
                    free(pai);
                    free(peso_prim);
                } else {
                    printf("Erro de memoria para Prim.\n");
                }
                break;

            case 0:
                system("pause");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    libera_Grafo(gr);
    return 0;
}