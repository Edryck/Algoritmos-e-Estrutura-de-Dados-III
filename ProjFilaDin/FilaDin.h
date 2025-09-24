//Arquivo FilaDin.h
struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct fila Fila;

Fila* cria_Fila();
void libera_Fila(Fila* fi);
int consulta_Fila(Fila* fi, struct aluno *al);
int insere_Fila(Fila* fi, struct aluno al);
int remove_Fila(Fila* fi);
int tamanho_Fila(Fila* fi);
int Fila_vazia(Fila* fi);
int Fila_cheia(Fila* fi);
void imprime_Fila(Fila* fi);

int separa(Fila* f1, Fila* f2, int n);

typedef struct fila_de_filas Fila_F;

Fila_F* cria_Fila_F();
void libera_Fila_F(Fila_F* fi);
int insere_Fila_F(Fila_F* fi, Fila* f);
int remove_Fila_F(Fila_F* fi);
void imprime_Fila_F(Fila_F* fi);

typedef struct pilha Pilha;

Pilha* cria_Pilha();
void libera_Pilha(Pilha* pi);
int insere_Pilha(Pilha* pi, struct aluno al);
int remove_Pilha(Pilha* pi);
int consulta_Pilha(Pilha* pi, struct aluno *al);
int Pilha_vazia(Pilha* pi);

void inverte_Fila(Fila* fi);

int fura_Fila(Fila* fi, struct aluno al);

int ex_5();

void merge_Filas(Fila* f1, Fila* f2, Fila* f_res);

void reverso(Fila* fi);

int fura_Fila(Fila* fi, struct aluno al);

int ex_8();