/**
 * Alunos: 
 *    Edryck - a2727617
 *    Samuel - a2727820
 */

#include <stdio.h>
#include <stdlib.h>
#include "FilaDin.h"
int main(){
    int opcao;
    do {
    printf("\t\t Lista de Filas\n\n");
    printf("1 - Exercicio 5 (controle de decolagem)\n");
    printf("2 - Exercicio 8 (funcoes de fila da alunos).\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", opcao);
    if(opcao == 1)
        ex_5();
    else if (opcao == 2)
        ex_8();
    else if (opcao == 0)
        system("pause");
    else
        printf("Opcao invalida! Tente novamente.\n\n");
    } while(opcao != 0);
    return 0;
}