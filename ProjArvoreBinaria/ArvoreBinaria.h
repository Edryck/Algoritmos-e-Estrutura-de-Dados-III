
typedef struct NO* ArvBin;
typedef struct NO_char* ArvBinChar;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
struct NO* remove_atual(struct NO* atual);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, int valor);
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

void quant_folha(ArvBin* raiz, int *count);
void identifica_no(ArvBin* raiz, int altura, int parente);
void conta_ocorrencia(ArvBin* raiz, int *count, int valor);
void folha_decrescente(ArvBin* raiz);
int arvore_igual(ArvBin* raiz1, ArvBin* raiz2);
void elimina_par(ArvBin* raiz);
int arv_similar(ArvBin* raiz1, ArvBin* raiz2);
void preOrdem_ArvBin_char(ArvBin* raiz);
int verifica_expressao(ArvBin* raiz);
void prefixa(ArvBin* raiz);
void infixa(ArvBin* raiz);
void posfixa(ArvBin* raiz);