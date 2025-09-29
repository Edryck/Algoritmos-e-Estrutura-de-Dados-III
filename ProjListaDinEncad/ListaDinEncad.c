#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncad.h" //inclui os Prot�tipos

//Defini��o do tipo lista
struct elemento{
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elemento;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elemento* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elemento *no;
    no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere in�cio
        *li = no;
    }else{
        Elemento *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elemento* no;
    no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    *li = no;
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elemento *no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        Elemento *ant, *atual = *li;
        while(atual != NULL && atual->dados.matricula < al.matricula){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere in�cio
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_lista(Lista* li, int mat){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elemento *ant, *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//n�o encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elemento *no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elemento *ant, *no = *li;
    while(no->prox != NULL){
        ant = no;
        no = no->prox;
    }

    if(no == (*li))//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elemento* no = *li;
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
    Elemento* no = *li;
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

int consulta (Lista* li, int mat) {
    if(li == NULL)
        return 0;
    Elemento* aux = *li;
    while(aux != NULL && aux->dados.matricula != mat)
        aux = aux->prox;
    if(aux == NULL){
        printf("Nao tem nenhum aluno com essa matricula\n\n");
        return 0;
    } else
        printf("Aluno: %s\n\n", aux->dados.nome);
    return 1;
}

int consulta_posicao (Lista* li, int pos) {
    int tam = 0;
    if(li == NULL)
        return 0;
    Elemento * aux = *li;
    while(aux != NULL && tam != pos) {
        tam++;
        aux->prox;
    }
    if(aux == NULL) {
        printf("Nao tem nenhum aluno nesta posicao");
        return 0;
    } else
        printf("Aluno: %s\n\n", aux->dados.nome);
    return 1;
}

int remove_no (Lista* li, int info) {
    Elemento* no = *li;
    if(li == NULL)
        return 0;
    if(no == NULL){
        printf("Nao encontrado\n\n");
        return 0;
    } else {
        if(no->dados.matricula == info){
            *li = no->prox;
            free(no);
            printf("Removido\n\n");
            return 1;
        } else
            return remove_no(&no->prox, info);
    }
}

int lista_iguais(Lista* l1, Lista* l2) {
    Elemento *aux1 = *l1, *aux2 = *l2;
    if(l1 == NULL) {
        if(l2 == NULL)
            return 1;
        else
            return 0;
    } else {
        if(l1 == NULL)
            return 0;
        else if(aux1->dados.matricula == aux2->dados.matricula) {
            if(aux1->prox == NULL && aux2->prox == NULL){
                printf("Listas Iguais\n\n");
                return 1;
            } else
                return lista_iguais(&aux1->prox, &aux2->prox);
        } else {
            printf("Listas Diferentes\n\n");
            return 0;
        }
    }
}

int insere_lista (Lista* li, struct aluno al, int pos) {
    if(li == NULL || pos <= 0)
        return 0;
    Elemento* no_novo = (Elemento*) malloc (sizeof(Elemento));
    if(no_novo == NULL)
        return 0;
    no_novo->dados = al;
    no_novo->prox = NULL;
    if(pos == 1) {
        no_novo->prox = *li;
        *li = no_novo;
        return 1;
    }
    int tam = 1;
    Elemento* atual = *li;
    while(atual != NULL && tam < pos - 1) {
        tam++;
        atual = atual->prox;
    }
    if (atual == NULL) {
        free(no_novo);
        return 0;
    }
    no_novo->prox = atual->prox;
    atual->prox = no_novo;
    return 1;
}

int insere_lista_float(Lista* li, float v) {
    if(li == NULL)
        return 0;
    Elemento* no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados.matricula = 0;
    no->dados.nome[0] = '\0';
    no->dados.n1 = v;
    no->dados.n2 = 0;
    no->dados.n3 = 0;
    no->prox = (*li);
    *li = no;
    return 1;
}

int remove_n(Lista* li, int n) {
    if(li == NULL || n < 0)
        return 0;
    Elemento* no = *li, *aux = NULL;
    while(no != NULL) {
        if(no->dados.matricula == n) {
            if (aux == NULL) {
                *li = no->prox;
                free(no);
                no = *li;
            } else {
                aux->prox = no->prox;
                free(no);
                no = aux->prox;
            }
        } else {
            aux = no;
            no = no->prox;
        }
    }
    return 1;
}

int concatenar(Lista* l1, Lista* l2) {
    if(l1 == NULL || l2 == NULL)
        return 0;
    if(lista_vazia(l1)) {
        *l1 = *l2;
        *l2 = NULL;
        return 1;
    }
    if(lista_vazia(l2))
        return 1;
    Elemento* no = *l1;
    while(no->prox != NULL)
        no = no->prox;
    no->prox = *l2;
    *l2 = NULL;
    return 1;
}

int remove_repetido(Lista* li) {
    if(li == NULL)
        return 0;
    Elemento* no = *li;
    while(no != NULL) {
        Elemento* aux = no;
        while(aux->prox != NULL) {
            if(aux->prox->dados.matricula == no->dados.matricula) {
                Elemento* remove = aux->prox;
                aux->prox = remove->prox;
                free(remove);
            } else
                aux = aux->prox;
        }
        no = no->prox;
    }
    return 1;
}

int fusao_lista(Lista* l1, Lista* l2) {
    if(l1 == NULL || l2 == NULL)
        return 0;
    if(lista_vazia(l1)) {
        *l1 = *l2;
        *l2 = NULL;
        return 1;
    }
    if(lista_vazia(l2))
        return 1;
    Elemento* aux1 = *l1, *aux2 = *l2, *ant1 = NULL;
    while(aux2 != NULL) {
        while(aux1 != NULL && aux1->dados.matricula < aux2->dados.matricula) {
            ant1 = aux1;
            aux1 = aux1->prox;
        }
        Elemento* pos2 = aux2->prox;
        if(ant1 == NULL) {
            aux2->prox = *l1;
            *l1 = aux2;
        } else {
            ant1->prox = aux2;
            aux2->prox = aux1;
        }
        ant1 = aux2;
        aux2 = pos2;
    }
    *l2 = NULL;
    return 1;
}

int Troca(Lista* li, Elemento* p) {
    if(li == NULL || *li == NULL)
        return 0;
    if(p == NULL || p->prox == NULL)
        return 0;
    Elemento* pos = p->prox;
    if(*li == p) {
        *li = pos;
        p->prox = pos->prox;
        pos->prox = p;
    } else {
        Elemento* ant = *li;
        while(ant != NULL && ant->prox != p)
            ant = ant->prox;
        if(ant == NULL)
            return 0;
        ant->prox = pos;
        p->prox = pos->prox;
        pos->prox = p;
    }
    return 1;
}
