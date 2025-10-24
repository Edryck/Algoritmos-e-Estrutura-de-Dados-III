#ifndef MATRIZ_H
#define MATRIZ_H

struct elemento {
    int valor;
    struct elemento* dir;
    struct elemento* esq;
    struct elemento* cima;
    struct elemento* baixo;
};
struct matriz {
    struct elemento* inicio;
    int linhas;
    int colunas;
};

typedef struct matriz Matriz;
typedef struct elemento Elemento;

Matriz* cria_matriz(int linha, int coluna);
void libera_matriz(Matriz* m);
int insere_matriz(Matriz* m, int valor, int x, int y);
Elemento* consulta_no(Matriz* m, int x, int y);
Elemento* busca_valor(Matriz* m, int valor);
void imprime_vizinhos(Matriz* m, int x, int y);

int remove_especifico(Matriz* m, int x, int y); // (Define valor como 0)
int imprime_matriz(Matriz* m);
int matriz_vazia(const Matriz* m);
int matriz_cheia(const Matriz* m);
int consulta_valor(Matriz* m, int x, int y, int* valor_out);
int tamanho_total(const Matriz* m);
int tamanho_usado(Matriz* m);


#endif // MATRIZ_H
