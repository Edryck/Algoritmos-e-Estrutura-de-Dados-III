#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h" //inclui os Prot�tipos

//Defini��o do tipo lista
struct elemento{
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->ant = NULL;
        *li = no;
    }else{
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if(*li != NULL)//lista n�o vazia: apontar para o anterior!
        (*li)->ant = no;
    *li = no;
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    *li = no->prox;
    if(no->prox != NULL)
        no->prox->ant = NULL;

    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    while(no->prox != NULL)
        no = no->prox;

    if(no->ant == NULL)//remover o primeiro e �nico
        *li = no->prox;
    else
        no->ant->prox = NULL;

    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
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

int remove_mat(Lista* li, int mat) {
    if(li == NULL || *li == NULL)
        return 0;
    Elem* no = *li;
    while(no != NULL && no->dados.matricula != mat) // Percorre a lista até achar o elemento que tem que remover
        no = no->prox;
    if(no == NULL) // Se for nulo, o aluno não foi encontrado
        return 0;
    else if(no->ant == NULL) { // Se for o primeiro nó, o prox passar a ser a cabeça
        *li = no->prox;
        if(no->prox != NULL) // Se for não ficou vazia, o ant da cabeça recebe nulo
            no->prox->ant = NULL;
    } else {
        no->ant->prox = no->prox; // Se estiver no meio, o prox do ant aponta pro prox do atual
        if(no->prox != NULL) // Se estiver no fim, esse if não executa, pq o prox do ant já recebeu nulo
            no->prox->ant = no->ant;
    }
    free(no);
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    }
    else{
        Elem *ant, *atual = *li;
        while(atual != NULL && atual->dados.matricula < al.matricula){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere in�cio
            no->ant = NULL;
            no->prox = (*li);
            (*li)->ant = no;
            *li = no;
        }else{
            no->prox = atual;
            no->ant = ant;
            ant->prox = no;
            if(atual != NULL)
                atual->ant = no;
        }
        return 1;
    }
}

int conta_lista_nota(Lista* li, int n1){
    int count = 0;
    float n = n1;
    if(li == NULL || *li == NULL)
        return 0;
    while((*li)->prox != NULL){
        if((*li)->dados.n1 == n || (*li)->dados.n2 == n || (*li)->dados.n3 == n)
            count++;
        *li = (*li)->prox;
    }
    if ((*li)->dados.n1 == n || (*li)->dados.n2 == n || (*li)->dados.n3 == n) {
        count++;
    }
    while((*li)->ant != NULL){
        *li = (*li)->ant;
    }
    return count;
}

int insere_lista_final_circ(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al; 
    if((*li) == NULL){
        no->prox = no;
        no->ant = no;
        *li = no;
    } else {
        Elem *ant = (*li)->ant;
        no->prox = (*li);
        no->ant = ant;
        ant->prox = no;
        (*li)->ant = no;
    }
    return 1;
}

int insere_lista_inicio_circ(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if ((*li) == NULL) {
        *li = no;
        no->prox = no;
        no->ant = no;
    } else {
        Elem *aux= (*li)->ant;
        no->prox = (*li);
        no->ant = aux;
        (*li)->ant = no;
        aux->prox = no;
        *li = no;
    }
    return 1;
}

void percorre_lista_circ(Lista* li) {
    if (li == NULL || (*li) == NULL)
        return;
    Elem* no = *li;
    while (no != (*li)){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;
    }
}