//Arquivo ListaDinEncad.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct elemento* Lista;
typedef struct elemento Elemento;

Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_inicio(Lista* li, struct aluno al);
int insere_lista_ordenada(Lista* li, struct aluno al);
int remove_lista(Lista* li, int mat);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
int lista_cheia(Lista* li);
void imprime_lista(Lista* li);
// Exercício 1
int consulta (Lista* li, int mat);
int consulta_posicao (Lista* li, int pos);
// Exercício 2
int remove_no (Lista* li, int info);
int lista_iguais(Lista* l1, Lista* l2);
// Exercício 3
int insere_lista(Lista* li, struct aluno al, int pos);
// Exercício 4
int insere_lista_float(Lista* li, float v);
// Exercício 5
int remove_n(Lista* li, int n);
// Exercício 6
int concatenar(Lista* l1, Lista* l2);
// Exercício 7
int remove_repetido(Lista* li);
// Exercício 8
int fusao_lista(Lista* l1, Lista* l2);
// Exercício 9
int Troca(Lista* li, Elemento* p);
