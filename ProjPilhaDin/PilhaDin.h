//Arquivo PilhaDin.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

struct numeros{
    float numero;
};

typedef struct elemento* Pilha;
typedef struct numero* Pilha_num;
typedef struct elemento_char* Pilha_char;

Pilha* cria_Pilha();
void libera_Pilha(Pilha* pi);
int consulta_topo_Pilha(Pilha* pi, struct aluno *al);
int insere_Pilha(Pilha* pi, struct aluno al);
int remove_Pilha(Pilha* pi);
int tamanho_Pilha(Pilha* pi);
int Pilha_vazia(Pilha* pi);
int Pilha_cheia(Pilha* pi);
void imprime_Pilha(Pilha* pi);

int pop2(Pilha* pi);
int push2(Pilha* pi, struct aluno al1, struct aluno al2);
int popN(Pilha* pi, int n);
Pilha *pilha_copia(Pilha* pi);
Pilha_num* cria_Pilha_num();
void libera_Pilha_num(Pilha_num* pi);
int insere_Pilha_num(Pilha_num* pi, float n);
int remove_Pilha_num(Pilha_num* pi);
int consulta_topo_Pilha_num(Pilha_num* pi, float *n);
int Pilha_num_vazia(Pilha_num* pi);
int maior_menor_media(Pilha_num *pi);
int comparar_pilha(Pilha* pi1, Pilha* pi2);
int inverso_e_verificar(char* texto);
int pares_impares(Pilha* pi, struct numeros num);
int converter_binario(int decimal);
Pilha_char* cria_Pilha_char();
void libera_Pilha_char(Pilha_char* pi);
int insere_Pilha_char(Pilha_char* pi, char dado);
int remove_Pilha_char(Pilha_char* pi);
int consulta_topo_Pilha_char(Pilha_char* pi, char *dado);
int Pilha_char_vazia(Pilha_char* pi);
int verifica_forma(char* str);
void menu();

int questoes();
