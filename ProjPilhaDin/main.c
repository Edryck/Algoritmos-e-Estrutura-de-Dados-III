#include <stdio.h>
#include <stdlib.h>
#include "PilhaDin.h"

int main(){
    int opcao;
    float num;
    Pilha* pi = cria_Pilha();

    do {
        opcao = questoes();
        switch(opcao){
            case 1:{
                struct aluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
                printf("Tamanho: %d\n\n",tamanho_Pilha(pi));
                int i;
                for(i=0; i < 4; i++)
                    insere_Pilha(pi,a[i]);
                imprime_Pilha(pi);
                printf("Tamanho: %d\n\n",tamanho_Pilha(pi));

                for(i=0; i < 4; i++)
                    remove_Pilha(pi);
                printf("Tamanho: %d\n\n",tamanho_Pilha(pi));
                imprime_Pilha(pi);

                for(i=0; i < 4; i++)
                    insere_Pilha(pi,a[i]);
                printf("Tamanho: %d\n\n",tamanho_Pilha(pi));
                imprime_Pilha(pi);

                libera_Pilha(pi);
                break;
            }
            case 2:{
                int quant;

                printf("Digite a quantidade que irá retirar da pilha: ");
                scanf("%d", &quant);
                popN(pi, quant);
                break;
            }
            case 3:{
                printf("Pilha original: \n\n");
                imprime_Pilha(pi);
                printf("Cópia da pilha: \n\n");
                imprime_Pilha(pilha_copia(pi));
                break;
            }
            case 4:{
                // Novo caso para inserir N números
                if (pi == NULL) {
                    printf("Erro: A pilha nao foi inicializada.\n");
                    break;
                }
                int quant;
                printf("Informe a quantidade de elementos da pilha: ");
                scanf("%d", &quant);
                for(int i = 0; i < quant; i++){
                    printf("\nDigite o numero: ");
                    scanf("%f", &num);
                    if(insere_Pilha_num(pi, num)){
                        printf("Numero %d inserido com sucesso!\n", i + 1);
                    } else {
                        printf("Falha ao inserir o numero %d.\n", i + 1);
                        break;
                    }
                }
                break;
            }
            case 5:{
                maior_menor_media(pi);
                break;
            }
            case 6:{
                char texto[100];
                printf("Digite uma sequencia de caracteres: ");
                scanf(" %[^\n]", texto);
                inverso_e_verificar(texto);
                break;
            }
            case 7:{
                conta_par_impar(pi);
                break;
            }
            case 8:{
                char texto_ab[100];
                printf("Digite uma cadeia de caracteres na forma xCy: ");
                scanf(" %[^\n]", texto_ab);
                if (verifica_forma(texto_ab)) {
                    printf("A cadeia de caracteres e da forma xCy.\n");
                } else {
                    printf("A cadeia de caracteres e da forma xCy.\n");
                }
                break;
            }
            case 9:{
                int opcao, matricula;
                float n1, n2, n3;
                char nome[100];
                struct aluno Aluno;
                Pilha *pi = cria_Pilha();

                do{
                    menu();
                    scanf("%d", &opcao);
                    switch(opcao){
                        case 1:{
                            printf("Digite a matricula do aluno: ");
                            scanf("%d", &Aluno.matricula);
                            printf("Digite o nome do aluno: ");
                            scanf(" %s", Aluno.nome);
                            printf("Digite a nota 1, 2 e 3: ");
                            scanf("%f %f %f", &Aluno.n1, &Aluno.n2, &Aluno.n3);

                            pi = insere_Pilha(pi, Aluno);
                            if(pi == NULL)
                                printf("Não foi possivel criar a pilha.\n\n");
                            break;
                        }
                        case 2:
                            if(Pilha_vazia(pi) == 1)
                                printf("Pilha vazia!\n\n");
                            break;
                        case 3:
                            if(Pilha_cheia(pi) == 0)
                                printf("Pilha cheia!\n\n");
                            break;
                        case 4:{
                            printf("Digite a matricula do aluno: ");
                            scanf("%d", &Aluno.matricula);
                            printf("Digite o nome do aluno: ");
                            scanf(" %s", Aluno.nome);
                            printf("Digite a nota 1, 2 e 3: ");
                            scanf("%f %f %f", &Aluno.n1, &Aluno.n2, &Aluno.n3);
                            insere_Pilha(pi, Aluno);
                            break;
                        }
                        case 5:
                            remove_Pilha(pi);
                            break;
                        case 6:
                            consulta_topo_Pilha(pi, &Aluno);
                            system("pause");
                            break;
                        case 7:{
                            int num, bin;
                            printf("Digite o numero: ");
                            scanf("%d", &num);
                            converter_binario(num);
                            system("pause");
                            break;
                        }
                        case 8:
                            libera_Pilha(pi);
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n\n");
                            break;
                    }
                } while(opcao != 8);
                break;
            }
            case 0:
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n\n");
                break;
        }
    } while(opcao != 0);
    system("pause");
    return 0;
}

