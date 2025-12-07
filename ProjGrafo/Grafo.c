 #include "Grafo.h"

Grafo* cria_Grafo(int nro_vertices, int eh_ponderado) {
    Grafo *gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL) {
        gr->nos = nro_vertices;
        gr->eh_ponderado = (eh_ponderado != 0) ? 1 : 0;
        gr->vet = (Lista*) malloc(nro_vertices * sizeof(Lista));
        
        int i;
        for(i = 0; i < nro_vertices; i++)
            gr->vet[i] = NULL;
    }
    return gr;
}
/*explicacao: A funcao cria_Grafo aloca, ela primeiro aloca dinamicamente uma struct grafo. Se a alocacao for bem sucedida, armazena em gr->nos o numero 
de vertices informado por nro_vertices. Em seguida, normaliza o parametro eh_ponderado para 0 ou 1 e guarda em 
gr->eh_ponderado, indicando se o grafo usa pesos nas arestas. Depois disso, aloca um vetor em gr->vet, com uma posicao para cada vertice.
Cada posicao desse vetor eh inicializada com NULL indicando que, 
inicialmente nenhum vertice possui arestas saindo dele. Por fim, a funcao retorna o ponteiro para o grafo criado 
ou NULL caso a primeira alocacao falhe.
*/


void libera_Grafo(Grafo* gr){
    if(gr != NULL){
        int i;
        for(i=0; i < gr->nos; i++){
            No *aux = gr->vet[i];
            while(aux != NULL){
                No *temp = aux;
                aux = aux->prox;
                free(temp);
            }
        }
        free(gr->vet);
        free(gr);
    }
}
/*explicacao: a funcao libera_Grafo apaga tudo que foi criado para o grafo,
ela verifica se o ponteiro e valido, deois ela passa por todos os vertices e vai apagando cada no das listas
sando free, Quando todas as listas estiverem vazias, ela libera o vetor gr->vet e depois libera
tambem a estrutura do grafo, Depois disso o grafo nao pode mais ser usado.
*/

int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso) {
    if(gr == NULL || orig < 0 || orig >= gr->nos || dest < 0 || dest >= gr->nos)
        return 0;

    No* no = (No*) malloc(sizeof(No));
    if(no == NULL) return 0;

    no->destino = dest;
    no->peso = (gr->eh_ponderado) ? peso : 1.0;
    
    // Inserção no início (LIFO)
    no->prox = gr->vet[orig];
    gr->vet[orig] = no;

    if(eh_digrafo == 0)
        insereAresta(gr, dest, orig, 1, peso);

    return 1;
}
/*explicacao: a funcao insereAresta coloca uma nova aresta no grafo.
Ela primeiro verifica se o grafo e valido e se os vertices existem. Se tiver algo errado, ela retorna 0
Se estiver tudo certo, ela cria um novo no da lista e coloca nele o destino e o peso da aresta
Se o grafo nao for ponderad o peso vira 1.0 automaticamente.
Depois ela coloca esse no no comeco se o grafo nao for digrafo (eh_digrafo == 0),
ela chama de novo a funcao para inserir a aresta ao contrario,
assim o grafo vira nao direcionado, No final retorna 1 para indicar que deu certo.
*/

int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo) {
    if(gr == NULL || orig < 0 || orig >= gr->nos || dest < 0 || dest >= gr->nos)
        return 0;

    Lista* li = &gr->vet[orig];
    No* no = *li, *aux = NULL;

    while(no != NULL) {
        if(no->destino == dest) {
            if (aux == NULL) {
                *li = no->prox;
                free(no);
                no = *li;
            } else {
                aux->prox = no->prox;
                free(no);
                no = aux->prox;
            }
            break; // Removeu, sai do loop
        } else {
            aux = no;
            no = no->prox;
        }
    }

    if(eh_digrafo == 0)
        removeAresta(gr, dest, orig, 1);
        
    return 1;
}
/*explicacao: a funcao removeAresta tira uma aresta da lista do graf
Ela verifica se o grafo existe e se os vertices sao validos se nao for, retorna 0
Depois ela pega a lista do vertice orig e percorre ela ate achar o destino que quer remover,
Se o no que vai sair for o primeiro da lista, ela só muda a cabeca da lista para o proximo
Se for outro no mais pra frente, ela liga o no anterior direto no seguinte O no removido e apagado com free.
Se o grafo nao for digrafo (eh_digrafo == 0), ela tambem remove a aresta contraria chamando a mesma funcao.
Sempre retorna 1 no final, mesmo que a aresta nao exista*/


void imprime_Grafo(Grafo *gr){
    if(gr == NULL) return;
    int i;
    for(i=0; i < gr->nos; i++){
        printf("%d: ", i);
        No *aux = gr->vet[i];
        while(aux != NULL){
            if(gr->eh_ponderado)
                printf("%d(%.2f) -> ", aux->destino, aux->peso);
            else
                printf("%d -> ", aux->destino);
            aux = aux->prox;
        }
        printf("NULL\n");
    }
}

int buscaNo(Grafo* gr, int no) {
    if(gr == NULL || no < 0 || no >= gr->nos)
        return 0;
    return 1;
}

int buscaMenorAresta(Grafo* gr, int *orig_res, int *dest_res, float *peso_res) {
    if(gr == NULL) return 0;
    int encontrou = 0;
    int i;
    
    for(i = 0; i < gr->nos; i++) {
        No* no = gr->vet[i];
        while(no != NULL) {
            if(encontrou == 0 || no->peso < *peso_res) {
                *orig_res = i;
                *dest_res = no->destino;
                *peso_res = no->peso;
                encontrou = 1;
            }
            no = no->prox;
        }
    }
    return encontrou;
}