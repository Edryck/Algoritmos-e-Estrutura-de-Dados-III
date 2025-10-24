#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h" //inclui os Prot�tipos

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada n�
    free(raiz);//libera a raiz
}
// 1 - Observe as fun��es insere_Arvore e remove_Arvore fa�a testes com as mesmas e descreva como cada fun��o opera na �rvore.
// Respondendo comentando o c�digo
int insere_ArvBin(ArvBin* raiz, int valor){
    if(raiz == NULL) // Verifica se existe
        return 0;
    struct NO* novo; // Cria um n� e aloca ele
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL) // Verifica se alocou ele
        return 0;
    novo->info = valor; // Atribui o valor dele
    novo->dir = NULL; // Por enquanto a direita e a esquerda fica nula
    novo->esq = NULL;

    if(*raiz == NULL) // Se for o primeiro n� da �rvore, a cabe�a passa a apontar pra ele
        *raiz = novo; // Esse if s� � utilizado uma vez, que � quando vai adicionar o primeiro n�
    else{
        struct NO* atual = *raiz; // Guarda o n� atual
        struct NO* ant = NULL; // Cria um n� anterior, inicialmente nulo
        while(atual != NULL){ // Percorre at� a folha
            ant = atual; // Atualizando o anterior
            if(valor == atual->info){ // Se o valor que do n� que ser� adicionado for igual o valor do atual
                free(novo); // Libera ele, ele j� existe
                return 0;//elemento j� existe
            }

            if(valor > atual->info) // Verifica pra qual lado ele tem que ir
                atual = atual->dir; // Se o valor for maior, vai pra direita que tem os valores maiores que o atual
            else
                atual = atual->esq; // Se n�o, o contr�rio if, ele tem o valor menor que o atual, ent�o pra esquerda
        }
        if(valor > ant->info) // Se chegou aqui � por que a direita ou a esquerda � nula
            ant->dir = novo; // Se for maior, o novo n� fica na direita
        else
            ant->esq = novo; // Se n�o, fica na esquerda
    }
    return 1; // Sucesso
}

// http://www.ime.usp.br/~pf/algoritmos/aulas/binst.html
int remove_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL) // Verifica��o
        return 0;
    struct NO* ant = NULL; // Cria um anterior pra armazenar depois pra liberar o n�
    struct NO* atual = *raiz; // Um atual pra apontar pra raiz
    while(atual != NULL){ // Enquanto for diferente de nulo ele percorre at� achar o n� com o valor = valor
        if(valor == atual->info){ // Verifica se o valor � igual o valor do n�
            if(atual == *raiz) // No caso de se a raiz, remove ela
                *raiz = remove_atual(atual);
            else{ // Se n�o passa para as outras verifica��es
                if(ant->dir == atual) // Se for o n� da direita, remove ele
                    ant->dir = remove_atual(atual);
                else // Se n�o, tira da esquerda
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual; // Atualizando o anterior pra remo��o
        if(valor > atual->info) // Se for maior, direita
            atual = atual->dir; // O atual passa a ser o n� da direita
        else // Se n�o, esquerda
            atual = atual->esq; // O atual passa a ser o n� da esquerda
    }
    return 0; // Se n�o passou antes, falhou
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

/*struct NO* remove_atual(struct NO* atual) {
    struct NO *no1, *no2;
    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }
    // no2 � o n� anterior a r na ordem e-r-d
    // no1 � o pai de no2
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}*/

int altura_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}


void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%d\n",(*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}
// 2 -  Com base na fun��o escreva as fun��es de varredura EMOrdem_Arvore e POSOrdem_ArvBin.
void emOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d\n",(*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d\n",(*raiz)->info);
    }
}

// 3 - Fa�a uma recursiva que conta a quantidade de n�s que existem na �rvore int TotalNO_Arvore(ArvBin *raiz).
int totalNO_ArvBin(ArvBin* raiz) {
    if(raiz == NULL || *raiz == NULL)
        return 0;

    int quant_esq = totalNO_ArvBin(&((*raiz)->esq));
    int quant_dir = totalNO_ArvBin(&((*raiz)->dir));

    return (quant_esq + quant_dir + 1);
}

// 4 - Fa�a uma fun��o que consulta se um determinado valor existe na �rvore int Cons_Arvore(ArvBin *raiz, int valor).
int consulta_ArvBin(ArvBin* raiz, int valor) {
    if(raiz == NULL)
        return 0;
    if((*raiz)->info == valor)
        return 1;
    if(valor < (*raiz)->info)
        return consulta_ArvBin(&((*raiz)->esq), valor);
    else
        return consulta_ArvBin(&((*raiz)->dir), valor);
}

// 5 - Fa�a uma fun��o que recebe um determinado n� da �rvore e o remove struct NO* Remove_ArvoreAtual(struct NO* atual)
struct NO* remove_atual(struct NO* atual){
    if(atual == NULL)
        return NULL;
    // Caso o n� seja uma folha
    if(atual->dir == NULL && atual->esq == NULL){
        free(atual);
        return NULL;
    }
    // Caso o n� tenha um filho na direita
    if(atual->esq == NULL){
        struct NO* temp = atual->dir;
        free(atual);
        return temp;
    }
    // Caso o n� tenha um filho na esquerda
    if(atual->dir == NULL){
        struct NO* temp = atual->esq;
        free(atual);
        return temp;
    }
    // Caso o n� tenha dois filhos, esquerda e direita
    // Procura o menor valor da direita
    struct NO* menor = atual->dir;
    while (menor->esq != NULL)
        menor = menor->esq;

    struct NO* filho = menor; // Pega o menor n� da direita
    atual->info = filho ->info; // Copia o dado do filho para o n� atual
    struct NO* pai_filho = atual->dir; // Procura o pai do filho

    // Se o filho for sucessor direto do atual
    if(pai_filho == filho)
        atual->dir = filho->dir; // O atual aponta para sua direita para o o filho direito do sucessor
    else {
        // Vai at� o pai do filho
        while(pai_filho->esq != filho)
            pai_filho = pai_filho->esq;
        // O pai do filho pula o filho e aponta para o filho direito do filho
        pai_filho->esq = filho->dir;

    }
    free(filho); // Libera o filho
    return atual;
};
