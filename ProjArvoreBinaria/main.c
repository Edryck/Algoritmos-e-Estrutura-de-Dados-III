#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"
int main() {
    int opcao, valor, count = 0, resultado;
    ArvBin *raiz = cria_ArvBin();

    do {
        printf("===== LISTA ÁRVORE BINARIA =====\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Remover elemento\n");
        printf("3 - Mostrar arvore (Pre, Em, Pos-ordem)\n");
        printf("4 - Contar total de nos\n");
        printf("5 - Consultar valor\n");
        printf("6 - Contar folhas\n");
        printf("7 - Identificar nos (pais, filhos e folhas)\n");
        printf("8 - Contar ocorrencia de um valor\n");
        printf("9 - Mostrar folhas em ordem decrescente\n");
        printf("10 - Eliminar numeros pares\n");
        printf("11 - Inserir letras (questao 8)\n");
        printf("12 - Expressao matematica (questao 9)\n");
        printf("0 - Sair\n");
        printf("===============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        system("cls"); // limpa a tela a cada operação

        switch(opcao) {
            case 1:
                printf("Digite um valor inteiro: ");
                scanf("%d", &valor);
                if(insere_ArvBin(raiz, valor))
                    printf("Valor inserido com sucesso!\n");
                else
                    printf("Falha ao inserir valor!\n");
                break;

            case 2:
                printf("Digite o valor para remover: ");
                scanf("%d", &valor);
                if(remove_ArvBin(raiz, valor))
                    printf("Valor removido com sucesso!\n");
                else
                    printf("Valor nao encontrado!\n");
                break;

            case 3:
                printf("Escolha o tipo de percurso:\n");
                printf("1 - Pre-Ordem\n");
                printf("2 - Em-Ordem\n");
                printf("3 - Pos-Ordem\n");
                printf("Opcao: ");
                scanf("%d", &valor);
                printf("\n");

                if(valor == 1)
                    preOrdem_ArvBin(raiz);
                else if(valor == 2)
                    emOrdem_ArvBin(raiz);
                else if(valor == 3)
                    posOrdem_ArvBin(raiz);
                else
                    printf("Opcao invalida!\n");
                break;

            case 4:
                printf("Total de nos: %d\n", totalNO_ArvBin(raiz));
                break;

            case 5:
                printf("Digite o valor a consultar: ");
                scanf("%d", &valor);
                if(consulta_ArvBin(raiz, valor))
                    printf("Valor encontrado na arvore!\n");
                else
                    printf("Valor nao encontrado.\n");
                break;

            case 6:
                count = 0;
                quant_folha(raiz, &count);
                printf("Total de folhas: %d\n", count);
                break;

            case 7:
                identifica_no(raiz, 0, 0);
                break;

            case 8:
                printf("Digite o valor para contar ocorrencia: ");
                scanf("%d", &valor);
                count = 0;
                conta_ocorrencia(raiz, &count, valor);
                printf("O valor %d apareceu %d vezes.\n", valor, count);
                break;

            case 9:
                printf("Folhas em ordem decrescente:\n");
                folha_decrescente(raiz);
                break;

            case 10:
                elimina_par(raiz);
                printf("Todos os valores pares foram removidos.\n");
                break;

            case 11: {
                char letras[] = {'M','F','S','D','J','P','U','A','E','H','Q','T','W','K'};
                int tamanho = sizeof(letras)/sizeof(letras[0]);
                for(int i=0; i<tamanho; i++)
                    insere_ArvBin(raiz, letras[i]);
                printf("Letras inseridas na arvore!\n\n");
                preOrdem_ArvBin_char(raiz);
                break;
            }

            case 12:
                printf("Construindo e avaliando a expressao da questão 9...\n");
                resultado = verifica_expressao(raiz);
                printf("Resultado da expressao: %d\n", resultado);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        printf("\n");
        system("pause");
        system("cls"); 

    } while(opcao != 0);

    libera_ArvBin(raiz);
    return 0;
}

