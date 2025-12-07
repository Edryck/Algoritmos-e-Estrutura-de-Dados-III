#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int destino;
    float peso;
    struct no *prox;
} No;

typedef No* Lista;

typedef struct grafo {
    Lista* vet; // Array de Listas
    int nos; // Número de vértices
    int eh_ponderado;
} Grafo;

Grafo* cria_Grafo(int nro_vertices, int eh_ponderado);
void libera_Grafo(Grafo* gr);
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);
int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo);
void imprime_Grafo(Grafo *gr);
int buscaNo(Grafo* gr, int no);
int buscaMenorAresta(Grafo* gr, int *orig, int *dest, float *peso);
void prim(Grafo* gr, int orig, int *pai, float *peso);
