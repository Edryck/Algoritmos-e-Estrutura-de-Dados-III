#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main() {
    Matriz* m = cria_matriz(5, 5);
    if(m == NULL)
        return 1;

    imprime_matriz(m);
    printf("\n\n\n");

    insere_matriz(m, 1, 2, 2);
    imprime_matriz(m);
    printf("\n\n\n");

    insere_matriz(m, 1, 0, 0);
    imprime_matriz(m);
    printf("\n\n\n");

    insere_matriz(m, 1, 4, 0);
    imprime_matriz(m);
    printf("\n\n\n");

    insere_matriz(m, 1, 0, 4);
    imprime_matriz(m);
    printf("\n\n\n");

    insere_matriz(m, 1, 4, 4);
    imprime_matriz(m);
    printf("\n\n\n");

    imprime_vizinhos(m, 2, 2);
    printf("\n\n\n");

    remove_especifico(m, 2, 2);
    imprime_matriz(m);
    printf("\n\n\n");

    libera_matriz(m);
    return 0;
}
