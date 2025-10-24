#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"


Matriz* cria_matriz(int linha, int coluna){
    if (linha <= 0 || coluna <= 0)
        return NULL;

    Matriz* m = (Matriz*) malloc(sizeof(Matriz));
    if(m == NULL)
        return NULL;

    m->inicio = NULL;
    m->linhas = linha;
    m->colunas = coluna;

    Elemento* linha_ant_ini = NULL;

    for(int i = 0; i < linha; i++) {
        Elemento* esq = NULL;
        Elemento* cima = linha_ant_ini;
        Elemento* linha_atual_ini = NULL;

        for(int j = 0; j < coluna; j++) {
            Elemento* no = (Elemento*) malloc(sizeof(Elemento));
            if(no == NULL) {
                libera_matriz(m);
                return NULL;
            }

            no->valor = 0; // Sempre inicializa com zero
            no->dir = NULL;
            no->baixo = NULL;

            // Liga esq <-> dir
            no->esq = esq;
            if(esq != NULL)
                esq->dir = no;

            // Liga cima <-> baixo
            no->cima = cima;
            if(cima != NULL)
                cima->baixo = no;

            // Prepara pra próxima iteração
            esq = no;
            if(cima != NULL)
                cima = cima->dir; // O nó de cima anda para a direita

            if(i == 0 && j == 0)
                m->inicio = no; // Salva o inicio (0,0) como a "cabeça"

            if(j == 0)
                linha_atual_ini = no; // Salva o nó (x, 0)
        }
        linha_ant_ini = linha_atual_ini;
    }
    return m;
}

void libera_matriz(Matriz *m) {
    if (m == NULL)
        return;

    if (m->inicio != NULL) {
        Elemento* linha = m->inicio;
        while (linha != NULL) {
            Elemento* proxima = linha->baixo;
            Elemento* aux = linha;
            while (aux != NULL) {
                Elemento* no = aux;
                aux = aux->dir;
                free(no);
            }
            linha = proxima;
        }
    }
    free(m);
}

int insere_matriz(Matriz* m, int valor, int x, int y){
    if(m == NULL || m->inicio == NULL)
        return 0;

    if(x < 0 || x >= m->linhas || y < 0 || y >= m->colunas)
        return 0;

    Elemento *no = m->inicio;

    for(int i = 0; i < x; i++)
        no = no->baixo;

    for(int j = 0; j < y; j++)
        no = no->dir;

    if (no != NULL) {
        no->valor = valor;
        return 1;
    }
    return 0;
}
int remove_especifico(Matriz* m, int x, int y) {
    if (!m || !m->inicio) return 0;

    if (x < 0 || x >= m->linhas || y < 0 || y >= m->colunas) return 0;

    Elemento* p = m->inicio;

    for (int i = 0; i < x; ++i) {
        if (!p) return 0;
        p = p->baixo;
    }
    for (int j = 0; j < y; ++j) {
        if (!p) return 0;
        p = p->dir;
    }
    if (!p) return 0;

    p->valor = 0;
    return 1;
}

int imprime_matriz(Matriz* m) {
    if (!m || !m->inicio) return 0;

    Elemento* linha = m->inicio;
    for (int i = 0; i < m->linhas && linha; ++i) {
        Elemento* col = linha;
        for (int j = 0; j < m->colunas && col; ++j) {
            printf("%d%s", col->valor, (j == m->colunas - 1) ? "" : " ");
            col = col->dir;
        }
        printf("\n");
        linha = linha->baixo;
    }
    return 1;
}

int matriz_vazia(const Matriz* m) {
    if (!m || !m->inicio) return 1;
    Elemento* linha = m->inicio;
    for (int i = 0; i < m->linhas && linha; ++i) {
        Elemento* col = linha;
        for (int j = 0; j < m->colunas && col; ++j) {
            if (col->valor != 0) return 0;
            col = col->dir;
        }
        linha = linha->baixo;
    }
    return 1;
}

int matriz_cheia(const Matriz* m) {
    if (!m || !m->inicio) return 0;
    Elemento* linha = m->inicio;
    for (int i = 0; i < m->linhas && linha; ++i) {
        Elemento* col = linha;
        for (int j = 0; j < m->colunas && col; ++j) {
            if (col->valor == 0) return 0;
            col = col->dir;
        }
        linha = linha->baixo;
    }
    return 1;
}

int consulta_valor(Matriz* m, int x, int y, int* valor_out) {
    if (!m || !m->inicio || !valor_out) return 0;

    if (x < 0 || x >= m->linhas || y < 0 || y >= m->colunas) return 0;

    Elemento* p = m->inicio;

    for (int i = 0; i < x; ++i) {
        if (!p) return 0;
        p = p->baixo;
    }
    for (int j = 0; j < y; ++j) {
        if (!p) return 0;
        p = p->dir;
    }
    if (!p) return 0;

    *valor_out = p->valor;
    return 1;
}

int tamanho_total(const Matriz* m) {
    if (!m) return 0;
    return m->linhas * m->colunas;
}

int tamanho_usado(Matriz* m) {
    if (!m || !m->inicio) return 0;
    int count = 0;

    Elemento* linha = m->inicio;
    for (int i = 0; i < m->linhas && linha; ++i) {
        Elemento* col = linha;
        for (int j = 0; j < m->colunas && col; ++j) {
            if (col->valor != 0) count++;
            col = col->dir;
        }
        linha = linha->baixo;
    }
    return count;
}

void imprime_vizinhos(Matriz* m, int x, int y) {
    if (m == NULL)
        return;
    if(x < 0 || y < 0)
        return;

    Elemento* no = consulta_no(m, x, y);

    if(no == NULL)
        return;

    if(no->cima == NULL) printf("No acima é nulo, entao e a borda superior\n");
    else printf("Vizinho de cima e: (%d, %d) %d\n", x - 1, y, no->cima->valor);

    if(no->esq == NULL) printf("Vizinho da esquerda e nulo, entao e a borda esquerda\n");
    else printf("Vizinho da esquerda e: (%d, %d) %d\n", x, y - 1, no->esq->valor);

    if(no->dir == NULL) printf("Vizinho da direita e nulo, entao e a borda direita\n");
    else printf("Vizinho da direita e: (%d, %d) %d\n", x, y + 1, no->dir->valor);

    if(no->baixo == NULL) printf("Vizinho de baixo e nulo, entao e a borda inferior\n");
    else printf("Vizinho de baixo e: (%d, %d) %d\n", x + 1, y, no->baixo->valor);
}

Elemento* busca_valor(Matriz* m, int valor) {
    if (m == NULL)
        return NULL;

    Elemento* linha = m->inicio;
    for (int i = 0; i < m->linhas && linha; ++i) {
        Elemento* col = linha;
        for (int j = 0; j < m->colunas && col; ++j) {
            if(col == NULL)
                break;
            if (col->valor == valor)
                return col;
            col = col->dir;
        }
        if(linha == NULL) break;
        linha = linha->baixo;
    }

    return NULL;
}

Elemento* consulta_no(Matriz* m, int x, int y) {
    if(m == NULL)
        return NULL;
    if(x < 0 || y < 0 || x >= m->linhas || y >= m->colunas)
        return NULL;

    Elemento* no = m->inicio;
    for (int i = 0; i < x; ++i) {
        if (no == NULL) return NULL;
        no = no->baixo;
    }
    for (int j = 0; j < y; ++j) {
        if (no == NULL) return NULL;
        no = no->dir;
    }
    return no;
}
