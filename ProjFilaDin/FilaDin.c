#include <stdio.h>
#include <stdlib.h>
#include "FilaDin.h" //inclui os Prot�tipos
//Defini��o do tipo Fila
struct elemento{
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;
//Defini��o do N� Descritor da Fila
struct fila{
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
};

Fila* cria_Fila(){
    Fila* fi = (Fila*) malloc(sizeof(Fila));
    if(fi != NULL){
        fi->final = NULL;
        fi->inicio = NULL;
        fi->qtd = 0;
    }
    return fi;
}

void libera_Fila(Fila* fi){
    if(fi != NULL){
        Elem* no;
        while(fi->inicio != NULL){
            no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
        }
        free(fi);
    }
}

int consulta_Fila(Fila* fi, struct aluno *al){
    if(fi == NULL)
        return 0;
    if(fi->inicio == NULL)
        return 0;
    *al = fi->inicio->dados;
    return 1;
}

int insere_Fila(Fila* fi, struct aluno al){
    if(fi == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if(fi->final == NULL)
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    fi->qtd++;
    return 1;
}

int remove_Fila(Fila* fi){
    if(fi == NULL)
        return 0;
    if(fi->inicio == NULL)
        return 0;
    Elem *no = fi->inicio;
    fi->inicio = fi->inicio->prox;
    if(fi->inicio == NULL)
        fi->final = NULL;
    free(no);
    fi->qtd--;
    return 1;
}

int tamanho_Fila(Fila* fi){
    if(fi == NULL)
        return 0;
    return fi->qtd;
}

int Fila_vazia(Fila* fi){
    if(fi == NULL)
        return 1;
    if(fi->inicio == NULL)
        return 1;
    return 0;
}

int Fila_cheia(Fila* fi){
    return 0;
}

void imprime_Fila(Fila* fi){
    if(fi == NULL)
        return;
    Elem* no = fi->inicio;
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;
    }
}

int separa(Fila* f1, Fila* f2, int n){
    if (f1 == NULL || f1->inicio == NULL)
        return 0;
    Elem *no = f1->inicio;
    int qtd_f1 = 1;
    while(no->prox != NULL && no->dados.matricula != n){
        no = no->prox;
        qtd_f1++;
    }
    if(no->prox == NULL){
        return 0; 
    }
    f2->inicio = no->prox;
    f2->final = f1->final;
    f2->qtd = f1->qtd - qtd_f1;
    f1->final = no;
    f1->final->prox = NULL;
    f1->qtd = qtd_f1;
    return 1;
}

struct elemento_ff{
    Fila* dados;
    struct elemento_ff *prox;
};
typedef struct elemento_ff ElemFF;

struct fila_de_filas{
    struct elemento_ff *inicio;
    struct elemento_ff *final;
};

Fila_F* cria_FilaDeFilas(){
    Fila_F* fi = (Fila_F*) malloc(sizeof(Fila_F));
    if(fi != NULL){
        fi->final = NULL;
        fi->inicio = NULL;
    }
    return fi;
}

void libera_Fila_F(Fila_F* fi){
    if(fi != NULL){
        ElemFF* no;
        while(fi->inicio != NULL){
            no = fi->inicio;
            libera_Fila(no->dados);
            fi->inicio = fi->inicio->prox;
            free(no);
        }
        free(fi);
    }
}

int insere_Fila_F(Fila_F* fi, Fila* f){
    if(fi == NULL) return 0;
    ElemFF *no = (ElemFF*) malloc(sizeof(ElemFF));
    if(no == NULL) return 0;
    no->dados = f;
    no->prox = NULL;
    if(fi->final == NULL)
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    return 1;
}

int remove_Fila_F(Fila_F* fi){
    if(fi == NULL || fi->inicio == NULL) return 0;
    ElemFF *no = fi->inicio;
    fi->inicio = fi->inicio->prox;
    if(fi->inicio == NULL)
        fi->final = NULL;
    libera_Fila(no->dados); 
    free(no);
    return 1;
}

void imprime_Fila_F(Fila_F* fi){
    if(fi == NULL) return;
    ElemFF* no = fi->inicio;
    int count = 1;
    while(no != NULL){
        printf("--- Fila Interna %d ---\n", count++);
        imprime_Fila(no->dados);
        no = no->prox;
    }
}

struct elemento_pilha {
    struct aluno dados;
    struct elemento_pilha *prox;
};
typedef struct elemento_pilha ElemPilha;

struct pilha {
    ElemPilha *topo;
    int qtd;
};

Pilha* cria_Pilha() {
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if (pi != NULL) {
        pi->topo = NULL;
        pi->qtd = 0;
    }
    return pi;
}

void libera_Pilha(Pilha* pi) {
    if (pi != NULL) {
        ElemPilha* no;
        while (pi->topo != NULL) {
            no = pi->topo;
            pi->topo = pi->topo->prox;
            free(no);
        }
        free(pi);
    }
}

int insere_Pilha(Pilha* pi, struct aluno al) {
    if (pi == NULL) return 0;
    ElemPilha* no = (ElemPilha*) malloc(sizeof(ElemPilha));
    if (no == NULL) return 0;
    no->dados = al;
    no->prox = pi->topo;
    pi->topo = no;
    pi->qtd++;
    return 1;
}

int remove_Pilha(Pilha* pi) {
    if (pi == NULL || pi->topo == NULL) return 0;
    ElemPilha* no = pi->topo;
    pi->topo = pi->topo->prox;
    free(no);
    pi->qtd--;
    return 1;
}

int consulta_Pilha(Pilha* pi, struct aluno *al) {
    if (pi == NULL || pi->topo == NULL) return 0;
    *al = pi->topo->dados;
    return 1;
}

int Pilha_vazia(Pilha* pi){
    if(pi == NULL) return 1;
    if(pi->topo == NULL) return 1;
    return 0;
}

void inverte_Fila(Fila* fi){
    if (fi == NULL || Fila_vazia(fi))
        return;

    Pilha* p_aux = cria_Pilha();
    struct aluno al_aux;

    while(!Fila_vazia(fi)){
        consulta_Fila(fi, &al_aux);
        insere_Pilha(p_aux, al_aux);
        remove_Fila(fi);
    }

    while(!Pilha_vazia(p_aux)){
        consulta_Pilha(p_aux, &al_aux);
        insere_Fila(fi, al_aux);
        remove_Pilha(p_aux);
    }

    libera_Pilha(p_aux);
}

int fura_Fila(Fila* fi, struct aluno al){
    if(fi == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = fi->inicio;
    fi->inicio = no;
    if(fi->final == NULL)
        fi->final = no;
    fi->qtd++;
    return 1;
}

void menu_a() {
    printf("\n\tControle de Decolagem\t\n");
    printf("1 - Listar numero de avioes aguardando\n");
    printf("2 - Autorizar decolagem do primeiro aviao\n");
    printf("3 - Adicionar um aviao a fila de espera\n");
    printf("4 - Listar todos os avioes na fila\n");
    printf("5 - Listar caracteristicas do primeiro aviao\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

int ex_5(){
    Fila* fila_decolagem = cria_Fila();
    int opcao;
    struct aluno av;
    do {
        menu();
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("\nNumero de avioes na fila: %d\n", tamanho_Fila(fila_decolagem));
                break;
            case 2:
                if (remove_Fila(fila_decolagem)) {
                    printf("\nDecolagem autorizada.\n");
                } else {
                    printf("\nNenhum aviao na fila.\n");
                }
                break;
            case 3:
                printf("\nDigite o ID do aviao: ");
                scanf("%d", &av.matricula);
                printf("Digite o nome do aviao: ");
                fgets(av.nome, 30, stdin);
                if (insere_Fila(fila_decolagem, av)) {
                    printf("Aviao adicionado a fila.\n");
                }
                break;
            case 4:
                 printf("\n--- Avioes na Fila ---\n");
                 imprime_Fila(fila_decolagem);
                 break;
            case 5:
                if (consulta_Fila(fila_decolagem, &av)) {
                    printf("\n--- Primeiro da Fila ---\n");
                    printf("ID: %d\n", av.matricula);
                    printf("Nome: %s\n", av.nome);
                } else {
                    printf("\nNenhum aviao na fila.\n");
                }
                break;
            case 0:
                printf("\nEncerrando programa.\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);
    libera_Fila(fila_decolagem);
    return 0;
}

void merge_Filas(Fila* f1, Fila* f2, Fila* f_res){
    if (f_res == NULL) return;
    struct aluno al1, al2;
    int tem1 = consulta_Fila(f1, &al1);
    int tem2 = consulta_Fila(f2, &al2);
    while (tem1 && tem2) {
        if (al1.matricula < al2.matricula){
            insere_Fila(f_res, al1);
            remove_Fila(f1);
            tem1 = consulta_Fila(f1, &al1);
        } else {
            insere_Fila(f_res, al2);
            remove_Fila(f2);
            tem2 = consulta_Fila(f2, &al2);
        }
    }
    while(tem1){
        insere_Fila(f_res, al1);
        remove_Fila(f1);
        tem1 = consulta_Fila(f1, &al1);
    }
    while(tem2){
        insere_Fila(f_res, al2);
        remove_Fila(f2);
        tem2 = consulta_Fila(f2, &al2);
    }
}

void reverso(Fila* fi){
    if (fi == NULL || Fila_vazia(fi))
        return;
    Pilha* p_aux = cria_Pilha();
    struct aluno al_aux;
    while(!Fila_vazia(fi)){
        consulta_Fila(fi, &al_aux);
        insere_Pilha(p_aux, al_aux);
        remove_Fila(fi);
    }
    while(!Pilha_vazia(p_aux)){
        consulta_Pilha(p_aux, &al_aux);
        insere_Fila(fi, al_aux);
        remove_Pilha(p_aux);
    }
    libera_Pilha(p_aux);
}

void menu(){
    printf("\n\t\tMENU\n");
    printf("1 - Inicializa fila.\n");
    printf("2 - Verifica se a fila eh vazia.\n");
    printf("3 - Verifica se a fila eh cheia.\n");
    printf("4 - Enfileira o elemento na fila.\n");
    printf("5 - Desenfileira elemento da fila.\n");
    printf("6 - Le o numero no inicio da fila.\n");
    printf("7 - Testar qual fila possui mais elementos.\n");
    printf("8 - Furar a fila.\n");
    printf("0 - Sair.\n");
    printf("Escolha uma opcao: ");
}

struct aluno ler_aluno(){
    struct aluno al;
    printf("Digite a matricula: ");
    scanf("%d", &al.matricula);
    printf("Digite o nome: ");
    scanf(" %s", &al.nome);
    al.n1 = al.n2 = al.n3 = 0;
    return al;
}

int ex_8(){
    Fila* f1 = NULL;
    Fila* f2 = NULL;
    int opcao;
    struct aluno al;
    do {
        menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                if(f1 != NULL) 
                    libera_Fila(f1);
                f1 = cria_Fila();
                printf("Fila 1 inicializada.\n");
                break;
            case 2:
                if(f1 == NULL || Fila_vazia(f1)) 
                    printf("Fila vazia.\n");
                else 
                    printf("Fila nao esta vazia.\n");
                break;
            case 3:
                if(Fila_cheia(f1)) 
                    printf("Fila cheia.\n");
                else 
                    printf("Fila nao esta cheia.\n");
                break;
            case 4:
                if(f1 == NULL) { 
                    printf("Nenhuma fila incializada.\n"); 
                    break; 
                }
                al = ler_aluno();
                insere_Fila(f1, al);
                printf("Aluno enfileirado.\n");
                break;
            case 5:
                 if(f1 == NULL) { 
                    printf("Nenhuma fila incializada.\n"); 
                    break; 
                }
                if(remove_Fila(f1)) 
                    printf("Elemento desenfileirado.\n");
                else 
                    printf("Fila vazia.\n");
                break;
            case 6:
                if(f1 == NULL) { 
                    printf("Nenhuma fila incializada.\n"); 
                    break; 
                }
                if(consulta_Fila(f1, &al)) {
                    printf("Primeiro elemento: Matricula %d, Nome %s", al.matricula, al.nome);
                } else {
                    printf("Fila vazia.\n");
                }
                break;
            case 7:
                 if(f2 != NULL) 
                    libera_Fila(f2);
                 f2 = cria_Fila();
                 insere_Fila(f2, ler_aluno());
                 printf("Tamanho Fila 1: %d\n", tamanho_Fila(f1));
                 printf("Tamanho Fila 2: %d\n", tamanho_Fila(f2));
                 if(tamanho_Fila(f1) > tamanho_Fila(f2)) 
                    printf("Fila 1 e maior.\n");
                 else if(tamanho_Fila(f2) > tamanho_Fila(f1)) 
                    printf("Fila 2 e maior.\n");
                 else 
                    printf("As filas tem o mesmo tamanho.\n");
                 libera_Fila(f2);
                 f2 = NULL;
                 break;
            case 8:
                if(f1 == NULL) { 
                    printf("Nenhuma fila incializada.\n"); 
                    break; 
                }
                al = ler_aluno();
                fura_Fila(f1, al);
                printf("Aluno adicionado no inicio.\n");
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
    if(f1 != NULL) 
        libera_Fila(f1);
    return 0;
}