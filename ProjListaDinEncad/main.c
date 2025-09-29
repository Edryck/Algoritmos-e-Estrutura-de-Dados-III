#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncad.h"

struct aluno ler_aluno() {
    struct aluno al;
    printf("Digite a matricula: ");
    scanf("%d", &al.matricula);
    printf("Digite o nome: ");
    scanf("%s", al.nome);
    printf("Digite as 3 notas (n1 n2 n3): ");
    scanf("%f %f %f", &al.n1, &al.n2, &al.n3);
    return al;
}

int main() {
    Lista* li = cria_lista();
    int opcao, mat;
    struct aluno al;
    Elemento* p_troca;

    do {
        printf("\n Lista de Listas \n");
        printf("1 - Inserir aluno no final\n");
        printf("2 - Inserir aluno no inicio\n");
        printf("3 - Inserir aluno de forma ordenada\n");
        printf("4 - Remover aluno por matricula\n");
        printf("5 - Remover aluno do inicio\n");
        printf("6 - Remover aluno do final\n");
        printf("7 - Ver tamanho da lista\n");
        printf("8 - Consultar aluno por matricula\n");
        printf("9 - Imprimir lista\n");
        printf("10 - Trocar aluno com o proximo\n");
        printf("0 - Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                al = ler_aluno();
                if (insere_lista_final(li, al))
                    printf("Aluno adicionado!\n");
                else
                    printf("Aluno adicionado!\n");
                break;
            case 2:
                al = ler_aluno();
                if (insere_lista_inicio(li, al))
                    printf("Aluno adicionado!\n");
                else
                    printf("Aluno adicionado!\n");
                break;
            case 3:
                al = ler_aluno();
                if (insere_lista_ordenada(li, al))
                    printf("Aluno adicionado!\n");
                else
                    printf("Aluno adicionado!\n");
                break;
            case 4:
                printf("Digite a matricula do aluno que sera removido: ");
                scanf("%d", &mat);
                if (remove_lista(li, mat))
                    printf("Aluno removido!\n");
                else
                    printf("Nao foi possivel remover ou aluno nao foi encontrado!\n");
                break;
            case 5:
                if (remove_lista_inicio(li))
                    printf("Aluno removido!\n");
                else
                    printf("Nao foi possivel remover ou a lista esta vazia!\n");
                break;
            case 6:
                if (remove_lista_final(li))
                    printf("Aluno removido!\n");
                else
                    printf("Nao foi possivel remover ou a lista esta vazia!\n");
                break;
            case 7:
                 printf("Tamanho da lista: %d\n", tamanho_lista(li));
                 break;
            case 8:
                 printf("Digite a matricula: ");
                 scanf("%d", &mat);
                 consulta(li, mat);
                 break;
            case 9:
                imprime_lista(li);
                break;
            case 10:
                printf("Digite a matricula do aluno para ser trocada: ");
                scanf("%d", &mat);
                p_troca = consulta(li, mat);
                if (p_troca != NULL) {
                    if (Troca(li, p_troca)) {
                        imprime_lista(li);
                    } else {
                        printf("Nao foi possivel trocar!\n");
                    }
                } else {
                    printf("Aluno nao encontrado!\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    libera_lista(li);
    return 0;
}
