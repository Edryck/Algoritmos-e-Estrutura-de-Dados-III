#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

int main() {
    ArvAVL *raiz = cria_ArvAVL();
    int opcao, valor, retorno;

    do {
        printf("\n======================================\n");
        printf("\t\tMENU - ARVORE AVL\n");
        printf("======================================\n");
        printf("1 - Inserir Elemento\n");
        printf("2 - Remover Elemento\n");
        printf("3 - Imprimir em Ordem (com FB e Altura)\n");
        printf("4 - Imprimir Pre-Ordem\n");
        printf("5 - Imprimir Pos-Ordem\n");
        printf("6 - Consultar Valor\n");
        printf("7 - Informacoes (Total Nos / Altura)\n");
        printf("8 - Verificar se e AVL (Questao 7)\n");
        printf("9 - Transformar em AVL (Questao 8)\n");
        printf("0 - Sair\n");
        printf("--------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("\nDigite o valor a inserir: ");
                scanf("%d", &valor);
                if(insere_ArvAVL(raiz, valor))
                    printf("Insercao realizada com sucesso!\n");
                else
                    printf("Falha na insercao.\n");
                break;

            case 2:
                printf("\nDigite o valor a remover: ");
                scanf("%d", &valor);
                if(remove_ArvAVL(raiz, valor))
                    printf("Remocao realizada com sucesso!\n");
                else
                    printf("Falha na remocao (valor nao encontrado ou erro).\n");
                break;

            case 3:
                printf("\n--- Em Ordem ---\n");
                emOrdem_ArvAVL(raiz);
                printf("----------------\n");
                break;

            case 4:
                printf("\n--- Pre Ordem ---\n");
                preOrdem_ArvAVL(raiz);
                printf("-----------------\n");
                break;

            case 5:
                printf("\n--- Pos Ordem ---\n");
                posOrdem_ArvAVL(raiz);
                printf("-----------------\n");
                break;

            case 6:
                printf("\nDigite o valor para consultar: ");
                scanf("%d", &valor);
                if(consulta_ArvAVL(raiz, valor))
                    printf("Valor %d encontrado na arvore.\n", valor);
                else
                    printf("Valor %d nao encontrado.\n", valor);
                break;

            case 7:
                printf("\nTotal de Nos: %d\n", totalNO_ArvAVL(raiz));
                printf("Altura da Arvore: %d\n", altura_ArvAVL(raiz));
                break;

            case 8:
                retorno = VerificaAVL(*raiz);
                if(retorno == -2)
                    printf("\nNao e AVL (Desbalanceada ou erro estrutural).\n");
                else
                    printf("\nE AVL (Altura retornada: %d).\n", retorno);
                break;

            case 9:
                if(*raiz == NULL) {
                    printf("Arvore vazia\n");
                } else {
                    ArvAVL novaRaiz = transformaAVL(raiz);
                    libera_ArvAVL(raiz); 
                    raiz = cria_ArvAVL();
                    *raiz = novaRaiz;
                    printf("\nArvore transformada em AVL!\n");
                }
                break;

            case 0:
                printf("Saindo...\n");
                libera_ArvAVL(raiz);
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
