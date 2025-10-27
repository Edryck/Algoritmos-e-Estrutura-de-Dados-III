#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

void menu(Matriz* m);

int main() {
    Matriz* m = NULL;
    int opcao;
    int linha, coluna, valor, x, y; 
    int valor_lido;
    Elemento* no_encontrado;

    do {
        menu(m);
        scanf("%d", &opcao);

        if (m == NULL) {
            // Matriz não existe
            switch (opcao) {
                case 1:
                    printf("Digite o numero de linhas: ");
                    scanf("%d", &linha);
                    printf("Digite o numero de colunas: ");
                    scanf("%d", &coluna);
                    m = cria_matriz(linha, coluna); 
                    if (m != NULL) {
                        printf("Matriz %dx%d criada com sucesso!\n", linha, coluna);
                        imprime_matriz(m);
                    } else {
                        printf("Erro: Dimensoes invalidas.\n");
                    }
                    break;
                case 0:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opcao invalida. Crie uma matriz primeiro.\n");
                    break;
            }
        } else {
            // Matriz já existe
            switch (opcao) {
                case 1: // Inserir Valor
                    printf("Digite a linha (x): "); scanf("%d", &x);
                    printf("Digite a coluna (y): "); scanf("%d", &y);
                    printf("Digite o valor: "); scanf("%d", &valor);
                    if (insere_matriz(m, valor, x, y)) {
                        printf("Valor %d inserido em (%d, %d).\n", valor, x, y);
                    } else {
                        printf("Erro: Posicao (%d, %d) fora dos limites da matriz.\n", x, y);
                    }
                    break;
                case 2: // Remover Valor (definir como 0)
                    printf("Digite a linha (x): "); scanf("%d", &x);
                    printf("Digite a coluna (y): "); scanf("%d", &y);
                    if (remove_especifico(m, x, y)) { //
                        printf("Valor em (%d, %d) removido (definido como 0).\n", x, y);
                    } else {
                        printf("Erro: Posicao (%d, %d) fora dos limites da matriz.\n", x, y);
                    }
                    break;
                case 3: // Consultar Valor
                    printf("Digite a linha (x): "); scanf("%d", &x);
                    printf("Digite a coluna (y): "); scanf("%d", &y);
                    if (consulta_valor(m, x, y, &valor_lido)) {
                        printf("Valor na posicao (%d, %d) e: %d\n", x, y, valor_lido);
                    } else {
                        printf("Erro: Posicao (%d, %d) fora dos limites da matriz.\n", x, y);
                    }
                    break;
                case 4: // Buscar Valor
                    printf("Digite o valor a ser buscado: ");
                    scanf("%d", &valor);
                    no_encontrado = busca_valor(m, valor);
                    if (no_encontrado != NULL) {
                        // A struct Elemento não guarda x,y, então só podemos confirmar que existe
                        printf("O valor %d foi encontrado na matriz.\n", valor);
                    } else {
                        printf("O valor %d nao foi encontrado na matriz.\n", valor);
                    }
                    break;
                case 5: // Imprimir Vizinhos
                    printf("Digite a linha (x): "); scanf("%d", &x);
                    printf("Digite a coluna (y): "); scanf("%d", &y);
                    imprime_vizinhos(m, x, y);
                    break;
                case 6: // Imprimir Matriz Completa
                    imprime_matriz(m);
                    break;
                case 7: // Ver os dados
                    printf("\t\t\tDados da Matriz\n");
                    printf("Dimensoes: %d linhas x %d colunas\n", m->linhas, m->colunas);
                    printf("Total de Nos: %d\n", tamanho_total(m));
                    printf("Nos em Uso (valor != 0): %d\n", tamanho_usado(m));
                    printf("Matriz esta vazia (todos 0)? %s\n", matriz_vazia(m) ? "Sim" : "Nao");
                    printf("Matriz esta cheia (nenhum 0)? %s\n", matriz_cheia(m) ? "Sim" : "Nao");
                    break;
                case 8: // Destruir Matriz
                    libera_matriz(m); 
                    printf("Matriz liberada. Voce pode criar uma nova.\n");
                    m = NULL;
                    break;
                case 0: // Sair
                    printf("Saindo e liberando memoria...\n");
                    libera_matriz(m); 
                    break;
                default:
                    printf("Opcao invalida. Tente novamente.\n");
                    break;
            }
        }

        printf("\nPressione ENTER para continuar...");
    } while (opcao != 0);

    return 0;
}

void menu(Matriz* m) {
    printf("\t\t\tMenu\n");

    if (m == NULL) {
        printf("A matriz ainda nao foi criada.\n\n");
        printf("1 - Criar Matriz\n");
        printf("0 - Sair\n");
    } else {
        printf("Matriz %dx%d carregada.\n\n", m->linhas, m->colunas);
        printf("1 - Inserir Valor (x, y)\n");
        printf("2 - Remover Valor (x, y) (define como 0)\n");
        printf("3 - Consultar Valor (x, y)\n");
        printf("4 - Buscar Valor (verifica se existe)\n");
        printf("5 - Imprimir Vizinhos (x, y)\n");
        printf("6 - Imprimir Matriz Completa\n");
        printf("7 - Ver Estatisticas\n");
        printf("8 - Liberar a matriz\n");
        printf("0 - Sair (libera a lista tambem)\n");
    }
    printf("=================================\n");
    printf("Escolha uma opcao: ");
}